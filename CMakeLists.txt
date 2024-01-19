cmake_minimum_required(VERSION 3.12)
project(pdf_toc)

# Add your source files here
set(SOURCE_FILES main.c)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories for the project
include_directories(${CMAKE_SOURCE_DIR} /opt/homebrew/Cellar/mupdf/1.23.7/include)

# Manually set the paths for cJSON
set(cJSON_INCLUDE_DIR /opt/homebrew/Cellar/cjson/1.7.17/include)
set(cJSON_LIBRARIES /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson.a /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson.a /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson_utils.1.dylib /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson.1.7.17.dylib /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson.dylib /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson_utils.a /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson.1.dylib /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson_utils.1.7.17.dylib /opt/homebrew/Cellar/cjson/1.7.17/lib/libcjson_utils.dylib)

# Manually set the paths for MuPDF
set(MUPDF_INCLUDE_DIR /opt/homebrew/Cellar/mupdf/1.23.7/include)
set(MUPDF_LIBRARIES /opt/homebrew/Cellar/mupdf/1.23.7/lib/libmupdf-third.dylib /opt/homebrew/Cellar/mupdf/1.23.7/lib/libmupdf.dylib)

# Add executable target
add_executable(pdf_toc ${SOURCE_FILES})

# Add cJSON and MuPDF to target_include_directories
target_include_directories(pdf_toc PRIVATE ${cJSON_INCLUDE_DIR} ${MUPDF_INCLUDE_DIR})

# Link cJSON and MuPDF to target_link_libraries
target_link_libraries(pdf_toc ${cJSON_LIBRARIES} ${MUPDF_LIBRARIES})
