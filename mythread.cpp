#include "mythread.h"
#include <QDebug>
#include "mycrawl.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

MyThread::~MyThread()
{
    delete m_manager;
}

void MyThread::slot_StartMyThread(QString rootURL, QString machURL,
                                  QString tagName, QString attrName)
{
    //打印线程ID
    qDebug() << "kid " << "threadID : " << QThread::currentThread();

    // 爬取根URL，获取任务列表
    Mycrawl mycrawl(rootURL);
    mycrawl.setMachUrl(machURL);
    mycrawl.get(m_manager,tagName, attrName);

    // 开始任务
    while (1)
    {
        if(MyTable::GetInstance()->GetTodoTable().isEmpty())
        {
            qDebug()<<"work over"<<endl;
            break;
        }
        // 从队列取任务
        QString todo_url;
        bool isRepeat = false;

        // URL去重
        do
        {
            todo_url = MyTable::GetInstance()->PopTodoTable();

            for(auto i : MyTable::GetInstance()->GetVisitedTable())
            {
                // 如果重复，取下一个任务
                if(todo_url.compare(i)==0)
                {
                    isRepeat = true;
                    break;
                }
            }
        }while(isRepeat);

        MyTable::GetInstance()->PushVisitedTable(todo_url);

        //URL未使用，爬虫工作
        Mycrawl todo_crawl(todo_url);
        todo_crawl.setMachUrl(machURL);
        todo_crawl.get(m_manager, tagName, attrName);
    }


    //返回线程完成信号
    //emit Threadfinish();
}
