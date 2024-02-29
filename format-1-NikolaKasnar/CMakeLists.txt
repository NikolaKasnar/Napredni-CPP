cmake_minimum_required(VERSION 3.13)
project(dz_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(3.dz src/main.cpp)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG master
)

FetchContent_MakeAvailable(fmt)
target_link_libraries(3.dz PRIVATE fmt::fmt)



