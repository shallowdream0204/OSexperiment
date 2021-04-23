import time  # 该模块用来获取当前时间
import threading  # 该模块用来建立线程
from threading import Semaphore  # 导入Semaphore类用来实现信号量机制

db = Semaphore(1)  # 该信号量实现对临界资源的访问
Readcount = 0  # 统计访问临界资源的读者数目
Writecount = 0  # 统计当前阻塞的写者数目
read = Semaphore(1)  # 该信号量实现写者到来时打断读者线程
Rmutex = Semaphore(1)  # 利用该信号量完成对Readcount的互斥访问
Wmutex = Semaphore(1)  # 利用该信号量完成对Writecount的互斥访问


def reader(idx, worktime, ftime, starttime):  # 读者线程函数（线程号，线程持续时间，最初时间，线程开始时间）
    time.sleep(starttime)  # 等待读者线程申请资源
    print('时间点%.1f  线程%d  发出读申请' % (float(time.time())-ftime, idx))
    read.acquire()  # 申请read
    Rmutex.acquire()  # 申请读者计数器
    print('时间点%.1f  线程%d  开始读操作' % (float(time.time())-ftime, idx))
    global Readcount
    if Readcount == 0:  # 若读者队列为空，则申请临界资源
        db.acquire()
    Readcount += 1  # 线程开始读，读者数+1
    Rmutex.release()  # 释放读者计数器
    read.release()  # 释放read
    time.sleep(worktime)  # 该时间段内线程进行读操作
    print('时间点%.1f  线程%d  结束读操作' % (float(time.time())-ftime, idx))
    Rmutex.acquire()  # 申请读者计数器
    Readcount -= 1
    if Readcount == 0:  # 若读者计数器为空，释放临界资源
        db.release()
    Rmutex.release()  # 释放读者计数器


def writer(idx, worktime, ftime, starttime):  # 写者线程函数（线程号，线程持续时间，最初时间，线程开始时间）
    time.sleep(starttime)  # 等待写者申请资源
    print('时间点%.1f  线程%d  发出写申请' % (float(time.time())-ftime, idx))
    Wmutex.acquire()  # 申请写者计数器
    global Writecount
    if Writecount == 0:  # 写者队列为空，申请read
        read.acquire()
    Writecount += 1
    Wmutex.release()  # 释放写者计数器
    db.acquire()  # 申请临界资源
    print('时间点%.1f  线程%d  开始写操作' % (float(time.time())-ftime, idx))
    time.sleep(worktime)  # 该时间段内，线程进行写操作
    print('时间点%.1f  线程%d  结束写操作' % (float(time.time())-ftime, idx))
    db.release()  # 释放临界资源
    Wmutex.acquire()  # 申请写者计数器
    Writecount -= 1
    if Writecount == 0:  # 写者队列为空则释放read
        read.release()
    Wmutex.release()  # 释放写者计数器


if __name__ == '__main__':
    idx = []  # 线程号
    rwtype = []  # 读写类型
    starttime = []  # 线程开始时间
    worktime = []  # 线程持续时间
    with open('input.txt') as file:  # 读取文件数据
        linedata = file.readlines()  # 按行提取数据
        for data in linedata:
            data = data.split()  # 以空格为分隔将4个数据存入一个list中
            idx.append(data[0])  # 线程号
            rwtype.append(data[1])  # 读写类型
            starttime.append(data[2])  # 线程开始时间
            worktime.append(data[3])  # 线程持续时间
    ftime = float(time.time())  # 获取最初时间（秒数）
    for i in range(len(idx)):  # “几乎同时”创建每一个线程
        print('时间点%.1f  线程%d  创建' % (ftime-ftime, int(idx[i])))
        if(rwtype[i] == 'W'):  # 判断线程类型
            thread = threading.Thread(target=writer, args=(
                int(idx[i]), float(worktime[i]), ftime, float(starttime[i])))  # 创建线程
            thread.start()  # 线程开始
        else:
            thread = threading.Thread(target=reader, args=(
                int(idx[i]), float(worktime[i]), ftime, float(starttime[i])))
            thread.start()
