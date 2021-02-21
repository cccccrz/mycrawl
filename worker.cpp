#include "worker.h"
#include <QDebug>

Worker::Worker(QObject *parent) : QObject(parent)
{
    // 创建线程
    subthread = new QThread();
    m_myThread= new MyThread();
    m_myThread->moveToThread(subthread);

    // 注册工作信号
    connect(this, SIGNAL(sig_startThread()), m_myThread, SLOT(slot_StartMyThread()));
    //connect(m_myThread, SIGNAL(Threadfinish()), this, SLOT(slot_finishThread()));
    //自动回收
    connect(subthread, &QThread::finished, m_myThread, &QObject::deleteLater);
}

void Worker::start_thread(QString rootURL, QString machURL,
                          QString tagName, QString attrName)
{
    qDebug() << "main threadID : " << QThread::currentThread();
    subthread->start(); //开启线程
    emit sig_startThread(rootURL, machURL, tagName, attrName); //通过信号通知子线程任务
}

//void Worker::slot_finishThread()
//{
//    //处理线程完成的函数
//    //...
//}
