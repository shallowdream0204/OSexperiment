import time
import threading
from threading import Semaphore

db = Semaphore(1)
Readcount = 0
Writecount = 0
read = Semaphore(1)
Rmutex = Semaphore(1)
Wmutex = Semaphore(1)


def reader(idx, worktime, ftime, starttime):
    time.sleep(starttime)
    print('时间点%.1f  线程%d  发出读申请' % (float(time.time())-ftime, idx))
    read.acquire()
    Rmutex.acquire()
    print('时间点%.1f  线程%d  开始读操作' % (float(time.time())-ftime, idx))
    global Readcount
    if Readcount == 0:
        db.acquire()
    Readcount += 1
    Rmutex.release()
    read.release()
    time.sleep(worktime)
    print('时间点%.1f  线程%d  结束读操作' % (float(time.time())-ftime, idx))
    Rmutex.acquire()
    Readcount -= 1
    if Readcount == 0:
        db.release()
    Rmutex.release()


def writer(idx, worktime, ftime, starttime):
    time.sleep(starttime)
    print('时间点%.1f  线程%d  发出写申请' % (float(time.time())-ftime, idx))
    Wmutex.acquire()
    global Writecount
    if Writecount == 0:
        read.acquire()
    Writecount += 1
    Wmutex.release()
    db.acquire()
    print('时间点%.1f  线程%d  开始写操作' % (float(time.time())-ftime, idx))
    time.sleep(worktime)
    print('时间点%.1f  线程%d  结束写操作' % (float(time.time())-ftime, idx))
    db.release()
    Wmutex.acquire()
    Writecount -= 1
    if Writecount == 0:
        read.release()
    Wmutex.release()

if __name__ == '__main__':
    idx = []
    rwtype = []
    starttime = []
    worktime = []
    with open('input.txt') as file:
        linedata = file.readlines()
        for data in linedata:
            data = data.split()
            idx.append(data[0])  # 线程号
            rwtype.append(data[1])  # 读写类型
            starttime.append(data[2])  # 线程开始时间
            worktime.append(data[3])  # 线程持续时间
    ftime = float(time.time())
    for i in range(len(idx)):
        print('时间点%.1f  线程%d  创建' % (ftime-ftime, int(idx[i])))
        if(rwtype[i] == 'W'):
            thread = threading.Thread(target=writer, args=(
                int(idx[i]), float(worktime[i]), ftime, float(starttime[i])))
            thread.start()
        else:
            thread = threading.Thread(target=reader, args=(
                int(idx[i]), float(worktime[i]), ftime, float(starttime[i])))
            thread.start()
