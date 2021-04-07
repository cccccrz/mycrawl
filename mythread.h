#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QNetworkAccessManager>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();

    static void on_thread_finished_btn_clicked();
    static void on_thread_wait_btn_clicked();
    static void on_thread_continue_btn_clicked();
signals:
    void Threadfinish(); //线程完成时的信号

public slots:
    //需要在线程中执行的槽函数
    void slot_StartMyThread(QString rootURL, uint nWebType);

public:
    //  线程状态标志
    static int thread_flag;
private:
    QNetworkAccessManager* m_manager;
};

#endif // MYTHREAD_H
