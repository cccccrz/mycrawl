#ifndef PARSER_H
#define PARSER_H
#include <QQueue>
#include <QString>
#include "table.hpp"
#include "html/ParserDom.h"
using namespace htmlcxx;

class Parser
{
public:
    Parser();
    virtual void Parse()=0;
    virtual ~Parser();

protected:

    // 解析器
    HTML::ParserDom m_parser;
    tree<HTML::Node> m_dom;
    tree<HTML::Node>::iterator m_it;
    tree<HTML::Node>::iterator m_endit;

    // 爬取标签名
    QString m_tagName;
    QString m_attrName;
    QString m_resURL;
    QString m_rootURL;
    QString m_matchURL;

private:

};

#endif // PARSER_H
