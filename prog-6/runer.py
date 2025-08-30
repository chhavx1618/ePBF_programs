from bcc import BPF
import socket, time

b=BPF(src_file="main.c")
fn = b.load_func("f", BPF.SOCKET_FILTER)
s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(3))


print("bytes per protocol")
iface = "wlp8s0"   # change if needed (e.g. "eth0", "enp0s3")
s.bind((iface,0))
b.attach_raw_socket(fn, iface)

names = {1:"ICMP", 6:"TCP", 17:"UDP"}

while 1:
  time.sleep(5)
  for k,v in b["x"].items():
    print(names.get(k.value, str(k.value)), v.value)
