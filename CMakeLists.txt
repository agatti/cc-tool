cmake_minimum_required(VERSION 3.26)
project(cc-tool)

set(DISABLE_CCACHE OFF CACHE BOOL "Do not use ccache even if it is available")
if (NOT DISABLE_CCACHE)
    find_program(CCACHE_EXECUTABLE ccache)
    if (CCACHE_EXECUTABLE)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_EXECUTABLE})
    endif()
endif()

set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)

find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB_RECURSE SRC_FILES
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    LIST_DIRECTORIES FALSE
    "src/*.cpp" "src/*.h")

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/common"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
    PkgConfig::libusb
    Boost::program_options)
