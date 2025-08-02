cmake_minimum_required(VERSION 3.8)

# set the project name
project(PandoraSimulator)

if(APPLE)
    set(IS_MACOS TRUE)
    message(STATUS "Detected macOS system")

    # 检测 macOS 架构
    if(CMAKE_OSX_ARCHITECTURES)
        set(MACOS_ARCH ${CMAKE_OSX_ARCHITECTURES})
        message(STATUS "Using specified architecture: ${MACOS_ARCH}")
    else()
        execute_process(
            COMMAND uname -m
            OUTPUT_VARIABLE MACOS_ARCH
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        message(STATUS "Detected architecture: ${MACOS_ARCH}")
    endif()

    # 根据架构设置 Homebrew 路径
    if(MACOS_ARCH STREQUAL "arm64")
        set(HOMEBREW_PREFIX "/opt/homebrew")
        set(IS_ARM64 TRUE)
        message(STATUS "Using ARM64 (Apple Silicon) Homebrew path: ${HOMEBREW_PREFIX}")
    else()
        # x86_64 或其他架构，使用传统路径
        set(HOMEBREW_PREFIX "/usr/local")
        set(IS_ARM64 FALSE)
        message(STATUS "Using x86_64 (Intel) Homebrew path: ${HOMEBREW_PREFIX}")
    endif()

elseif(UNIX)
    # 检测是否为 Ubuntu 系统
    execute_process(
        COMMAND lsb_release -is
        OUTPUT_VARIABLE LINUX_DISTRO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(LINUX_DISTRO STREQUAL "Ubuntu")
        set(IS_UBUNTU TRUE)
        message(STATUS "Detected Ubuntu system")
    else()
        set(IS_UBUNTU FALSE)
        message(STATUS "Detected non-Ubuntu system: ${LINUX_DISTRO}")
    endif()
endif()

find_package(OpenMP)

if(APPLE)
    # 使用动态设置的 Homebrew 路径配置 OpenMP
    set(LIBOMP_INCLUDE_DIR "${HOMEBREW_PREFIX}/opt/libomp/include")
    set(LIBOMP_LIBRARY_DIR "${HOMEBREW_PREFIX}/opt/libomp/lib")
    set(LIBOMP_LIBRARY_PATH "${LIBOMP_LIBRARY_DIR}/libomp.dylib")

    message(STATUS "OpenMP include directory: ${LIBOMP_INCLUDE_DIR}")
    message(STATUS "OpenMP library path: ${LIBOMP_LIBRARY_PATH}")

    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I${LIBOMP_INCLUDE_DIR}")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY "${LIBOMP_LIBRARY_PATH}")
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I${LIBOMP_INCLUDE_DIR}")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY "${LIBOMP_LIBRARY_PATH}")
    endif()

    # 检查 OpenMP 库是否存在
    if(NOT EXISTS "${LIBOMP_LIBRARY_PATH}")
        message(WARNING "OpenMP library not found at ${LIBOMP_LIBRARY_PATH}")
        message(STATUS "Please install libomp: brew install libomp")
    endif()

    if(NOT EXISTS "${LIBOMP_INCLUDE_DIR}")
        message(WARNING "OpenMP headers not found at ${LIBOMP_INCLUDE_DIR}")
        message(STATUS "Please install libomp: brew install libomp")
    endif()
elseif(UNIX AND NOT APPLE)
    # Linux系统的OpenMP配置
    if(OpenMP_FOUND)
        message(STATUS "Found OpenMP for Linux")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    else()
        message(WARNING "OpenMP not found, trying to set manual flags")

        # 手动设置OpenMP标志（适用于GCC）
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
            set(OpenMP_CXX_LIBRARIES "gomp")
            set(OpenMP_C_LIBRARIES "gomp")
        elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
            set(OpenMP_CXX_LIBRARIES "omp")
            set(OpenMP_C_LIBRARIES "omp")
        endif()
    endif()
endif()

# 检查c++编译器标志，设置c++11支持变量
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# set(CMAKE_EXE_LINKER_FLAGS "-no-pie")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb") # Debug模式下的编译指令
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") # Release模式下的编译指令

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../bin/Debug/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin/Release/)

add_definitions(-std=c++11)
add_definitions(-D__LINUX__=1 -Dlinux)

include_directories("../PandoraStrategy/")
include_directories("../Interface/include/")
include_directories("../Interface/")

set(CTP_INTERFACE_BASE_DIR "${PROJECT_SOURCE_DIR}/../Interface")
string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)

# 根据系统类型设置库路径
if(BUILD_TYPE_UPPER STREQUAL DEBUG)
    add_definitions(-g -DDEBUG)

    if(IS_MACOS)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/MacOS/Debug/")
    elseif(IS_UBUNTU)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Ubuntu/Debug/")
    else()
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Debug/")
    endif()

    link_directories("${PROJECT_SOURCE_DIR}/../bin/Debug/")
elseif(BUILD_TYPE_UPPER STREQUAL RELEASE)
    add_definitions(-DNDEBUG -O3)

    if(IS_MACOS)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/MacOS/Release/")
    elseif(IS_UBUNTU)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Ubuntu/Release/")
    else()
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Release/")
    endif()

    link_directories("${PROJECT_SOURCE_DIR}/../bin/Release/")
endif()

# 获取正在处理的CMakeLists.txt所在的文件夹下面的所有源文件，放到DIR_SRC变量里面
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} DIR_SRC)

# add the executable
add_executable(PandoraSimulator ${DIR_SRC})

TARGET_LINK_LIBRARIES(PandoraSimulator pthread)

if(APPLE)
    target_link_libraries(PandoraSimulator libPandoraStrategy.a libcwPandoraDLL_MacOS_Universal.a libTinyXml_MacOS_Universal.a)
    target_link_libraries(PandoraSimulator ${OpenMP_omp_LIBRARY})
else()
    target_link_libraries(PandoraSimulator libPandoraStrategy.a libcwPandoraDLL_Linux.a libTinyXml_Linux.a)

    # Linux系统的OpenMP链接
    if(OpenMP_FOUND AND TARGET OpenMP::OpenMP_CXX)
        target_link_libraries(PandoraSimulator OpenMP::OpenMP_CXX)
    elseif(OpenMP_CXX_LIBRARIES)
        target_link_libraries(PandoraSimulator ${OpenMP_CXX_LIBRARIES})
    else()
        # 手动链接OpenMP库
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
            target_link_libraries(PandoraSimulator gomp)
        elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            target_link_libraries(PandoraSimulator omp)
        endif()
    endif()
endif()
