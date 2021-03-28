#include "dianyinttparser.h"

#define TAGNAME "a"
#define ATTRNAME "href"
#define ROOTURL "https://yingtt.com"
#define MATCHURL "/vodplay/"

extern Parser* DIANYINTT_CreateParser(QString html)
{
    return (new DianyinttParser(html));
}

DianyinttParser::DianyinttParser(QString html)
{
    m_dom = m_parser.parseTree(html.toStdString());
    m_it = m_dom.begin();
    m_endit = m_dom.end();

    m_tagName = TAGNAME;
    m_attrName = ATTRNAME;
    m_rootURL = ROOTURL;
    m_matchURL = MATCHURL;
}

DianyinttParser::~DianyinttParser()
{

}

void DianyinttParser::Parse()
{
    for (; m_it != m_endit; ++m_it) {
        if (!m_it->isTag())
            continue;
        if ((_stricmp(m_it->tagName().c_str(), m_tagName.toUtf8().data()) == 0))
        {
            //qDebug()<<"[parse]:"<<m_it->text().c_str()<<endl;
            //匹配子标签
            m_it->parseAttributes();
            if (m_it->attribute(m_attrName.toUtf8().data()).first)
            {
                m_resURL = QString::fromStdString( m_it->attribute(m_attrName.toUtf8().data()).second);
                // 匹配结果URL,加入队列
                if (m_resURL.toStdString().compare(0, (size_t)m_matchURL.length(), m_matchURL.toStdString()) == 0)
                {
                    QString resurl = m_rootURL + m_resURL;
                    MyTable::GetInstance()->PushResultTable(resurl);
                }
                // 匹配有效工作URL
                if (m_resURL.toStdString().compare(0, 1, "/") == 0)
                {
                    m_resURL = m_rootURL + m_resURL;
                }
                // 去除根URL
                if (m_resURL.compare(m_rootURL + '/') == 0)
                    continue;
                if(m_resURL.toStdString().compare(0,4,"http")!=0) // 过滤非http/https协议
                    continue;
                MyTable::GetInstance()->PushTodoTable(m_resURL);
                //qDebug()<<"[TODO]:"<<m_resURL;
            }
        }
    }
}
