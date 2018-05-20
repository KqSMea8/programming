cmake_minimum_required(VERSION 3.11)
project(hello)

set(src 
  string.cpp
  )
set (header
  SlowObject.h
  )
set (head
  ~/glog/
  ~/glog/src/
  )

link_directories(~/glog/)
include_directories(${head})
add_library( mak SHARED make.cpp make.h)
add_executable(hello ${src} ${header})
target_link_libraries(hello mak libglog.a)
