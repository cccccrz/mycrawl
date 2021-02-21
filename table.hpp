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

    inline QQueue<QString> GetTodoTable(){return m_todo_Table;}
    inline QQueue<QString> GetResultTable(){return m_result_Table;}
    inline QVector<QString> GetVisitedTable(){return m_visited_Table;}

private:
    MyTable(){}
    MyTable(const MyTable&);
    MyTable& operator=(const MyTable&);

private:
    QQueue<QString> m_todo_Table;
    QQueue<QString> m_result_Table;
    QVector<QString> m_visited_Table;
};

#endif // TABLE_H
