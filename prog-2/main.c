#include <uapi/linux/ptrace.h>

BPF_HASH(start, u32);

int trace_start(struct pt_regs *ctx) {
    u32 pid = bpf_get_current_pid_tgid();
    u64 ts = bpf_ktime_get_ns();
    start.update(&pid, &ts);
    return 0;
}

int trace_end(struct pt_regs *ctx) {
    u32 pid = bpf_get_current_pid_tgid();
    u64 *tsp = start.lookup(&pid);

    if (tsp) {
        u64 delta = bpf_ktime_get_ns() - *tsp;
        bpf_trace_printk("PID %d Read latency: %llu ns\n", pid, delta);
        start.delete(&pid);
    }
    return 0;
}
