#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSslConfiguration>
#include <QSslSocket>
#include <QVariant>
#include "html/ParserDom.h"
#include "table.hpp"

using namespace std;

#define BAIDU "https://www.baidu.com/s?wd="
#define BINGCN "https://cn.bing.com/search?q="
#define BINGFR "&ensearch=1"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // 隐藏进度条
    //ui->progressBar->hide();
    // 初始化
    m_manager = new QNetworkAccessManager(this);

    //m_URL = "http://www.yhdm.io/";

    //ui->comboBox->clear();


    /********* test **********/
    //检测QT支持的协议 //("ftp", "file", "qrc", "http", "https", "data")
    //qDebug()<<m_manager->supportedSchemes();
    // 测试openssl版本
    //qDebug() <<"ssl:" << QSslSocket::sslLibraryBuildVersionString();

    /********* UI美化 *********/
    // 去掉边框
    //this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{

    //delete m_manager;
    delete ui;
}

/******************* 爬取动作 ***************************/
void MainWindow::on_btn_StartSearch_clicked()
{
    /********** https 请求 **************/
    // sslcfg 对象
    QSslConfiguration cfg = m_request.sslConfiguration();
    // 设置验证模式
    // 不从对等端请求证书，发送本地证书
    cfg.setPeerVerifyMode(QSslSocket::VerifyNone);
    // 设置标准加密协议 TLSV1.0
    cfg.setProtocol(QSsl::TlsV1SslV3);
    m_request.setSslConfiguration(cfg);

    // 请求信息
    m_request.setUrl(QUrl(m_URL));

    /************* https 请求头 *******************/
    QVariant user_Agent_IE = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.96 Safari/537.36 Edg/88.0.705.56";
    QVariant user_Agent_chrome = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36";
//    QString cookie = "BIDUPSID=12C223BAA3C4B66955EA42D78F4824C0; PSTM=1588207425; BAIDUID=12C223BAA3C4B669D4B62BC5B762EC6F:FG=1; BDUSS=y1OVENCQjFuUHJwM1daVzdRSjdTNUxHTGxuQXI3QlJEMmpJek9uRjlBVjlTeGhmRVFBQUFBJCQAAAAAAAAAAAEAAACkp40bOTA0MjE0MwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH2-8F59vvBeR; BDUSS_BFESS=y1OVENCQjFuUHJwM1daVzdRSjdTNUxHTGxuQXI3QlJEMmpJek9uRjlBVjlTeGhmRVFBQUFBJCQAAAAAAAAAAAEAAACkp40bOTA0MjE0MwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH2-8F59vvBeR; BD_UPN=12314753; __yjs_duid=1_3242264e707ace0f1c7669fe92a1ecbb1611450269296; BAIDUID_BFESS=FBD223578851B81C15AB06B58F140287:FG=1; BDORZ=B490B5EBF6F3CD402E515D22BCDA1598; BD_HOME=1; H_PS_PSSID=33425_33515_33582_33256_33273_31253_33459_26350; BDRCVFR[feWj1Vr5u3D]=I67x6TjHwwYf0; delPer=0; BD_CK_SAM=1; PSINO=5; COOKIE_SESSION=606706_0_9_0_118_17_1_2_7_4_1_0_0_0_6_0_1611046018_0_1612061256|9#0_0_1612061256|1; sugstore=0; H_PS_645EC=695afFdYzSqxxzjQyNT9BtdXY9NpgPgZhlYM439SUTpk5Q4q08fweH7ytQc; BA_HECTOR=ag250124a4218h00721g1ckja0q";
//    QByteArray cookieByte = cookie.toUtf8();
//    QList<QNetworkCookie> cookie_List;
//    cookie_List.push_back(QNetworkCookie(cookieByte));
//    QVariant cookie_var;
//    cookie_var.setValue(cookie);
    m_request.setHeader(QNetworkRequest::UserAgentHeader,user_Agent_chrome);
//    m_request.setHeader(QNetworkRequest::CookieHeader,cookie_var);
    // 发送 get 请求
    m_reply = m_manager->get(m_request);

    connect(m_reply,&QNetworkReply::readyRead,this,&MainWindow::reply_ReadyRead);

    connect(m_reply,&QNetworkReply::downloadProgress,this,&MainWindow::processBar_update);

    connect(m_reply,&QNetworkReply::finished,this,&MainWindow::reply_Finished);

}

// 设定URL 目前支持HTTP   // 定义枚举支持多协议
void MainWindow::on_btn_SetURL_clicked()
{
    QString url = ui->label_URL->text();
#if 0   // 输入URL合理性判断
    int iPos = -1;

    // 0匹配
    if((iPos = url.indexOf("http://")))
    {
        QMessageBox::information(this,"Waining","请输入完整URL！");
        return;
    }
#endif
    m_URL = url;
}

void MainWindow::reply_ReadyRead()
{
    //ui->progressBar->show();//显示进度条
}

void MainWindow::processBar_update(qint64 bytesRead, qint64 totalBytes)
{
//    qDebug()<<"当前进度："<<bytesRead<<",sum:"<<totalBytes;
//    if(bytesRead>0 && totalBytes>0)
//    {
//        ui->progressBar->setValue(bytesRead * 100 / totalBytes);
//    }
}

void MainWindow::reply_Finished()
{
    //ui->progressBar->hide();

#if 1 /************输出到屏幕************/
    //int num = 14;
    QByteArray all = m_reply->readAll();

    //QString res = QString("搜索到<font color=\"#0000FF\">%1</font>条数据：\n").arg(num);
    ui->out_Text->clear();
    //ui->out_Text->setText(res);
    ui->out_Text->append(all);


    //ui->out_Text->append("<font color=\"#FF0000\">红色字体</font> ");
   // ui->out_Text->append("<font color=\"#00FF00\">绿色字体</font> ");
    //ui->out_Text->append("<font color=\"#0000FF\">蓝色字体</font> ");
#else   /************输出到文件************/
    QFile file("F:/data.html");
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
    QTextStream out(&file);
    out<<m_reply->readAll()<<endl;

#endif
    m_reply->deleteLater();
}

//// ****************POST请求测试***********************
//void MainWindow::on_pushButton_clicked()
//{
//    QSslConfiguration cfg = m_request.sslConfiguration();
//    // 设置验证模式
//    // 不从对等端请求证书，发送本地证书
//    cfg.setPeerVerifyMode(QSslSocket::VerifyNone);
//    // 设置标准加密协议 TLSV1.0
//    cfg.setProtocol(QSsl::TlsV1SslV3);
//    m_request.setSslConfiguration(cfg);

//    // 请求信息
//    m_request.setUrl(QUrl(m_URL));

//    /************* https 请求头 *******************/
//    QVariant user_Agent_chrome = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36";
//    m_request.setHeader(QNetworkRequest::UserAgentHeader,user_Agent_chrome);
//    m_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
//    // *******************翻译测试**************************
//    QString data = "text: red";
//    QByteArray array = data.toUtf8();

//    m_reply = m_manager->post(m_request,array);

//    connect(m_reply,&QNetworkReply::readyRead,this,&MainWindow::reply_ReadyRead);

//    connect(m_reply,&QNetworkReply::downloadProgress,this,&MainWindow::processBar_update);

//    connect(m_reply,&QNetworkReply::finished,this,&MainWindow::reply_Finished);

//}

void MainWindow::on_work_Btn_clicked()
{
    QString rootUrl = "https://yingtt.com";
    QString machUrl = "/vodplay/";
    // 创建线程工作
    m_worker = new Worker;
    m_worker->start_thread(rootUrl,machUrl);
}

void MainWindow::on_show_Btn_clicked()
{
    for(int i=0; i<10; i++)
    {
        if (MyTable::GetInstance()->ResultTableIsEmpty())
        {
            continue;
        }
        QString resUrl = MyTable::GetInstance()->PopResultTable();
        ui->listWidget->addItem(resUrl);
    }
}

void MainWindow::on_btn_search_clicked()
{
    QString keywords = ui->str_keywords->text();
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        m_URL = BAIDU + keywords;
        break;
    case 1:
        m_URL = BINGCN + keywords;
        break;
    case 2:
        m_URL = BINGCN + keywords + BINGFR;
        break;
    default:
        m_URL = BAIDU + keywords;
        break;
    }
    qDebug()<<m_URL ;

    /********** https 请求 **************/
    // sslcfg 对象
    QSslConfiguration cfg = m_request.sslConfiguration();
    // 设置验证模式
    // 不从对等端请求证书，发送本地证书
    cfg.setPeerVerifyMode(QSslSocket::VerifyNone);
    // 设置标准加密协议 TLSV1.0
    cfg.setProtocol(QSsl::TlsV1SslV3);
    m_request.setSslConfiguration(cfg);

    // 请求信息
    m_request.setUrl(QUrl(m_URL));

    /************* https 请求头 *******************/
    QVariant user_Agent_IE = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.96 Safari/537.36 Edg/88.0.705.56";
    QVariant user_Agent_chrome = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36";
    //    QString cookie = "BIDUPSID=12C223BAA3C4B66955EA42D78F4824C0; PSTM=1588207425; BAIDUID=12C223BAA3C4B669D4B62BC5B762EC6F:FG=1; BDUSS=y1OVENCQjFuUHJwM1daVzdRSjdTNUxHTGxuQXI3QlJEMmpJek9uRjlBVjlTeGhmRVFBQUFBJCQAAAAAAAAAAAEAAACkp40bOTA0MjE0MwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH2-8F59vvBeR; BDUSS_BFESS=y1OVENCQjFuUHJwM1daVzdRSjdTNUxHTGxuQXI3QlJEMmpJek9uRjlBVjlTeGhmRVFBQUFBJCQAAAAAAAAAAAEAAACkp40bOTA0MjE0MwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH2-8F59vvBeR; BD_UPN=12314753; __yjs_duid=1_3242264e707ace0f1c7669fe92a1ecbb1611450269296; BAIDUID_BFESS=FBD223578851B81C15AB06B58F140287:FG=1; BDORZ=B490B5EBF6F3CD402E515D22BCDA1598; BD_HOME=1; H_PS_PSSID=33425_33515_33582_33256_33273_31253_33459_26350; BDRCVFR[feWj1Vr5u3D]=I67x6TjHwwYf0; delPer=0; BD_CK_SAM=1; PSINO=5; COOKIE_SESSION=606706_0_9_0_118_17_1_2_7_4_1_0_0_0_6_0_1611046018_0_1612061256|9#0_0_1612061256|1; sugstore=0; H_PS_645EC=695afFdYzSqxxzjQyNT9BtdXY9NpgPgZhlYM439SUTpk5Q4q08fweH7ytQc; BA_HECTOR=ag250124a4218h00721g1ckja0q";
    //    QByteArray cookieByte = cookie.toUtf8();
    //    QList<QNetworkCookie> cookie_List;
    //    cookie_List.push_back(QNetworkCookie(cookieByte));
    //    QVariant cookie_var;
    //    cookie_var.setValue(cookie);
    m_request.setHeader(QNetworkRequest::UserAgentHeader,user_Agent_chrome);
    //    m_request.setHeader(QNetworkRequest::CookieHeader,cookie_var);
    // 发送 get 请求
    m_reply = m_manager->get(m_request);

    connect(m_reply,&QNetworkReply::readyRead,this,&MainWindow::reply_ReadyRead);

    connect(m_reply,&QNetworkReply::downloadProgress,this,&MainWindow::processBar_update);

    connect(m_reply,&QNetworkReply::finished,this,&MainWindow::reply_Finished);
}

