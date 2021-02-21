#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();

signals:
    //void Threadfinish(); //线程完成时的信号
public slots:
    //需要在线程中执行的槽函数
    void slot_StartMyThread(QString rootURL, QString machURL,
                            QString tagName, QString attrName);
};

#endif // MYTHREAD_H
