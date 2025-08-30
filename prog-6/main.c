#include <uapi/linux/if_ether.h>
#include <uapi/linux/ip.h>
BPF_HASH(x, u8, u64);
int f(struct __sk_buff *skb) {
  struct ethhdr eth;
  struct iphdr ip;
  if (bpf_skb_load_bytes(skb, 0, &eth, sizeof(eth)) < 0) return 0;
  if (eth.h_proto != htons(ETH_P_IP)) return 0;
  if (bpf_skb_load_bytes(skb, sizeof(eth), &ip, sizeof(ip)) < 0) return 0;
  u8 p = ip.protocol;
  u64 n = bpf_ntohs(ip.tot_len);
  u64 *v = x.lookup(&p);
  if (v) __sync_fetch_and_add(v, n);
  else x.update(&p, &n);
  return 0;
}
