QT       += core gui
QT       += serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    logrecorder.cpp \
    homepage.cpp \
    page06_1.cpp \
    page06_2.cpp \
    page06_3.cpp \
    page_01.cpp \
    page_02.cpp \
    page_03.cpp \
    page_04.cpp \
    page_05.cpp \
    page_06.cpp \
    pageclose.cpp \
    pageopen.cpp \
    portcom.cpp \
    portsettings.cpp \
    readprocess.cpp \
    writeprocess.cpp

HEADERS += \
    homepage.h \
    logrecorder.h \
    page06_1.h \
    page06_2.h \
    page06_3.h \
    page_01.h \
    page_02.h \
    page_03.h \
    page_04.h \
    page_05.h \
    page_06.h \
    pageclose.h \
    pageopen.h \
    portcom.h \
    portsettings.h \
    readprocess.h \
    writeprocess.h

FORMS += \
    homepage.ui \
    page06_1.ui \
    page06_2.ui \
    page06_3.ui \
    page_01.ui \
    page_02.ui \
    page_03.ui \
    page_04.ui \
    page_05.ui \
    page_06.ui \
    pageclose.ui \
    pageopen.ui \
    portsettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
