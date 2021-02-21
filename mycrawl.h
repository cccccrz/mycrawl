#ifndef MYCRAWL_H
#define MYCRAWL_H
#include <QString>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QQueue>

#include"myparser.h"

class Mycrawl:public QObject
{
    Q_OBJECT
public:
    Mycrawl(QString rootUrl);
    ~Mycrawl();

    inline void setRootURL(QString value){m_rootURL = value;}
    inline void setMachUrl(QString value){m_machURL = value;}

    void get(QString tagName = "a", QString attrName = "href");

private slots:
    void reply_Finished();

private:
    MyParser* m_parser;
    QString m_rootURL;
    QString m_machURL;
    QString m_tagName;
    QString m_attrName;

    QNetworkRequest m_request;  // 请求
    QNetworkReply* m_reply;     // 响应
    QNetworkAccessManager* m_manager;
};

#endif // MYCRAWL_H
