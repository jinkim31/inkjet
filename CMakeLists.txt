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

add_subdirectory(external/imgui_bundle)
add_subdirectory(external/siglot)

# find boost
find_package(Boost 1.40.0 REQUIRED system)

# inkjet library
add_library(inkjet STATIC
        inkjet/inkjet/inkjet.cpp
        inkjet/inkjet/comm/serial/serial.cpp
        inkjet/inkjet/layout/width_layout.cpp
        inkjet/inkjet/state_machine/state_machine.cpp
        inkjet/inkjet/comm/comm.cpp
        inkjet/inkjet/comm/socket/udp_socket.cpp
)
message("boost:")
message(${Boost_INCLUDE_DIRS})

# link libraries
target_link_libraries(inkjet PUBLIC ${Boost_LIBRARIES} siglot imgui_bundle)
target_include_directories(inkjet PUBLIC  external/siglot)
target_include_directories(inkjet PUBLIC ${Boost_INCLUDE_DIRS})

# link libserialport
IF (WIN32)
    list(APPEND CMAKE_PREFIX_PATH "external/libserialport/win_x86-64_msvc")
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
