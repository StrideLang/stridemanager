cmake_minimum_required(VERSION 3.13) 
project(StrideManager)  

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MANAGER_SRC
  main.cpp
)

add_executable(stridemngr ${MANAGER_SRC})
target_link_libraries(stridemngr StrideCodegen StrideParser)
