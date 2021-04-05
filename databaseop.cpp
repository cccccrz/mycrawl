#include "databaseop.h"
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMutexLocker>

QMutex db_mutex;

QSqlQuery DatabaseOp::query;

DatabaseOp::DatabaseOp(QObject *parent) : QObject(parent) {}

bool DatabaseOp::openDatabase(QString hostName, QString dbName, QString user, QString passwd)
{
    if (hostName.isNull() || dbName.isNull() || user.isNull() || passwd.isNull()) {
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        return true;
    }
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(passwd);
    //db.setPort(port);

    // open db
    bool bl = db.open();
    if (bl == false) {
        QMessageBox::critical(nullptr, "ERROR", db.lastError().text());
        return false;
    }
    query = QSqlQuery(db);
    return true;
}

void DatabaseOp::closeDatabase()
{
    // 得到实例
    QSqlDatabase base = QSqlDatabase::database();
    // 关闭数据库
    base.close();
}

bool DatabaseOp::isExist(QString table, QString value, QString column)
{
    if(table.isNull() || value.isNull() || column.isNull())
    {
        return false;
    }
    //db_mutex.lock();

    QMutexLocker locker(&db_mutex);

    QString sql = QString("SELECT %1 FROM %2 WHERE %1='%3'").arg(column).arg(table).arg(value);
    //QSqlQuery query;
    if (!query.exec(sql))
    {
        //db_mutex.unlock();
        //qDebug() << "select err, sql:" << sql;
        return false;
    }

    //db_mutex.unlock();
    return query.size();
}

QVector<QVariantList> DatabaseOp::selectDatabase(QString table, QString filter)
{
    if(table.isNull() || filter.isNull())
    {
        qDebug()<<"select result err: input params err";
        return QVector<QVariantList>();
    }

    QSqlQuery query;
    QVector<QVariantList> list;
    list.clear();
    QString sql = QString("select * from %1 where %2").arg(table).arg(filter);
    if(!query.exec(sql))
    {
        qDebug()<<"select err :sql"<<sql;
        return QVector<QVariantList>();
    }
    qDebug()<<"sql:"<<sql;
    while(query.next())
    {
        QVariantList sublist;
        QSqlRecord record = query.record();
        for(int i=0; i<record.count(); ++i)
        {
            sublist.append(record.value(i));
        }
        list.append(sublist);
    }
    return list;
}

//QVariantList values;
//values << value1 << value2;
bool DatabaseOp::insertDB(QString table, QVariantList values)
{
    QStringList valList;
    for (int i = 0; i < values.size(); ++i) {
        if (values.at(i).type() == QVariant::String) {
            valList += ("'" + values.at(i).toString() + "'");
        } else if (values.at(i).type() == QVariant::DateTime) {
            //QString str = QString("to_date('%1', 'yyyy-mm-dd hh24:mi:ss')")
            //.arg(values.at(i).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            QString str = QString("date_format('%1', '%Y-%c-%d %h:%i:%s')")
                              .arg(values.at(i).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            valList += str;
        } else {
            valList += values.at(i).toString();
        }
    }
    QString myValues = valList.join(",");

    QString sql = QString("INSERT INTO %1 VALUES(%2)").arg(table).arg(myValues);
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    // 开启事务
    db.transaction();
    if (!query.exec(sql))
    {
        //qDebug() << "insert fail, sql:" << sql;
        return false;
    }
    db.commit();

    return true;
}

bool DatabaseOp::insertDB(QString table, QString value)
{
    QString sql = QString("INSERT INTO %1 VALUES('%2')").arg(table).arg(value);
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    // 开启事务
    db.transaction();
    if (!query.exec(sql))
    {
        //qDebug() << "insert fail, sql:" << sql;
        return false;
    }
    db.commit();

    return true;
}

bool DatabaseOp::deleteDB(QString table, QString filter)
{
    if(table.isNull() || filter.isNull())
    {
        return false;
    }

    //db_mutex.lock();

    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    QString sql = QString("DELETE FROM %1 WHERE %2").arg(table).arg(filter);

    db.transaction();
    if (query.exec(sql))
    {
        db.commit();
        //db_mutex.unlock();

        return true;
    } else
    {
        //db_mutex.unlock();
        //db.rollback();
        qDebug() << "delete fail, sql:" << sql;
        return false;
    }
}

bool DatabaseOp::Result_Push(QString table, QString url, QString info)
{
    if(table.isNull() || url.isNull() || info.isNull())
    {
        return false;
    }
    QVariantList values;
    values << url << info;
    return insertDB(table, values);
}

bool DatabaseOp::Visited_Push(QString table, QString url)
{
    if(table.isNull() || url.isNull())
    {
        return false;
    }
    return insertDB(table, url);
}

bool DatabaseOp::Todo_Push(QString table, QString url)
{
    if(table.isNull() || url.isNull())
    {
        return false;
    }
    return insertDB(table, url);
}

QString DatabaseOp::Todo_PoP(QString table)
{
    if(table.isNull())
    {
        return QString();
    }
    //db_mutex.lock();

    QMutexLocker locker(&db_mutex);
    //QSqlQuery query;
    QString url;
    QString sql = QString("SELECT * FROM %1").arg(table);

    if (!query.exec(sql))
    {
        //qDebug() << "select err, sql:" << sql;
        //db_mutex.unlock();

        return QString();
    }
    query.next();
    url = query.value(0).toString();
    deleteDB(table, "url='" + url + "'");
    //db_mutex.unlock();

    return url;
}
