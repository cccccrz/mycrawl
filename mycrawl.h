#ifndef MYCRAWL_H
#define MYCRAWL_H
#include <QString>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QQueue>

#include"myparser.h"

class Mycrawl:public QObject
{
public:
    Mycrawl(QString rootUrl);
    ~Mycrawl();

    inline void setRootURL(QString value){m_rootURL = value;}
    inline void setMachUrl(QString value){m_machURL = value;}

    void get(QNetworkAccessManager* manager, QString tagName = "a", QString attrName = "href");

private slots:
    //void reply_Finished();

private:
    MyParser* m_parser;
    QString m_rootURL;
    QString m_machURL;
    QString m_tagName;
    QString m_attrName;

    QNetworkRequest m_request;  // 请求
    QNetworkReply* m_reply;     // 响应
};

#endif // MYCRAWL_H
