#ifndef INTERFACE_H
#define INTERFACE_H

#include "parser.h"


//*  订阅网站   *//
#define DIANYINTT "https://yingtt.com"
#define YINHUA "http://www.yhdm.io"


/* 网站接口声明 */
#ifdef DIANYINTT
extern Parser* CreateParser_DIANYINTT(QString html);
#endif

#ifdef YINHUA
extern Parser* CreateParser_YINHUA(QString html);
#endif

/* 网站类型枚举 */
enum WEB_TYPE
{
    WEBTYPE_DIANYINTT = 1,
    WEBTYPE_YINHUA = 2,
};

/* 网站对象创建方法 */
Parser* TTY_CreatParser(uint nWebType, QString html);


#endif // INTERFACE_H
