#include <uapi/linux/ptrace.h>

struct data {
	u32 pid;
	u64 delta;
	char comm[16];
};

BPF_HASH(start, u32, u64);
BPF_PERF_OUTPUT(events);
BPF_HASH(maxlat, u32, u64);

int trace_entry(struct pt_regs *ctx) {

u32 pid = bpf_get_current_pid_tgid();
u64 ts = bpf_ktime_get_ns();
start.update(&pid, &ts);
return 0;
}

int trace_return(struct pt_regs *ctx) {
u32 pid = bpf_get_current_pid_tgid();
u64 *tsp = start.lookup(&pid);
if (!tsp) return 0;

u64 delta = bpf_ktime_get_ns() - *tsp;
start.delete(&pid);

struct data data = {};
data.pid = pid;
data.delta = delta;
bpf_get_current_comm(&data.comm, sizeof(data.comm));
events.perf_submit(ctx, &data, sizeof(data));


    u64 *maxp = maxlat.lookup(&pid);
    if (!maxp || delta > *maxp) {
        maxlat.update(&pid, &delta);
    }
return 0;

}
