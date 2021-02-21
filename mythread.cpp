#include "mythread.h"
#include <QDebug>
#include "mycrawl.h"

MyThread::MyThread(QObject *parent) : QObject(parent) {
}

MyThread::~MyThread(){
}

void MyThread::slot_StartMyThread(QString rootURL, QString machURL,
                                  QString tagName, QString attrName)
{
    //打印线程ID
    qDebug() << "kid " << "threadID : " << QThread::currentThread();

    //...需要执行的内容
    while (1)
    {
        Mycrawl mycrawl(rootURL);
        mycrawl.setMachUrl(machURL);
        mycrawl.get(tagName, attrName);
    }

    //返回线程完成信号
    //emit Threadfinish();
}
