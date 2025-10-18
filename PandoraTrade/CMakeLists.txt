cmake_minimum_required(VERSION 3.8)

# cmake_policy(SET CMP0060 NEW)

# set the project name
project(PandoraTrade)

if(APPLE)
    set(IS_MACOS TRUE)

    message(STATUS "Detected macOS system")
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

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)

# link_directories("${PROJECT_SOURCE_DIR}/../Interface/CTPTradeApiLinux/")
# link_directories("/root/projects/PandoraTrader/Interface/CTPTradeApiLinux")
# 根据系统类型设置库路径
if(BUILD_TYPE_UPPER STREQUAL DEBUG)
    add_definitions(-g -DDEBUG)

    if(IS_MACOS)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/MacOS/Debug/")
        message(STATUS "IS_MACOS ${PROJECT_SOURCE_DIR}/../Interface/lib/MacOS/Debug/")
    elseif(IS_UBUNTU)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Ubuntu/Debug/")
        message(STATUS "${PROJECT_SOURCE_DIR}/../Interface/lib/Ubuntu/Debug/")
    else()
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Debug/")
        message(STATUS "${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Debug/")
    endif()

    link_directories("${PROJECT_SOURCE_DIR}/../bin/Debug/")
    message(STATUS "${PROJECT_SOURCE_DIR}/../bin/Debug/")
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

set(CTP_INTERFACE_BASE_DIR "${PROJECT_SOURCE_DIR}/../Interface")

# 根据系统类型设置 CTP 库路径
if(IS_MACOS)
    # 针对 macOS 设置 CTP 库路径

    # 定义 macOS 下 CTP Framework 的完整路径
    set(CTP_TRADE_FRAMEWORK_DIR "${CTP_INTERFACE_BASE_DIR}/CTPTradeApiMacOS")
    set(CTP_MD_FRAMEWORK_DIR "${CTP_INTERFACE_BASE_DIR}/CTPTradeApiMacOS")

    # CTP Framework 内部的实际二进制文件路径
    # set(CTP_TRADE_BIN_PATH "${CTP_TRADE_FRAMEWORK_DIR}/thosttraderapi_se.framework/Versions/A/thosttraderapi_se")
    # set(CTP_MD_BIN_PATH "${CTP_MD_FRAMEWORK_DIR}/thostmduserapi_se.framework/Versions/A/thostmduserapi_se")
    set(CTP_TRADE_BIN_PATH "${CTP_TRADE_FRAMEWORK_DIR}/thosttraderapi_se.framework")
    set(CTP_MD_BIN_PATH "${CTP_MD_FRAMEWORK_DIR}/thostmduserapi_se.framework")

    # 检查 Framework 是否存在，如果不存在则报错
    if(NOT EXISTS "${CTP_TRADE_BIN_PATH}")
        message(FATAL_ERROR "CTP Trade API Framework binary not found at: ${CTP_TRADE_BIN_PATH}")
    endif()

    if(NOT EXISTS "${CTP_MD_BIN_PATH}")
        message(FATAL_ERROR "CTP MD API Framework binary not found at: ${CTP_MD_BIN_PATH}")
    endif()

    # 定义 IMPORTED 库
    # 对于 Framework，它们内部通常是动态库，因此使用 SHARED
    # 如果它们是静态库，则使用 STATIC
    add_library(CTPTradeLIB SHARED IMPORTED)
    set_property(TARGET CTPTradeLIB PROPERTY IMPORTED_LOCATION "${CTP_TRADE_BIN_PATH}")

    # 对于 macOS 框架，通常需要设置 IMPORTED_NO_SONAME
    set_property(TARGET CTPTradeLIB PROPERTY IMPORTED_NO_SONAME TRUE)

    add_library(CTPMdLIB SHARED IMPORTED)
    set_property(TARGET CTPMdLIB PROPERTY IMPORTED_LOCATION "${CTP_MD_BIN_PATH}")
    set_property(TARGET CTPMdLIB PROPERTY IMPORTED_NO_SONAME TRUE)

else()
    # 针对 Linux 系统设置 CTP 库路径

    # 定义 Linux 下 CTP 共享库的完整路径
    set(CTP_LINUX_API_DIR "${CTP_INTERFACE_BASE_DIR}/CTPTradeApiLinux")
    set(CTP_TRADE_SO_PATH "${CTP_LINUX_API_DIR}/thosttraderapi_se.so")
    set(CTP_MD_SO_PATH "${CTP_LINUX_API_DIR}/thostmduserapi_se.so")

    # 检查共享库是否存在，如果不存在则报错
    if(NOT EXISTS "${CTP_TRADE_SO_PATH}")
        message(FATAL_ERROR "CTP Trade API shared library not found at: ${CTP_TRADE_SO_PATH}")
    endif()

    if(NOT EXISTS "${CTP_MD_SO_PATH}")
        message(FATAL_ERROR "CTP MD API shared library not found at: ${CTP_MD_SO_PATH}")
    endif()

    # 为 Linux 系统添加 CTP 库的链接目录
    link_directories("${CTP_LINUX_API_DIR}")

    # 定义 IMPORTED 库
    add_library(CTPTradeLIB SHARED IMPORTED)
    set_property(TARGET CTPTradeLIB PROPERTY IMPORTED_LOCATION "${CTP_TRADE_SO_PATH}")

    add_library(CTPMdLIB SHARED IMPORTED)
    set_property(TARGET CTPMdLIB PROPERTY IMPORTED_LOCATION "${CTP_MD_SO_PATH}")
endif()

add_executable(PandoraTrader ${DIR_SRC})

# 根据系统类型设置 RPATH
if(IS_MACOS)
    # ---
    # # 设置 macOS RPATH
    # ---
    # RPATH 告诉 dyld 在运行时去哪里查找动态库 (Frameworks, .dylib等)

    # 1. BUILD_RPATH: 用于在构建目录中运行可执行文件时查找库
    # 这里设置为 CTP Framework 的父目录，确保 dyld 能找到它们
    # 如果你的 frameworks 会在 /path/to/project/Interface/CTPTradeApiMacOS/
    # 而可执行文件在 /path/to/project/bin/Debug/PandoraTrader
    # 那么 dyld 需要知道去 /path/to/project/Interface/CTPTradeApiMacOS/ 查找
    # 也可以使用 @loader_path/../../Interface/CTPTradeApiMacOS
    set_property(TARGET PandoraTrader PROPERTY BUILD_RPATH
        "${CTP_TRADE_FRAMEWORK_DIR}" # CTP Trade Framework 的父目录
        "${CTP_MD_FRAMEWORK_DIR}" # CTP MD Framework 的父目录
    )

    # 2. INSTALL_RPATH: 用于安装后运行可执行文件时查找库
    # 如果你将应用程序打包成 .app 或者安装到特定目录，通常会将 Frameworks 复制到
    # 应用程序包的 Contents/Frameworks 目录。
    # 那么相对于可执行文件 (Contents/MacOS/PandoraTrader)，Frameworks 就在 ../Frameworks
    # 如果你没有打包成 .app，而是直接发布可执行文件和 Frameworks，
    # 并且 Frameworks 放在可执行文件同级目录的 Frameworks 子目录，那么也用这个。
    # **你可能需要根据实际的部署策略调整这个路径**
    set_property(TARGET PandoraTrader PROPERTY INSTALL_RPATH "@loader_path/../../Interface/CTPTradeApiMacOS")

    # 确保在构建时也应用安装的 RPATH 规则 (对于某些构建系统很有用)
    set_property(TARGET PandoraTrader PROPERTY BUILD_WITH_INSTALL_RPATH TRUE)

else()
    # ---
    # # 设置 Linux RPATH
    # ---
    # RPATH 告诉 ld.so 在运行时去哪里查找动态库 (.so文件)
    # 如果需要从当前目录加载库，请设置环境变量：
    # LD_LIBRARY_PATH=. ./PandoraTrader

    # 1. BUILD_RPATH: 用于在构建目录中运行可执行文件时查找库
    # 可执行文件在 /path/to/project/bin/Debug/PandoraTrader
    # CTP 共享库在 /path/to/project/Interface/CTPTradeApiLinux/
    # 使用 $ORIGIN 相对路径，确保可执行文件能找到共享库
    set_property(TARGET PandoraTrader PROPERTY BUILD_RPATH
        "${CTP_LINUX_API_DIR}" # CTP 共享库的目录
        "$ORIGIN/../../Interface/CTPTradeApiLinux" # 使用相对路径
    )

    # 2. INSTALL_RPATH: 用于安装后运行可执行文件时查找库
    # 对于 Linux，通常将共享库安装到系统库目录或应用程序相对目录
    set_property(TARGET PandoraTrader PROPERTY INSTALL_RPATH
        "$ORIGIN/../../Interface/CTPTradeApiLinux"
        "$ORIGIN/../lib"
    )

    # 确保在构建时也应用安装的 RPATH 规则
    set_property(TARGET PandoraTrader PROPERTY BUILD_WITH_INSTALL_RPATH TRUE)
endif()

TARGET_LINK_LIBRARIES(PandoraTrader pthread)

# 根据系统类型链接不同的库
if(IS_MACOS)
    target_link_libraries(PandoraTrader libPandoraStrategy.a libcwPandoraDLL_MacOS_Universal.a libTinyXml_MacOS_Universal.a)
else()
    # Linux 系统库链接
    target_link_libraries(PandoraTrader libPandoraStrategy.a libcwPandoraDLL_Linux.a libTinyXml_Linux.a)
endif()

# 链接 CTP 库（macOS 和 Linux 都使用相同的目标名称）
target_link_libraries(PandoraTrader CTPTradeLIB)
target_link_libraries(PandoraTrader CTPMdLIB)