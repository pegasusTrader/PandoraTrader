cmake_minimum_required (VERSION 3.8)

#cmake_policy(SET CMP0060 NEW)

# set the project name
project (PandoraTrade)

# 检测是否为 Ubuntu 系统
execute_process(
    COMMAND lsb_release -is
    OUTPUT_VARIABLE LINUX_DISTRO
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 设置系统相关变量
if(LINUX_DISTRO STREQUAL "Ubuntu")
    set(IS_UBUNTU TRUE)
    message(STATUS "Detected Ubuntu system")
else()
    set(IS_UBUNTU FALSE)
    message(STATUS "Detected non-Ubuntu system: ${LINUX_DISTRO}")
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

#set(CMAKE_EXE_LINKER_FLAGS "-no-pie")

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")  # Debug模式下的编译指令
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")         # Release模式下的编译指令

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/../bin/Debug/)    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${PROJECT_SOURCE_DIR}/../bin/Release/) 

add_definitions(-std=c++11)
add_definitions(-D__LINUX__=1 -Dlinux)


include_directories ("../PandoraStrategy/")
include_directories ("../Interface/include/")
include_directories ("../Interface/")

#link_directories("${PROJECT_SOURCE_DIR}/../Interface/CTPTradeApiLinux/")
#link_directories("/root/projects/PandoraTrader/Interface/CTPTradeApiLinux")

if (CMAKE_BUILD_TYPE STREQUAL DEBUG)   
    add_definitions(-g -DDEBUG)
    if(IS_UBUNTU)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Ubuntu/Debug/")
    else()
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Debug/")
    endif()
    link_directories("${PROJECT_SOURCE_DIR}/../bin/Debug/")
elseif (CMAKE_BUILD_TYPE STREQUAL RELEASE)
    add_definitions(-DNDEBUG -O3)
    if(IS_UBUNTU)
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Ubuntu/Release/")
    else()
        link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Release/")
    endif()
    link_directories("${PROJECT_SOURCE_DIR}/../bin/Release/")
endif()


# 获取正在处理的CMakeLists.txt所在的文件夹下面的所有源文件，放到DIR_SRC变量里面
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} DIR_SRC)

# add the executable
add_library(CTPTradeLIB UNKNOWN IMPORTED)
set_property(TARGET CTPTradeLIB PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../Interface/CTPTradeApiLinux/thosttraderapi_se.so")

add_library(CTPMdLIB UNKNOWN IMPORTED)
set_property(TARGET CTPMdLIB PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../Interface/CTPTradeApiLinux/thostmduserapi_se.so")

add_executable(PandoraTrader ${DIR_SRC})

TARGET_LINK_LIBRARIES(PandoraTrader pthread)
target_link_libraries(PandoraTrader libPandoraStrategy.a libcwPandoraDLL_Linux.a libTinyXml_Linux.a )

target_link_libraries(PandoraTrader CTPTradeLIB)
target_link_libraries(PandoraTrader CTPMdLIB)