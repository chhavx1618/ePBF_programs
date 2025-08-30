from bcc import BPF

b = BPF(src_file="main.c")

b.attach_kprobe(event="__x64_sys_openat", fn_name="trace")

print("%-6s %-16s %s" % ("PID", "COMM", "FILENAME"))

count=0
while True:
	try:

		
		(task, pid, cpu, flags, ts, msg) = b.trace_fields(nonblocking=False)
#		if "ls" in msg or "cat" in msg or "touch" in msg:
		print(msg)
		count+=1
		if count>20:
			exit()
	except KeyboardInterrupt:
		break	
