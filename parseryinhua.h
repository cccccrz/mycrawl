#ifndef PARSERYINHUA_H
#define PARSERYINHUA_H
#include "parser.h"

class ParserYinhua : public Parser
{
public:
    ParserYinhua(QString html);
    virtual ~ParserYinhua() override;

    virtual void Parse() override;
};

#endif // PARSERYINHUA_H
