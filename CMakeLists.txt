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
        inkjet/inkjet/inkjet.cpp
        inkjet/inkjet/comm/serial/serial.cpp
)

# link libraries
target_link_libraries(inkjet PUBLIC siglot imgui_bundle)
target_include_directories(inkjet PUBLIC  external/siglot)

# link libserialport
IF (WIN32)
    list(APPEND CMAKE_PREFIX_PATH "external/libserialport/win_x86-64")
    find_library(libserialport REQUIRED NAMES libserialport.lib)
ELSEIF(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "external/libserialport/apple_arm64")
    find_library(libserialport REQUIRED NAMES libserialport.dylib)
ELSE(UNIX)
    list(APPEND CMAKE_PREFIX_PATH "external/libserialport/linux_x86-64")
    find_library(libserialport REQUIRED NAMES libserialport.a)
ENDIF()
target_link_libraries(inkjet PRIVATE ${libserialport})
target_include_directories(inkjet PUBLIC external/libserialport)

# inkjet include paths
target_include_directories(inkjet PUBLIC inkjet)

# example executable
imgui_bundle_add_app(inkjet_example
        example/main.cpp
        example/application.cpp
)
target_link_libraries(inkjet_example PRIVATE inkjet)
