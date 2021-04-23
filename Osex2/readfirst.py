import time  # 该模块用来获取当前时间
import threading  # 该模块用来建立线程
from threading import Semaphore  # 导入Semaphore类用来实现信号量机制

db = Semaphore(1)  # 利用该信号量实现对临界资源的访问
Readcount = 0  # 该计数器统计访问临界资源的读者数目
Rmutex = Semaphore(1)  # 利用该信号量完成对计数器资源的互斥访问


def writer(idx, worktime, ftime, starttime):  # 写者线程函数（线程号，线程持续时间，最初时间，线程开始时间）
    time.sleep(starttime)  # 等待写者线程申请资源
    print('时间点%.1f  线程%d  发出写申请' % (float(time.time())-ftime, idx))
    db.acquire()  # 申请访问临界资源
    print('时间点%.1f  线程%d  开始写操作' % (float(time.time())-ftime, idx))
    time.sleep(worktime)  # 该时间段内线程进行写操作
    print('时间点%.1f  线程%d  结束写操作' % (float(time.time())-ftime, idx))
    db.release()  # 释放临界资源


def reader(idx, worktime, ftime, starttime):  # 读者线程函数（线程号，线程持续时间，最初时间，线程开始时间）
    time.sleep(starttime)  # 等待读者线程申请资源
    print('时间点%.1f  线程%d  发出读申请' % (float(time.time())-ftime, idx))
    Rmutex.acquire()  # 申请读者计数器
    global Readcount
    if Readcount == 0:  # 若读者队列为空，则申请临界资源
        db.acquire()
    print('时间点%.1f  线程%d  开始读操作' % (float(time.time())-ftime, idx))
    Readcount += 1  # 线程开始读，读者数量+1
    Rmutex.release()  # 释放读者计数器资源
    time.sleep(worktime)  # 该时间段内线程进行读操作
    print('时间点%.1f  线程%d  结束读操作' % (float(time.time())-ftime, idx))
    Rmutex.acquire()  # 申请读者计数器资源
    Readcount -= 1
    if Readcount == 0:  # 若读者数量为0，释放临界资源
        db.release()
    Rmutex.release()  # 释放读者计数器资源


if __name__ == '__main__':
    idx = []  # 线程号
    rwtype = []  # 线程类型
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
