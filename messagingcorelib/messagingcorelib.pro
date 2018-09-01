QT += core network
QT -= gui widgets

TARGET = messagingcorelib
TEMPLATE = lib

PROJECT_ROOT = ..

DEFINES += MESSAGINGCORELIB_LIBRARY

SOURCES += \
    dbmsgfieldbase.cpp \
    dbmsgbase.cpp \
    messages/mymessage.cpp

HEADERS += messagingcorelib_global.h \
    dbmsgfieldbase.h \
    dbmsgfield.h \
    dbmsgbase.h \
    messages/mymessage.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/project.pri)
