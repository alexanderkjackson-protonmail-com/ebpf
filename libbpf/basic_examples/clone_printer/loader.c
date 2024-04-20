#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) {
    return vfprintf(stderr, format, args);
}

int main(int argc, char **argv) {
    struct bpf_object *obj;
    struct bpf_program *prog;
    struct bpf_link *link;
    int prog_fd;

    // Set up libbpf errors and debug info
    libbpf_set_print(libbpf_print_fn);

    // Load and verify BPF application
    obj = bpf_object__open("clone_printer.o");
    if (libbpf_get_error(obj)) {
        fprintf(stderr, "Failed to open BPF object\n");
        return 1;
    }

    // Load BPF program into kernel
    if (bpf_object__load(obj)) {
        fprintf(stderr, "Failed to load BPF object\n");
        return 1;
    }

    // Attach kprobe
    prog = bpf_object__find_program_by_name(obj, "clone_printer");
    if (!prog) {
        fprintf(stderr, "Failed to load eBPF program from object.\n");
        return 1;
    }
    link = bpf_program__attach(prog);
    if (libbpf_get_error(link)) {
        fprintf(stderr, "Failed to attach kprobe\n");
        return 1;
    }

    printf("eBPF program loaded and attached. Press Enter to exit...\n");
    getchar();

    // Cleanup
    bpf_link__destroy(link);
    bpf_object__close(obj);

    return 0;
}
