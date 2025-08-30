#include <uapi/linux/ptrace.h>
#include <linux/sched.h>

int trace(struct pt_regs *ctx, int dfd, const char __user *filename, int flags, umode_t mode) {
    u32 pid = bpf_get_current_pid_tgid() >> 32;
    char comm[TASK_COMM_LEN];
    char fname[256];

    bpf_get_current_comm(&comm, sizeof(comm));
    bpf_probe_read_user_str(&fname, sizeof(fname), filename);

    bpf_trace_printk("pid=%d comm=%s file=%s\n", pid, comm, fname);
    return 0;
}
