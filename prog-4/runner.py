
from bcc import BPF
from time import sleep



b = BPF(src_file="main.c")

b.attach_kprobe(event="__x64_sys_read", fn_name="trace_entry")
b.attach_kretprobe(event="__x64_sys_read", fn_name="trace_return")


b.trace_print()
