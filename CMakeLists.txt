#-Configuration-#
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MFC_FLAG 1)
project(SameGame VERSION 1.0.0 LANGUAGES CXX)

#-Add MFC-#
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_AFXDLL)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(src)