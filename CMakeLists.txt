cmake_minimum_required(VERSION 3.0.0)
project(Compressor VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

file(GLOB src_files CONFIGURE_DEPENDS
     "src/*.cpp"
)

add_executable(Compressor src/Compressor.cpp ${src_files})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)