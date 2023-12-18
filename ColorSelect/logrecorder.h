#ifndef LOGRECORDER_H
#define LOGRECORDER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDate>
#include <QTime>
#include <QSerialPort>
#include <QDateTime>
#include "portcom.h"
#include <QThread>
#include <QDebug>

class LogRecorder : public QObject
{
    Q_OBJECT
public:

    //使用单例模式
    static LogRecorder *get_ins();
    static LogRecorder *logRec;

public slots:
    //在对应日期的日志文件中写入日志
    void writeLog(const QString &log);

private:
    explicit LogRecorder(QObject *parent = nullptr);
    ~LogRecorder();

    QFile logFile;
    QTextStream textStream;
    QMutex mutex;
    QDate currentDate;

    QThread *logThread;

    //创建对应日期的日志文件
    void openLogFile();

};

#endif // LOGRECORDER_H
