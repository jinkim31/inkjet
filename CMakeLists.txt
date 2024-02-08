cmake_minimum_required(VERSION 3.12)
project(inkjet)
set(CMAKE_CXX_STANDARD 17)

set(HELLOIMGUI_DOWNLOAD_FREETYPE_IF_NEEDED ON)
set(IMMVISION_FETCH_OPENCV ON)

if (NOT TARGET imgui_bundle)
    message(STATUS "Fetching imgui_bundle...")
    include(FetchContent)
    Set(FETCHCONTENT_QUIET FALSE)
    FetchContent_Declare(imgui_bundle GIT_REPOSITORY https://github.com/pthom/imgui_bundle.git GIT_TAG main)
    FetchContent_MakeAvailable(imgui_bundle)
endif()

imgui_bundle_add_app(${PROJECT_NAME} main.cpp inkjet.cpp application.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE external/IconFontCppHeaders)
add_subdirectory(external/siglot)
target_link_libraries(${PROJECT_NAME} PRIVATE siglot)

