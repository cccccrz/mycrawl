#ifndef MYPARSER_H
#define MYPARSER_H
#include <QQueue>
#include <QString>
#include "table.hpp"
#include "html/ParserDom.h"
using namespace htmlcxx;

class MyParser
{
public:
    MyParser(QString html);

    // 爬取URL 和 匹配URL
    void parse(QString rootUrl,QString machURL);

    inline void setTagName(QString value){m_tagName = value;}
    inline void setAttrName(QString value){m_attrName = value;}

private:
    MyParser(){}
    // 解析器
    HTML::ParserDom m_parser;
    tree<HTML::Node> m_dom;
    tree<HTML::Node>::iterator m_it;
    tree<HTML::Node>::iterator m_endit;

    // 爬取标签名
    QString m_tagName;
    QString m_attrName;
    QString m_resURL;
};

#endif // MYPARSER_H
