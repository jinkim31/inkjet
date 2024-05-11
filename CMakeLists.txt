cmake_minimum_required(VERSION 3.12)
project(inkjet)
set(CMAKE_CXX_STANDARD 17)

option(INKJET_WITH_IMMVISION "Use ImmVision and fetch OpenCV" OFF)

if(${INKJET_WITH_IMMVISION})
    set(IMMVISION_FETCH_OPENCV ON)
    set(IMGUI_BUNDLE_WITH_IMMVISION ON)
    add_compile_definitions(INKJET_WITH_IMMVISION)
else()
    set(IMMVISION_FETCH_OPENCV OFF)
    set(IMGUI_BUNDLE_WITH_IMMVISION OFF)
endif ()
set(HELLOIMGUI_DOWNLOAD_FREETYPE_IF_NEEDED ON)
set(IMGUI_BUNDLE_BUILD_PYTHON OFF)

# cmake submodules
add_subdirectory(external/imgui_bundle)
add_subdirectory(external/siglot)
add_subdirectory(external/poco)
add_subdirectory(external/serial)

# inkjet library
add_library(inkjet STATIC
        inkjet/inkjet/inkjet.cpp
        inkjet/inkjet/comm/serial/serial.cpp
        inkjet/inkjet/layout/width_layout.cpp
        inkjet/inkjet/state_machine/state_machine.cpp
        inkjet/inkjet/comm/comm.cpp
        inkjet/inkjet/comm/socket/socket.cpp
        inkjet/inkjet/comm/socket/udp_client.cpp
)

# link libraries
target_link_libraries(inkjet PRIVATE ${libserialport})
target_link_libraries(inkjet PUBLIC  siglot imgui_bundle)
target_link_libraries(inkjet PRIVATE Poco::Net)
target_link_libraries(inkjet PRIVATE serial)

# inkjet include directories
target_include_directories(inkjet PUBLIC inkjet)
target_include_directories(inkjet PUBLIC external/siglot)
target_include_directories(inkjet PUBLIC external/libserialport)
target_include_directories(inkjet PUBLIC external/poco/Net/include)
target_include_directories(inkjet PUBLIC external/poco/Foundation/include)
target_include_directories(inkjet PUBLIC external/serial/include)

# example executable
imgui_bundle_add_app(inkjet_example
        example/main.cpp
        example/application.cpp
)
target_link_libraries(inkjet_example PRIVATE inkjet)
