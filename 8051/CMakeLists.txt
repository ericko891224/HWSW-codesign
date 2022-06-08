cmake_minimum_required(VERSION 3.16)
project(8051_iss)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH E:/systemc-2.3.3/SystemC)

include_directories(${CMAKE_PREFIX_PATH}/include)
find_package(SystemCLanguage CONFIG REQUIRED)
link_directories(${CMAKE_PREFIX_PATH}/lib)
file(GLOB 8051_SRC
     "*.h"
     "*.cpp"
)
add_executable(8051_iss ${8051_SRC})
target_link_libraries(8051_iss SystemC::systemc)