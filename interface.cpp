#include "interface.h"

/* 网站对象创建方法 */
Parser* TTY_CreatParser(uint nWebType, QString html)
{
    Parser* pParser = nullptr;

    switch(nWebType)
    {
#ifdef DIANYINTT
    case WEBTYPE_DIANYINTT :
    {
        pParser = CreateParser_DIANYINTT(html);
    }
    break;
#endif

#ifdef YINHUA
    case WEBTYPE_YINHUA :
    {
        pParser = CreateParser_YINHUA(html);
    }
    break;
#endif
    default:
        break;
    }
    return pParser;
}
