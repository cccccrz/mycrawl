#include "parserdianyintt.h"
#include "common.h"

#include <QDebug>

#define TAGNAME "a"
#define ATTRNAME "href"
#define INFOMSG "title"
#define ROOTURL "https://yingtt.com"
#define MATCHURL "/vodplay/"

extern Parser* CreateParser_DIANYINTT(QString html)
{
    return (new ParserDianyintt(html));
}

ParserDianyintt::ParserDianyintt(QString html)
{
    m_dom = m_parser.parseTree(html.toStdString());
    m_it = m_dom.begin();
    m_endit = m_dom.end();

    m_tagName = TAGNAME;
    m_attrName = ATTRNAME;
    m_rootURL = ROOTURL;
    m_matchURL = MATCHURL;
    m_infomsg = INFOMSG;
    m_todo_table = TABLE_TODO_DIANYINTT;
    m_visited_table = TABLE_VISITED_DIANYINTT;
    m_result_table = TABLE_RESULT_DIANYINTT;
}

ParserDianyintt::~ParserDianyintt()
{

}

void ParserDianyintt::Parse()
{
    for (; m_it != m_endit; ++m_it) {
        if (!m_it->isTag())
            continue;
        if ((_stricmp(m_it->tagName().c_str(), m_tagName.toUtf8().data()) == 0))
        {
            //qDebug()<<"[parse]:"<<m_it->text().c_str()<<endl;
            m_it->parseAttributes(); // 扩展子标签
            // 匹配子标签
            if (m_it->attribute(m_attrName.toUtf8().data()).first)
            {
                m_resURL = m_it->attribute(m_attrName.toUtf8().data()).second.c_str();


                /* 匹配结果URL */
                if (m_resURL.toStdString().compare(0, (uint)m_matchURL.length(), m_matchURL.toStdString()) == 0)
                {
                    if(m_it->attribute("title").first) // 匹配结果标题
                    {
                        QString title = m_it->attribute(m_infomsg.toUtf8().data()).second.c_str();
#ifdef MYSQL
                        Push_Result(m_result_table, m_rootURL + m_resURL, title);
                        //DatabaseOp::Result_Push(TABLE_RESULT_YINHUA, m_rootURL+m_resURL, title);
#else
                        QString resurl = title + " " + m_rootURL + m_resURL;
                        MyTable::GetInstance()->PushResultTable(resurl);
#endif
                        //continue;
                    }
                }

                /***************************** URL 过滤 *****************************/
                /* 匹配有效工作URL */
                if (m_resURL.toStdString().compare(0, 1, "/") == 0)
                {
                    m_resURL = m_rootURL + m_resURL;
                }
                /* 过滤无效URL */
                if (m_resURL.compare(m_rootURL + '/') == 0) // 去除根URL
                    continue;
                if(m_resURL.toStdString().compare(0,4,"http")!=0) // 过滤非http/https协议
                    continue;

                    /************** 加入任务 ***************/
#ifdef MYSQL
                // URL去重
                if(IsExist(m_visited_table, m_resURL)==0)
                {
                    Push_Todo(m_todo_table, m_resURL);
                }
//                if(!DatabaseOp::isExist(TABLE_VISITED_YINHUA,m_resURL))
//                {
//                    DatabaseOp::Todo_Push(TABLE_TODO_YINHUA, m_resURL);
//                }
//qDebug()<<"continue";
#else
                MyTable::GetInstance()->PushTodoTable(m_resURL);
                //qDebug()<<"[TODO]:"<<m_resURL;
#endif
            }
        }
    }
}
