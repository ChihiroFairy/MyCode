#include "homepage.h"
#include <QApplication>
#include "portcom.h"
#include "logrecorder.h"


// Custom message handler for Qt log messages
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QMutex mutex;
    mutex.lock();

    QString logLevel;
    switch (type) {
        case QtDebugMsg:
            logLevel = QString("Debug");
            break;
        case QtWarningMsg:
            logLevel = QString("Warning");
            break;
        case QtCriticalMsg:
            logLevel = QString("Critical");
            break;
        case QtFatalMsg:
            logLevel = QString("Fatal");
            break;
        case QtInfoMsg:
            logLevel = QString("Info");
            break;
    }

    QString contextInfo = QString("File:(%1) Line:(%2)").arg(context.file).arg(context.line);
    QString message = QString("%1: %2 %3").arg(logLevel).arg(contextInfo).arg(msg);
    // Use LogRecorder to write the log message
    LogRecorder *logRecorder = LogRecorder::get_ins();
    logRecorder->writeLog(message);

    mutex.unlock();
}
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    PortCom portCom;
    // Set the custom message handler
    qInstallMessageHandler(outputMessage);
    HomePage w;
    w.show();
    return a.exec();
}
