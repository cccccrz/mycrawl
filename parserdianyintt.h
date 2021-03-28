#ifndef DIANYINTTPARSER_H
#define DIANYINTTPARSER_H
#include "parser.h"

class ParserDianyintt : public Parser
{
public:
    ParserDianyintt(QString html);
    virtual ~ParserDianyintt() override;

    virtual void Parse() override;
};

#endif // DIANYINTTPARSER_H
