from bcc import BPF

prog = open("main.c").read()
b = BPF(text=prog)

b.attach_tracepoint(tp="syscalls:sys_enter_read", fn_name="trace_start")
b.attach_tracepoint(tp="syscalls:sys_exit_read", fn_name="trace_end")


print("Tracing read() latency... Ctrl-C to stop.")
count = 0
while count<30:
	try:

		line=b.trace_readline()
		print(line, end="\n")        
		count+=1
	
	except KeyboardInterrupt:
		break
