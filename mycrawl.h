#ifndef MYCRAWL_H
#define MYCRAWL_H
#include <QString>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QQueue>

#include"parser.h"

class Mycrawl:public QObject
{
public:
    Mycrawl(QString rootUrl);
    ~Mycrawl();

    inline void setRootURL(QString value){m_rootURL = value;}

    void get(QNetworkAccessManager* manager, uint nWebType);

private slots:
    //void reply_Finished();

private:
    Parser* m_parser;
    QString m_rootURL;
//    QString m_machURL;
//    QString m_tagName;
//    QString m_attrName;

    QNetworkRequest request;  // 请求
    QNetworkReply* reply;     // 响应
};

#endif // MYCRAWL_H
