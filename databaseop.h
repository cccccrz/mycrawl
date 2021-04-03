#ifndef DATABASEOP_H
#define DATABASEOP_H

#include <QObject>

class DatabaseOp : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseOp(QObject *parent = nullptr);

    // 打开数据库
    static bool openDatabase(QString hostName, QString dbName, QString user, QString passwd);
    // 关闭数据库
    static void closeDatabase();
    //
    static bool Result_Push(QString table, QString url, QString info);
    static bool Visited_Push(QString table, QString url);
    static bool Todo_Push(QString table, QString url);
    static QString Todo_PoP(QString table);

    // 查询表中是否存在value
    static bool isExist(QString table, QString value, QString column = "url");

private:
    // 添加数据
    static bool insertDB(QString table, QVariantList value);
    static bool insertDB(QString table, QString value);
    // 删除数据
    static bool deleteDB(QString table, QString filter);

private:
    QString m_dbType;
};

#endif // DATABASEOP_H
