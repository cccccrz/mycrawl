#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkCookie>
#include <QFile>
#include <QMessageBox>

#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_StartSearch_clicked();  //  开始搜索

    void on_btn_SetURL_clicked();       //  手动设置URL

private:
    Ui::MainWindow *ui;


    QString m_URL;               // 待爬取的URL
    //QEventLoop m_loop;           // 事件循环
    QNetworkRequest m_request;  // 请求
    QNetworkReply* m_reply;     // 响应

    QNetworkAccessManager* m_manager;
    Worker* m_worker;

private slots:
    // 准备接受回调
    void reply_ReadyRead();
    // 更新进度条
    void processBar_update(qint64 bytesRead, qint64 totalBytes);
    // 接受完毕回调
    void reply_Finished();


    void on_work_Btn_clicked();
    void on_show_Btn_clicked();
    void on_btn_search_clicked();
};
#endif // MAINWINDOW_H
