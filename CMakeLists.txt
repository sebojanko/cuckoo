cmake_minimum_required(VERSION 3.12)
project(cuckoo)

set(CMAKE_CXX_STANDARD 17)

add_executable(cuckoo src/main.cpp src/table.cpp src/Bucket.cpp src/FastADocument.cpp src/GeneSequence.cpp)
