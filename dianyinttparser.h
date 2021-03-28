#ifndef DIANYINTTPARSER_H
#define DIANYINTTPARSER_H
#include "parser.h"

class DianyinttParser : public Parser
{
public:
    DianyinttParser(QString html);
    virtual ~DianyinttParser() override;

    virtual void Parse() override;
};

#endif // DIANYINTTPARSER_H
