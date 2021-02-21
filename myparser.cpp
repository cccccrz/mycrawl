#include "myparser.h"


MyParser::MyParser(QString html)
{
    m_dom = m_parser.parseTree(html.toStdString());
    m_it = m_dom.begin();
    m_endit = m_dom.end();

    m_tagName = "a";
    m_attrName = "href";
}

void MyParser::parse(QString rootUrl, QString machURL)
{
    for (; m_it != m_endit; ++m_it) {
        if (!m_it->isTag())
            continue;
        if ((_stricmp(m_it->tagName().c_str(), m_tagName.toUtf8().data()) == 0))
        {
            //匹配子标签
            m_it->parseAttributes();
            if (m_it->attribute(m_attrName.toUtf8().data()).first)
            {
                m_resURL = QString::fromStdString( m_it->attribute(m_attrName.toUtf8().data()).second);
                if (m_resURL.toStdString().compare(0, 1, "/") == 0)
                {
                    m_resURL = rootUrl + m_resURL;
                }
                // 匹配结果URL
                if (m_resURL.toStdString().compare(0, (size_t)machURL.length(), machURL.toStdString()) == 0)
                {
                    MyTable::GetInstance()->GetResultTable().push_back(m_resURL);
                }
                MyTable::GetInstance()->GetTodoTable().push_back(m_resURL);
            }
        }
    }
}
