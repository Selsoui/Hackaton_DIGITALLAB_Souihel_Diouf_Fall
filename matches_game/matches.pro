QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Matches_game
TEMPLATE = app

SOURCES += \
        main.cpp \
        src/mainwindow.cpp \
        src/matches_game.cpp \
        src/help.cpp \
        src/settings.cpp

HEADERS += \
        src/mainwindow.h \
        src/matches_game.h \
        src/help.h \
        src/settings.h

FORMS += \
        src/mainwindow.ui \
        src/matches_game.ui \
        src/help.ui \
        src/settings.ui

RESOURCES += \
    resources.qrc
