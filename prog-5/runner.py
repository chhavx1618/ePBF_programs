from bcc import BPF
from time import sleep
import ctypes as ct

b=BPF(src_file="main.c")
print("packet counter")
while True:
    sleep(5)
    d = b["cnt"]

    def get_val(proto):
        v = d.get(ct.c_uint(proto))
        return v.value if v else 0

    print(f"TCP={get_val(6)}, UDP={get_val(17)}, ICMP={get_val(1)}")

