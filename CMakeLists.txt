cmake_minimum_required(VERSION 3.5)
project(hanzi2pinyin)
set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../libs)

add_library(hanzi2pinyin SHARED src/transfer.cpp)
add_executable(main src/main.cpp)

include_directories(include)
target_include_directories(hanzi2pinyin PUBLIC include)
target_include_directories(main PUBLIC ./)
# still don't know why following two does not work
#target_include_directories(main PUBLIC ./include)
#target_include_directories(main PUBLIC include)

target_link_libraries(main hanzi2pinyin)
# without upper line will error like  "undefined reference to `Transfer::Transfer()'"


find_package(Boost REQUIRED COMPONENTS filesystem log system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(hanzi2pinyin ${Boost_LIBRARIES})
    add_definitions(-DBOOST_LOG_DYN_LINK)
endif ()
