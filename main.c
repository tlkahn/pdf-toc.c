#include <mupdf/fitz.h>
#include <cjson/cJSON.h>
#include <stdio.h>

cJSON *parse_outline(fz_context *ctx, fz_outline *outline)
{
    cJSON *toc_array = cJSON_CreateArray();

    while (outline)
    {
        cJSON *toc_item = cJSON_CreateObject();
        cJSON_AddStringToObject(toc_item, "title", outline->title);
        cJSON_AddNumberToObject(toc_item, "page", outline->page.page + 1);

        if (outline->down)
        {
            cJSON *subitems = parse_outline(ctx, outline->down);
            cJSON_AddItemToObject(toc_item, "subitem", subitems);
        }

        cJSON_AddItemToArray(toc_array, toc_item);
        outline = outline->next;
    }

    return toc_array;
}

char *extract_toc(const char *filepath)
{
    fz_context *ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    fz_register_document_handlers(ctx);

    char *json_string = NULL;

    fz_try(ctx)
    {
        fz_document *doc = fz_open_document(ctx, filepath);
        fz_outline *outline = fz_load_outline(ctx, doc);
        cJSON *toc_array = parse_outline(ctx, outline);

        fz_drop_outline(ctx, outline);
        fz_drop_document(ctx, doc);
        fz_drop_context(ctx);

        json_string = cJSON_PrintUnformatted(toc_array);
        cJSON_Delete(toc_array);
    }
    fz_catch(ctx)
    {
        fprintf(stderr, "Cannot open document: %s\n", filepath);
        fz_drop_context(ctx);
        return NULL;
    }

    return json_string;
}

void write_item(cJSON *item, int level, FILE *file)
{
    for (int i = 0; i < level; ++i) fprintf(file, "*");
    fprintf(file, " %s\n", cJSON_GetObjectItem(item, "title")->valuestring);
    fprintf(file, "Page: %d\n\n", cJSON_GetObjectItem(item, "page")->valueint);

    cJSON *subitems = cJSON_GetObjectItem(item, "subitem");
    if (subitems != NULL)
    {
        cJSON *subitem = NULL;
        cJSON_ArrayForEach(subitem, subitems)
        {
            write_item(subitem, level + 1, file);
        }
    }
}

void write_toc_to_markdown(const char *json_string, const char *output_file_path)
{
    cJSON *toc_array = cJSON_Parse(json_string);
    if (toc_array == NULL) return;

    FILE *output_file = fopen(output_file_path, "w");
    if (output_file == NULL) return;

    cJSON *item = NULL;
    cJSON_ArrayForEach(item, toc_array)
    {
        write_item(item, 2, output_file);
    }

    cJSON_Delete(toc_array);
    fclose(output_file);
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    const char *output_file_path = argv[2];

    FILE *file = fopen(filepath, "r");
    if (file)
    {
        fclose(file);
        char *json_string = extract_toc(filepath);
        if (json_string != NULL) {
          write_toc_to_markdown(json_string, output_file_path);
          free(json_string);
        }
    }
    else
    {
        fprintf(stderr, "Invalid filepath: %s\n", filepath);
        return 1;
    }

    return 0;
}
