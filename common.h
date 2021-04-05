#ifndef COMMON_H
#define COMMON_H

#include <QNetworkAccessManager>
#include <QObject>

#include "parser.h"

/************ 搜索引擎 ************/
#define BAIDU "https://www.baidu.com/s?wd="
#define BINGCN "https://cn.bing.com/search?q="
#define BINGFR "&ensearch=1"

/************ 订阅网站 ************/
#define DIANYINTT "https://yingtt.com"
#define YINHUA "http://www.yhdm.io"

/************ 使用MySQL *************/
#define MYSQL

/* mysql 表 */
#define TABLE_TODO_YINHUA "todo_yinhua"
#define TABLE_VISITED_YINHUA "visited_yinhua"
#define TABLE_RESULT_YINHUA "result_yinhua"

#define TABLE_TODO_DIANYINTT "todo_dianyintt"
#define TABLE_VISITED_DIANYINTT "visited_dianyintt"
#define TABLE_RESULT_DIANYINTT "result_dianyintt"

/************* 网站接口声明 *************/
#ifdef DIANYINTT
extern Parser *CreateParser_DIANYINTT(QString html);
#endif

#ifdef YINHUA
extern Parser *CreateParser_YINHUA(QString html);
#endif

/************* 网站类型枚举 *************/
enum WEB_TYPE {
    WEBTYPE_DIANYINTT = 1,
    WEBTYPE_YINHUA = 2,
};

/************* 网站对象创建方法 *************/
Parser *TTY_CreatParser(uint nWebType, QString html);

class Common : public QObject
{
    Q_OBJECT
public:
    Common(QObject *parent = nullptr);
    ~Common();

    // 得到http通信类对象
    static QNetworkAccessManager *getNetManager();

private:
    // http类
    static QNetworkAccessManager *m_netManager;
};

#endif // COMMON_H
