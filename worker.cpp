﻿#include "worker.h"
#include <QDebug>

Worker::Worker(QObject *parent) : QObject(parent)
{
    // 创建线程
    subthread = new QThread();
    m_myThread= new MyThread();
    m_myThread->moveToThread(subthread);

    //m_threadId = QThread::currentThreadId();
    // 注册工作信号
    connect(this, &Worker::sig_startThread, m_myThread, &MyThread::slot_StartMyThread);
    //connect(m_myThread, SIGNAL(Threadfinish()), this, SLOT(slot_finishThread()));
    //自动回收
    connect(subthread, &QThread::finished, m_myThread, &QObject::deleteLater);
}

void Worker::start_thread(QString rootURL, uint nWebType)
{
    qDebug() << "main thread : " << QThread::currentThread();
    qDebug() << "main threadID : " << QThread::currentThreadId();
    subthread->start(); //开启线程
    //    if (m_myThread->m_flag) {
    //        subthread->exit();
    //    }
    emit sig_startThread(rootURL, nWebType); //通过信号通知子线程任务
}

//void Worker::slot_finishThread()
//{
//    //处理线程完成的函数
//    //...
//}
