#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QQueue>


// 单例 -- 任务表
class MyTable
{
public:
    inline static MyTable* GetInstance()
    {
        static MyTable table;

        return &table;
    }

    inline bool TodoTableIsEmpty(){return m_todo_Table.isEmpty();}
    inline void PushTodoTable(QString value){m_todo_Table.enqueue(value);}
    inline QString PopTodoTable(){return m_todo_Table.dequeue();}
    inline QQueue<QString> GetTodoTable(){return m_todo_Table;}

    inline bool ResultTableIsEmpty(){return m_result_Table.isEmpty();}
    inline void PushResultTable(QString value){m_result_Table.enqueue(value);}
    inline QString PopResultTable(){return m_result_Table.dequeue();}
    inline QQueue<QString> GetResultTable(){return m_result_Table;}

    inline void PushVisitedTable(QString value){m_visited_Table.append(value);}
    inline void PopVisitedTable(QList<QString>::iterator pos){m_visited_Table.erase(pos);}
    inline QList<QString>& GetVisitedTable(){return m_visited_Table;}

private:
    MyTable(){}
    MyTable(const MyTable&);
    MyTable& operator=(const MyTable&);

private:
    QQueue<QString> m_todo_Table;
    QQueue<QString> m_result_Table;
    QList<QString> m_visited_Table;
};

#endif // TABLE_H
