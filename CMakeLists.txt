cmake_minimum_required(VERSION 3.16)
project(enet_demo)

# find_package(enet REQUIRED HINTS "/usr/local")
set(ENET_LIBRARY enet)

file(GLOB CLI_SOURCE_FILES client/*.cpp)
file(GLOB SER_SOURCE_FILES server/*.cpp)

file(GLOB CLI_HEADER_FILES client/*.h)
file(GLOB SER_HEADER_FILES server/*.h)

include_directories(
  "/usr/local/include"
)

link_directories(
  "/usr/local/lib"
)

add_executable(enet_demo_client ${CLI_SOURCE_FILES} ${CLI_HEADER_FILES})
add_executable(enet_demo_server ${SER_SOURCE_FILES} ${SER_HEADER_FILES})

target_link_libraries(enet_demo_client ${ENET_LIBRARY})
target_link_libraries(enet_demo_server ${ENET_LIBRARY})
