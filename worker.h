#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>
#include "mythread.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

public:
    //开启线程函数
    void start_thread(QString rootURL,uint nWebType);
signals:
    //通知子线程的信号
    void sig_startThread(QString rootURL,uint nWebType);

private:
    MyThread* m_myThread; //线程指针
    QThread* subthread;
public slots:
    //void slot_finishThread(); //线程完成的槽函数

};

#endif // WORKER_H
