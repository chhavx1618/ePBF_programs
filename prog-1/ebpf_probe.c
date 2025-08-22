#include <uapi/linux/ptrace.h> //kernel tracing points
#include <linux/sched.h> //task struct etc kernel process control block n uske constants
#include <bcc/proto.h> //bcc headers n functions for ebpf progs

//struct for the particular data iw ant
struct data_t {
u32 pid;
u32 ppid;
char comm[TASK_COMM_LEN];
};

//perf ring buffer. kernel space and user space talking channel pipe for sending data
BPF_PERF_OUTPUT(events);


//this one attaches kprobe to sys_clone system call. 
//ctx has the registers when syscall was called
int kprobe__sys_clone(void *ctx) {

struct data_t data = {};
struct task_struct *task; //pointer to task_struct

//pointers current process -> this one calls clone()
task = (struct task_struct *)bpf_get_current_task();
data.pid = bpf_get_current_pid_tgid();
data.ppid = task->real_parent->tgid; //Accesses the parent process ID through the task structure. real_parent points to the parent process, and tgid (thread group ID) is essentially the process ID of the parent.
bpf_get_current_comm(&data.comm, sizeof(data.comm));

events.perf_submit(ctx, &data, sizeof(data));
return 0;
//bpf_trace_printk("Hello\n");
//return 0;
}

