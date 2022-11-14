import sys
import time
import usb.core
import usb.util


def main():
    dev = usb.core.find(idVendor=0x14B4, idProduct=0x1004)
    if dev is None:
        raise ValueError('Device is not found')
    size = 10240*1024
    f = open(sys.argv[1], 'wb')
    start_time = time.time()
    databin = dev.read(0x86,size)
    stop_time = time.time()
    f.write(databin)
    times = stop_time - start_time
    speed = size / times / 1024 / 1024
    print("read time = %s speed = %s Mbyte/s" % (times, speed))
    print("finish")
    f.close()


if __name__ == '__main__':
    main()