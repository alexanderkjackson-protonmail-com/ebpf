# ebpf
This is a pedagogic project and, hopefully, will provide some useful eBPF
programs for tasks such as malware investigation, debugging, or profiling.
The compiler preferred is clang and the build system is cmake.

# Dev environment setup
This project generates eBPF objects and so clang is preferred.
Use a clang language server. Run: ``libbpf/clang_setup.sh`` to generate a
.clangd to access kernel headers for ease of development.

For each project, it is recommended to generate a compile_commands.json with
cmake to enable language server access to that project's source code. Simply
copy from the respective cmake build directory or, if needed, add the argument
``-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`` when you run cmake. 
# Building
## libbpf
Create/enter a build directory and run:
``cmake -D CMAKE_C_COMPILER=clang ..`` followed by ``make``
