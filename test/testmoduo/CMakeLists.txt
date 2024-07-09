cmake_minimum_required(VERSION 3.0)
project(main)

#编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# # 头文件搜索路径
# include_directories()
# # 配置库文件搜索路径
# link_directories()
# #设置需要编译的源文件列表
# set(SRC_LIST muduo_server.cpp)
# 把指令路径下的所有文件放入变量名SRC_LIST中

# 设置可执行文件存储路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SRC_LIST muduo_server.cpp)


add_executable(server muduo_server.cpp)
# 表示server这个目标程序，需要连接三个库
target_link_libraries(server muduo_net muduo_base pthread)

