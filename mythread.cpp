#include "mythread.h"
//#include "databaseop.h"
//#include <QMutexLocker>
#include "mycrawl.h"
#include "common.h"



#ifndef MYSQL
QMutex g_mutex;
#endif
uint MyThread::thread_flag = 0; // 1 表示退出

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

MyThread::~MyThread()
{
    delete m_manager;
}

/* 爬虫任务线程工作函数 */
void MyThread::slot_StartMyThread(QString rootURL,uint nWebType)
{
    //打印线程ID
    //qDebug() << "kid  thread : " << QThread::currentThread();
    qDebug() << "kid  threadID : " << QThread::currentThreadId() <<"url:"<<rootURL;

    // 爬取根URL，获取任务列表
#ifdef MYSQL
    //Mycrawl mycrawl(rootURL);
    //mycrawl.get(m_manager, nWebType);
#else
    Mycrawl mycrawl(rootURL);
    mycrawl.get(m_manager, nWebType);
#endif
    // 开始任务
    while (1)
    {
        // 从队列取任务
        QString todo_url;
        bool isRepeat = false;

        // URL去重
        do
        {
#ifdef MYSQL
            //todo_url = DatabaseOp::Todo_PoP(TABLE_TODO_YINHUA);
            todo_url = Pop_Todo(TABLE_TODO_YINHUA);
            if (todo_url.isNull() || thread_flag==1)
            {
                qDebug() << "work over";
                //continue;   // 多线程
                return; // 任务完成
            }

            //if (DatabaseOp::isExist(TABLE_VISITED_YINHUA, todo_url))
            if (IsExist(TABLE_VISITED_YINHUA, todo_url))    // ！=0 访问表中存在
            {
                qDebug()<<"continue";
                continue;
            }
#else
            if(MyTable::GetInstance()->TodoTableIsEmpty())
            {
                //qDebug()<<"work over";
                return; // 任务完成
            }
            g_mutex.lock();
            todo_url = MyTable::GetInstance()->PopTodoTable();
            g_mutex.unlock();
            // URL 去重
            for(auto i : MyTable::GetInstance()->GetVisitedTable())
            {
                // 如果重复，跳出取下一个
                if(todo_url.compare(i)==0)
                {
                    isRepeat = true;
                    break;
                }
            }
            if(isRepeat)
            {
                isRepeat = false;
                continue;
            }
#endif
        }while(isRepeat);// 爬取不重复url

#ifdef MYSQL
        //DatabaseOp::Visited_Push(TABLE_VISITED_YINHUA, todo_url);
        Push_Visited(TABLE_VISITED_YINHUA, todo_url);
        Mycrawl todo_crawl(todo_url);
        todo_crawl.get(m_manager, nWebType);
#else
        {
            QMutexLocker mutexlocker(&g_mutex);
            MyTable::GetInstance()->PushVisitedTable(todo_url);

            //URL未使用，爬虫工作
            Mycrawl todo_crawl(todo_url);
            todo_crawl.get(m_manager, nWebType);
        }
#endif
        // 休息1S
        //QThread::sleep(10);
    }

    //返回线程完成信号
    //emit Threadfinish();
}

void MyThread::on_thread_finished_btn_clicked()
{
    thread_flag = 1;
}
