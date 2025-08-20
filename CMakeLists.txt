cmake_minimum_required(VERSION 3.10)
project(packet_counter C)

set(CMAKE_C_STANDARD 11)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add executable with ALL source files
add_executable(packet_counter
        src/main.c
        src/packet_parser.c
)

# Link with libpcap
target_link_libraries(packet_counter pcap)