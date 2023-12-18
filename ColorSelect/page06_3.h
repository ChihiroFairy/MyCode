#ifndef PAGE06_3_H
#define PAGE06_3_H

#include <QWidget>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <QCompleter>
#include "writeprocess.h"

namespace Ui {
class Page06_3;
}

class Page06_3 : public QWidget
{
    Q_OBJECT

public:
    explicit Page06_3(QWidget *parent = nullptr);
    ~Page06_3();

signals:
    void back();

private slots:
    void on_qianCam_Button_clicked();

    void on_houCam_Button_clicked();

    void on_getImage_Button_clicked();

    void start();//监听的事件
    void acceptConnection();//被客户端连接上后，创建套接字、接收数据、处理异常、关闭服务器
    void updateServerProgress();//接收并处理显示图片
    void displayError(QAbstractSocket::SocketError socketError);//错误处理

    //base64字符串转图片
    QImage getImage(const QString &);
    void on_startButton_clicked();//监听或断开监听

private:
    Ui::Page06_3 *ui;

    //创建 写_预处理 对象
    writeProcess *writePro;

    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    qint64 totalBytes;     // 存放总大小信息
    qint64 bytesReceived;  // 已收到数据的大小
    qint64 fileNameSize;   // 文件名的大小信息
    qint64 imageSize; //图片大小

    QString fileName;      // 存放文件名
    QFile *localFile;      // 本地文件
    QByteArray inBlock;    // 数据缓冲区
    QString imageContent;

    QImage image;//图片
};

#endif // PAGE06_3_H
