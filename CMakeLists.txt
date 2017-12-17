cmake_minimum_required(VERSION 3.5)
project(StorageYadro)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0")

set(SOURCE_FILES src/main.cpp src/my_functions.h src/dataset_generator.cpp src/server.cpp src/storage_system.cpp src/storage_system.h src/storage.cpp src/storage.h src/client.cpp src/PCIeFabric.cpp src/load_balancer.cpp src/structures.h src/adapter.cpp src/cache.cpp)
add_executable(StorageYadro ${SOURCE_FILES})

include_directories(/home/kenenbek/SimGrid/include)
link_directories(/home/kenenbek/SimGrid/lib)

target_link_libraries(StorageYadro ~/SimGrid/lib/libsimgrid.so)
