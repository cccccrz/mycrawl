#include "mycrawl.h"
#include "common.h"
#include <QDebug>
#include <QMessageBox>

Mycrawl::Mycrawl(QString rootUrl):m_rootURL(rootUrl)
{    
}

Mycrawl::~Mycrawl()
{
}

void Mycrawl::get(QNetworkAccessManager* manager, uint nWebType)
{
    if(m_rootURL.isNull())
    {
        return;
    }
//    QSslConfiguration cfg = m_request.sslConfiguration();
//    cfg.setPeerVerifyMode(QSslSocket::VerifyNone);
//    cfg.setProtocol(QSsl::TlsV1SslV3);
//    m_request.setSslConfiguration(cfg);

    m_request.setUrl(QUrl(m_rootURL));

    QVariant user_Agent_chrome = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
                                 AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36";
    m_request.setHeader(QNetworkRequest::UserAgentHeader,user_Agent_chrome);
    m_request.setRawHeader("Accept-Language", "zh-CN,zh");

    // 发送 get 请求
    m_reply = manager->get(m_request);

    qDebug()<<"crawl "<<m_rootURL<<"......";
    //connect(m_reply,&QNetworkReply::finished,this,&Mycrawl::reply_Finished);

    // 事件循环，同步爬取
    QEventLoop loop;
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray replyData = m_reply->readAll();
    int statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QVariant redirectAttr = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        if (m_reply->error()
        || 300 == statusCode //状态码300 Multiple Choices，既不是错误也不算重定向，应该是qt bug
        || !redirectAttr.isNull())
    {
//        QString errString = m_reply->error() ? m_reply->errorString() : QString("发生重定向(%1)，不允许此情况").arg(statusCode);
//        QMessageBox::critical(nullptr, "网络异常",
//                              QString("发送get请求时出现错误：\n网址：%1\n错误信息：%2").arg(m_reply->request().url().toDisplayString(), errString));
        replyData.clear();
        m_reply->deleteLater();
        m_reply = nullptr;
        return;
    }
    qDebug()<<"done!";

    //创建对应网站的解析器，解析
    m_parser = TTY_CreatParser(nWebType, replyData);
    m_parser->Parse();

    //释放资源
    if(m_parser!=nullptr)
    {
        delete  m_parser;
        m_parser = nullptr;
    }
    m_reply->deleteLater();
    m_reply = nullptr;
}

// 爬取&解析
//void Mycrawl::reply_Finished()
//{
//    if (m_reply->error() != QNetworkReply::NoError)
//    {
//        qDebug() << m_reply->errorString();
//        //释放资源
//        m_reply->deleteLater();
//        return;
//    }
//    qDebug()<<"done!"<<endl;

//    // 爬取
//    QByteArray out = m_reply->readAll();
//    m_reply->deleteLater();

//    // 解析
//    m_parser = new MyParser(out);
//    m_parser->setTagName(m_tagName);
//    m_parser->setAttrName(m_attrName);
//    m_parser->parse(m_rootURL, m_machURL);

//    if (m_parser!=nullptr)
//    {
//        delete m_parser;
//        m_parser = nullptr;
//    }
//}


