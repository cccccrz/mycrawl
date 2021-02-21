#include "mycrawl.h"

Mycrawl::Mycrawl(QString rootUrl):m_rootURL(rootUrl)
{
    m_manager = new QNetworkAccessManager(this);
}

Mycrawl::~Mycrawl()
{
    delete m_manager;
}

void Mycrawl::get(QString tagName, QString attrName)
{
    QSslConfiguration cfg = m_request.sslConfiguration();
    cfg.setPeerVerifyMode(QSslSocket::VerifyNone);
    cfg.setProtocol(QSsl::TlsV1SslV3);
    m_request.setSslConfiguration(cfg);

    QVariant user_Agent_chrome = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
                                 AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36";
    m_request.setUrl(QUrl(m_rootURL));
    m_request.setHeader(QNetworkRequest::UserAgentHeader,user_Agent_chrome);

    // 发送 get 请求
    m_reply = m_manager->get(m_request);

    m_tagName = tagName;
    m_attrName = attrName;
    connect(m_reply,&QNetworkReply::finished,this,&Mycrawl::reply_Finished);
}

// 爬取&解析
void Mycrawl::reply_Finished()
{
    if (m_reply->error() != QNetworkReply::NoError)
    {
        qDebug() << m_reply->errorString();
        //释放资源
        m_reply->deleteLater();
        return;
    }
    // 爬取
    QString out;
    out = m_reply->readAll();
    m_reply->deleteLater();

    // 解析
    m_parser = new MyParser(out);
    m_parser->setTagName(m_tagName);
    m_parser->setAttrName(m_attrName);
    m_parser->parse(m_rootURL, m_machURL);

    if (m_parser!=nullptr)
    {
        delete m_parser;
        m_parser = nullptr;
    }
}


