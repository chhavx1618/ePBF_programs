Assignment 1: Tracing File Open Syscalls
Task:
• Write an eBPF program (C with BCC) that traces the open() syscall.
• Print the PID, process name, and filename whenever a process opens
a file.
• Loader program must be in Python using BCC APIs.
Test using:
• ls → opens directories.
• cat /etc/passwd → should show /etc/passwd file access.
• touch newfile → should show newfile.
