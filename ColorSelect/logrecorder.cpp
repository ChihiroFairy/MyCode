#include "logrecorder.h"

/*
 * 单例模式 *
*/
LogRecorder * LogRecorder::logRec = nullptr;
LogRecorder *LogRecorder::get_ins()
{
    if(logRec == nullptr) {
        logRec = new LogRecorder();
    }
    return logRec;
}

LogRecorder::LogRecorder(QObject *parent) : QObject(parent)
{
    logThread = new QThread();
    this->moveToThread(logThread);
    openLogFile();
    logThread->start();
}
LogRecorder::~LogRecorder() {
    logFile.close();
    logThread->quit();
    logThread->wait();
    logThread->deleteLater();
    delete logRec;
}

/*
 * 函数：writeLog()
 * 参数：log
 * 功能：在已创建的对应日期的日志文件中进行日志写入
 * 备注：
 */
void LogRecorder::writeLog(const QString &log) {
    QMutexLocker locker(&mutex);

    // Check if the current date has changed
    if (currentDate != QDate::currentDate()) {
        logFile.close();
        openLogFile();
    }

    // Get the current timestamp with milliseconds
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");


    // Get the current thread ID
    Qt::HANDLE threadId = QThread::currentThreadId();

    // If there is a valid serial port object, record its information
    if (logFile.isOpen()) {
        textStream << timestamp << " ThreadID:" << threadId << " :" << log << "\n";
        textStream.flush();
    }
}

/*
 * 函数：openLogFile()
 * 参数：
 * 功能：在指定路径创建对应日期的日志文件
 * 备注：
 */
void LogRecorder::openLogFile() {
    currentDate = QDate::currentDate();
    QString fileName = "logfile_" + currentDate.toString("yyyyMMdd") + ".txt";

    // 指定保存路径
    QString filePath = "/home/book/Documents/Log for test/" + fileName;

    logFile.setFileName(filePath);
    logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    textStream.setDevice(&logFile);
}
