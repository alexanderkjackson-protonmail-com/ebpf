cmake_minimum_required(VERSION 3.10)
project(eBPFExample)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Enable verbose output
set(CMAKE_VERBOSE_MAKEFILE ON)

# Optional: Generate compile_commands.json for clangd and other tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include libbpf library
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBBPF REQUIRED libbpf)

# Include headers and libraries
include_directories(${LIBBPF_INCLUDE_DIRS})
link_directories(${LIBBPF_LIBRARY_DIRS})

# Target for the eBPF program
add_library(clone_printer OBJECT clone_printer.c)

add_custom_target(copy_ebpf_object ALL
    COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_OBJECTS:clone_printer>
    ${CMAKE_BINARY_DIR}/clone_printer.o
    DEPENDS clone_printer)

# Target for eBPF (compile only, no linking)
target_compile_options(clone_printer PRIVATE -O2 -target bpf)
set_target_properties(clone_printer PROPERTIES LINKER_LANGUAGE C)

# Target for the user-space loader program
add_executable(loader loader.c)
target_link_libraries(loader ${LIBBPF_LIBRARIES})
