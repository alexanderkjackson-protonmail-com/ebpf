#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    struct bpf_object *obj;
    int map_fd, prog_fd;
    int key = 0;
    long value = 0;

    struct bpf_prog_load_attr prog_load_attr = {
        .prog_type = BPF_PROG_TYPE_XDP,
        .file = "./tcp_monitor.o",
    };

    struct bpf_prog_load_attr

    // Find map file descriptor
    map_fd = bpf_object__find_map_fd_by_name(obj, "search_string");
    if (map_fd < 0) {
        fprintf(stderr, "Failed to find BPF map\n");
        return 1;
    }

    // Initialize map entry
    bpf_map_update_elem(map_fd, &key, &value, BPF_ANY);

    // Attach XDP program
    prog_fd = bpf_program__fd(
            bpf_object__find_program_by_name(
                obj, 
                "xdp_prog"
                )
            );
    // bpf_xdp_attach(prog_fd, 0, XDP_FLAGS_UPDATE_IF_NOEXIST, NULL);
    bpf_xdp_attach(int ifindex, int prog_fd, __u32 flags, const struct bpf_xdp_attach_opts *opts);

    // Work here
    sleep(3); // Allow time for packets to be processed
    
    if (bpf_map_lookup_elem(map_fd, &key, &value) == 0) {
        printf("Value in map: %ld\n", value);
    }

    bpf_object__close(obj);

    return 0;
}
