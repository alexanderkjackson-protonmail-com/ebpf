# ebpf
This is a pedagogic project and, hopefully, will provide some useful eBPF
programs for tasks such as malware investigation, debugging, or profiling.
The compiler preferred is clang and the build system is cmake. The bpftrace
directory contains simple bpftrace scripts; it's a higher-level language
interface and probably what you're looking for unless you're super fancy.

This project will be scatterbrained - please forgive me. For more organized
learning, check out the below:
* https://www.brendangregg.com/blog/2019-01-01/learn-ebpf-tracing.html
* https://github.com/lizrice/learning-ebpf
* https://github.com/libbpf/libbpf-bootstrap (
* https://ebpf.io/get-started/#books

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
## Debugging
``bpftool`` is useful for checking programs loaded and maps. Ensure that debugfs
is mounted. Run: ``sudo mount -t debugfs debugfs /sys/kernel/debug`` if not.
``sudo cat /sys/kernel/debug/tracing/trace_pipe`` to watch bpf_printk() output.

# BPFTRACE!
The bpftrace directory contains scripts that can simply be run with bpftrace - a
much faster, more practical interface for basic eBPF tasks that are useful to a
systems administrator.

# TODO
Need to set this up so it's more like: https://github.com/libbpf/libbpf-bootstrap
* Need to add submodules with dependencies so these can be readily run.
* Ideally make a generic BPF program with common features commented out so one
  program can be used to make derivatives (like bootstrap from
  libbpf-bootstrap).
* Generate and use skeleton files from bpftool.
