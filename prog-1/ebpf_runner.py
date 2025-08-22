#!/usr/bin/env python3

from bcc import BPF
from pathlib import Path


#//which cpu core, raw bytes , size of data in bytes
def process_event(cpu, data, size):
	event = bpf["events"].event(data) #//py accessible data struct
	print(f"Process {event.comm.decode()} (PID: {event.pid}, called sys clone")

# read c file as string and compiled into ebpf bytecode
bpf_source = Path('ebpf_probe.c').read_text()

bpf = BPF(text=bpf_source)

#//calls the func as callback when perf ring buffer open
bpf["events"].open_perf_buffer(process_event)
print("Monitoring sys clon events ctrl c for exit")

while True:
	try:
		bpf.perf_buffer_poll() #check new data n call our func as needed
	except KeyboardInterrupt:
		break

