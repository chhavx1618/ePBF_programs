#include <uapi/linux/ptrace.h>
#include <linux/skbuff.h>
#include <linux/ip.h>

BPF_HASH(cnt, u32, u64);

int kprobe__ip_rcv(struct pt_regs *ctx, struct sk_buff *skb) {
    struct iphdr *ip = (struct iphdr *)(skb->head + skb->network_header);
    u32 proto = ip->protocol;
    u64 zero = 0, *val;

    val = cnt.lookup_or_init(&proto, &zero);
    (*val)++;
    return 0;
}
