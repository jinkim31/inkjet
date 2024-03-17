cmake_minimum_required(VERSION 3.12)
project(inkjet)
set(CMAKE_CXX_STANDARD 17)

set(SIGLOT_USE_GRAPHVIZ ON)
set(HELLOIMGUI_DOWNLOAD_FREETYPE_IF_NEEDED ON)
set(IMMVISION_FETCH_OPENCV ON)

add_subdirectory(external/imgui_bundle)
add_subdirectory(external/siglot)

# inkjet library
add_library(inkjet STATIC
        inkjet/inkjet.cpp
        inkjet/comm/serial/serial.cpp
)
target_link_libraries(inkjet PUBLIC siglot imgui_bundle)
target_include_directories(inkjet PUBLIC
        inkjet
        external/siglot)

# example executable
imgui_bundle_add_app(inkjet_example
        example/main.cpp
        inkjet/inkjet.cpp
        example/application.cpp
        inkjet/comm/serial/serial.cpp
)
target_link_libraries(inkjet_example PRIVATE inkjet)

