QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

DESTDIR += $$PWD/bin

TARGET = QtCrawl

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

#LIBS += -L$$PWD/lib -lhtmlcxx

SOURCES += \
    common.cpp \
    databaseop.cpp \
    main.cpp \
    mainwindow.cpp \
    html/utils.cc \
    html/Uri.cc \
    html/ParserSax.cc \
    html/ParserDom.cc \
    html/Node.cc \
    html/Extensions.cc \
    mycrawl.cpp \
    mythread.cpp \
    parser.cpp \
    worker.cpp \
    parserdianyintt.cpp \
    parseryinhua.cpp \
    databasecommon.cpp

HEADERS += \
    common.h \
    databaseop.h \
    mainwindow.h \
    html/utils.h \
    html/Uri.h \
    html/tree.h \
    html/ParserSax.h \
    html/ParserDom.h \
    html/Node.h \
    html/Extensions.h \
    html/debug.h \
    html/ci_string.h \
    html/wincstring.h \
    html/tld.h \
    mycrawl.h \
    mythread.h \
    parser.h \
    table.hpp \
    worker.h \
    parserdianyintt.h \
    parseryinhua.h \
    databasecommon.h

FORMS += \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
