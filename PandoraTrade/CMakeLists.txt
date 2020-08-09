cmake_minimum_required (VERSION 3.8)

# set the project name
project (PandoraTrade)

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

set(CMAKE_EXE_LINKER_FLAGS "-no-pie")

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")  # Debug模式下的编译指令
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")         # Release模式下的编译指令

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/../bin/Debug/)    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${PROJECT_SOURCE_DIR}/../bin/Release/) 

add_definitions(-std=c++11)
add_definitions(-D__LINUX__=1 -Dlinux)


include_directories ("../PandoraStrategy/")
include_directories ("../Interface/include/")
include_directories ("../Interface/")

link_directories("${PROJECT_SOURCE_DIR}/../Interface/CTPTradeApiLinux/")

if (CMAKE_BUILD_TYPE STREQUAL DEBUG)   
    add_definitions(-g -DDEBUG)
	link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Debug/")
	link_directories("${PROJECT_SOURCE_DIR}/../bin/Debug/")
elseif (CMAKE_BUILD_TYPE STREQUAL RELEASE)
	add_definitions(-DNDEBUG -O3)
	link_directories("${PROJECT_SOURCE_DIR}/../Interface/lib/Linux/Release/")
	link_directories("${PROJECT_SOURCE_DIR}/../bin/Release/")
endif()

# 获取正在处理的CMakeLists.txt所在的文件夹下面的所有源文件，放到DIR_SRC变量里面
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} DIR_SRC)

# add the executable
add_executable(PandoraTrader ${DIR_SRC})

TARGET_LINK_LIBRARIES(PandoraTrader pthread)
target_link_libraries(PandoraTrader libPandoraStrategy.a libcwPandoraDLL_Linux.a libTinyXml_Linux.a )

target_link_libraries(PandoraTrader "/home/wuchangsheng/project/PandoraTrader/Interface/CTPTradeApiLinux/thostmduserapi_se.so")
target_link_libraries(PandoraTrader "/home/wuchangsheng/project/PandoraTrader/Interface/CTPTradeApiLinux/thosttraderapi_se.so")

