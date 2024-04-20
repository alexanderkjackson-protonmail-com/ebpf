#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("kprobe/__x64_sys_clone")
int clone_printer(struct pt_regs *ctx) {
    bpf_printk("Clone called!\n");
    return 0;
}

char _license[] SEC("license") = "GPL";
