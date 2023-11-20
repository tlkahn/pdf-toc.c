# PDF Table of Contents Extractor

This C program uses the MuPDF library to extract the table of contents (ToC) from a PDF file and prints it in JSON format. The output includes the titles and page numbers for each entry in the ToC, along with any nested sub-items.

## Dependencies

- MuPDF: A lightweight PDF, XPS, and E-book viewer and parser library.
- cJSON: A C library for parsing and generating JSON data.

## Building

Simply use:
```
make
```

Or you want to do it manually:

1. Install the MuPDF and cJSON libraries.
2. Compile the program using the following command:

```sh
gcc -o pdf-toc main.c -lmupdf -lmupdf-third -lcjson -lm
```

If the libraries are installed in non-standard locations, specify the include and library paths using the `-I` and `-L` options:

```sh
gcc -o pdf-toc main.c -I/path/to/mupdf/include -I/path/to/cjson/include -L/path/to/mupdf/lib -L/path/to/cjson/lib -lmupdf -lmupdf-third -lcjson -lm
```

## Usage

```sh
./pdf-toc <filepath>
```

Replace `<filepath>` with the path to the PDF file you want to extract the ToC from.

## Example

```sh
./pdf-toc sample.pdf
```

This will print the ToC in JSON format:

```
[
  {
    "title": "Chapter 1",
    "page": 1,
    "subitem": [
      {
        "title": "Section 1.1",
        "page": 2
      },
      {
        "title": "Section 1.2",
        "page": 3
      }
    ]
  },
  {
    "title": "Chapter 2",
    "page": 4
  }
]
```