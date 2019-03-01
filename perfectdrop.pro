#-------------------------------------------------
#
# Project created by QtCreator 2019-02-11T19:38:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = perfectdrop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src\main.cpp \
        src\PerfectDrop.cpp \
        src\UI.cpp \
        src\Item.cpp \
        src\Parser.cpp \
        src\Database.cpp \
        src\ParserNode.cpp \
        src\Variant.cpp \
        src\Group.cpp \
        src\ItemGroup.cpp \
        src\Drop.cpp

HEADERS += \
        src\PerfectDrop.h \
        src\UI.h \
        src\Item.h \
        src\Parser.h \
        src\Database.h \
        src\ParserNode.h \
        src\Variant.h \
        src\Group.h \
        src\ItemGroup.h \
        src\Drop.h

RESOURCES += images/resource.qrc
RC_FILE   = images/icon.rc    
    
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
