#include "common.h"
#include "databasecommon.h"
#include <QSqlRecord>

// 初始化
QNetworkAccessManager *Common::m_netManager = new QNetworkAccessManager;

// 数据库连接方式
DBCommon::Control control({ "QMYSQL", "TestDB", "localhost", "crawl", "root", "123456" },
                          { 60 * 1000,        DBCommon::QueryMultiMode, 10});

/* 网站对象创建方法 */
Parser *TTY_CreatParser(uint nWebType, QString html)
{
    Parser *pParser = nullptr;

    switch (nWebType) {
#ifdef DIANYINTT
    case WEBTYPE_DIANYINTT: {
        pParser = CreateParser_DIANYINTT(html);
    } break;
#endif

#ifdef YINHUA
    case WEBTYPE_YINHUA: {
        pParser = CreateParser_YINHUA(html);
    } break;
#endif
    default:
        break;
    }
    return pParser;
}

Common::Common(QObject *parent) : QObject(parent) {}

Common::~Common() {}

QNetworkAccessManager *Common::getNetManager()
{
    return m_netManager;
}

bool Push_Result(QString table, QString url, QString info)
{
    if(table.isNull() || url.isNull() || info.isNull())
    {
        qDebug() <<__FUNCTION__<< "Error" << __LINE__;
        return false;
    }

    auto query(control.query());

    QString sql = QString("insert into %1 values('%2','%3')").arg(table).arg(url).arg(info);
    if(!query->exec(sql))
    {
        //qDebug() <<__FUNCTION__<< "Insert Error" << __LINE__;
        return false;
    }
    return true;
}

bool Push_Visited(QString table, QString url)
{
    if(table.isNull() || url.isNull())
    {
        qDebug() <<__FUNCTION__<< "Error" << __LINE__;
        return false;
    }
    auto query(control.query());

    QString sql = QString("insert into %1 values('%2')").arg(table).arg(url);
    if(!query->exec(sql))
    {
        //qDebug() <<__FUNCTION__<< "Insert Error" << __LINE__;
        return false;
    }
    return true;
}

bool Push_Todo(QString table, QString url)
{
    //return Push_Visited(table, url);
    if(table.isNull() || url.isNull())
    {
        return false;
    }
    auto query(control.query());
    QString sql = QString("insert into %1 values('%2')").arg(table).arg(url);
    if(!query->exec(sql))
    {
       //qDebug() <<__FUNCTION__<< "Insert Error" << __LINE__;
        return false;
    }
    return true;
}

QString Pop_Todo(QString table)
{
    if(table.isNull())
    {
        qDebug() <<__FUNCTION__<< "Error" << __LINE__;
        return QString();
    }

    auto query(control.query());
    QString url;
    QString sql = QString("SELECT * FROM %1").arg(table);

    if (!query->exec(sql))
    {
        //qDebug()<<__FUNCTION__ << "Select Error" << __LINE__;
        return QString();
    }
    query->next();
    url = query->value(0).toString();

    query->clear();

    sql = QString("DELETE FROM %1 WHERE url='%2'").arg(table).arg(url);
    if (!query->exec(sql))
    {
        //qDebug() <<__FUNCTION__<< "Delete Error" << __LINE__;
    }

    return url;
}

int IsExist(QString table, QString value)
{
    if(table.isNull() || value.isNull())
    {
        qDebug() <<__FUNCTION__<< "Error" << __LINE__;
        return -1;
    }

    auto query(control.query());

    QString sql = QString("SELECT * FROM %1 WHERE url='%2'").arg(table).arg(value);
    if (!query->exec(sql))
    {
        qDebug() <<__FUNCTION__<< "Select Error" << __LINE__;
        return -1;
    }

    int ret = query->size();
    return ret;
}

QVector<QVariantList> Select_Info_DB(QString table, QString filter)
{
    if(table.isNull() || filter.isNull())
    {
        qDebug() <<__FUNCTION__<< "Error" << __LINE__;
        return QVector<QVariantList>();
    }

    auto query(control.query());
    QVector<QVariantList> list;
    list.clear();
    QString sql = QString("select * from %1 where %2").arg(table).arg(filter);
    if(!query->exec(sql))
    {
        qDebug() <<__FUNCTION__<< "Select Error" << __LINE__;
        return QVector<QVariantList>();
    }
    //qDebug()<<"sql:"<<sql;
    while(query->next())
    {
        QVariantList sublist;
        QSqlRecord record = query->record();
        for(int i=0; i<record.count(); ++i)
        {
            sublist.append(record.value(i));
        }
        list.append(sublist);
    }
    return list;
}
