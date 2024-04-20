#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

char LICENSE[] SEC("license") = "GPL";

// Define the search string
const char search_string[] = "targetstring";

// Define the XDP program that will filter packets
SEC("xdp")
int filter_packets(struct xdp_md *ctx) {
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
    struct iphdr *iph;
    struct tcphdr *tcph;
    char *payload;
    int payload_size;
    
    // Check for Ethernet header
    if ((void *)(eth + 1) > data_end)
        return XDP_PASS;
    
    // Check for IP header
    iph = data + sizeof(*eth);
    if ((void *)(iph + 1) > data_end)
        return XDP_PASS;

    // Check for TCP header
    if (iph->protocol != IPPROTO_TCP)
        return XDP_PASS;
    
    tcph = (void *)iph + (iph->ihl * 4);
    if ((void *)(tcph + 1) > data_end)
        return XDP_PASS;
    
    // Calculate the TCP payload address and size
    payload = (char *)tcph + (tcph->doff * 4);
    payload_size = bpf_ntohs(iph->tot_len) - iph->ihl * 4 - tcph->doff * 4;

    // Check if payload contains the search string
    for (int i = 0; i < payload_size; i++) {
        if ((void *)(payload + i + sizeof(search_string) - 1) > data_end)
            break;
        
        if (__builtin_memcmp(payload + i, search_string, sizeof(search_string) - 1) == 0)
            return XDP_DROP;  // Drop packet if found
    }

    return XDP_PASS;
}
