# eBPF Program

This program is written to record the sysclone syscalls in a linux based system.

## Components

It has two components - 

1. eBPF_probe.c

This defines a struct for recording process's data (pid, etc.). It has a probe attatched for 'sysclone' calls, and records them in a buffer.

2. eBPF_runner.py

This files reads the data incoming from the source c file and stores it and prints it as needed for the user.

## Running

Overall, these two files together record and display the sysclone events happening inside the system LIVE.


## Submitted By
Chhavi Arora
202351023
