#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T12:45:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GalaxyGame
TEMPLATE = app
CONFIG += c++14


SOURCES += \
    galaxy.cc \
    main.cc \
    mainwindow.cpp \
    statistics.cc \
    eventhandler.cc \
    statsframe.cc \
    gamewindow.cc \
    gamecontroller.cc \
    gamewindowlayout.cc \
    rescuemission.cc \
    highscoresystem.cc \
    startwindow.cc \
    galaxyframe.cc \
    galaxyview.cc \
    graphicsview.cc \
    solarsystemitem.cc \
    quantumengine.cc \
    quantummap.cc \
    playership.cc \
    highscorewindow.cc \
    hpbar.cc \
    gamestate.cc \
    playerrepairdialog.cc \
    playerbuydialog.cc \
    missiondialog.cc \
    shipitem.cc \
    starinfoframe.cc \
    missioncompleteddialog.cc \
    startdialog.cc \
    gameoverdialog.cc


HEADERS  += \
    galaxy.hh \
    eventhandler.hh \
    statistics.hh \
    mainwindow.h \
    statsframe.hh \
    gamewindow.hh \
    gamecontroller.hh \
    gamewindowlayout.hh \
    imission.hh \
    rescuemission.hh \
    highscoresystem.hh \
    startwindow.hh \
    galaxyframe.hh \
    galaxyview.hh \
    graphicsview.hh \
    solarsystemitem.hh \
    quantumengine.hh \
    quantummap.hh \
    playership.hh \
    highscorewindow.hh \
    hpbar.hh \
    gamestate.hh \
    playerrepairdialog.hh \
    playerbuydialog.hh \
    missiondialog.hh \
    shipitem.hh \
    starinfoframe.hh \
    missioncompleteddialog.hh \
    startdialog.hh \
    gameoverdialog.hh

INCLUDEPATH += $$PWD/../Course
DEPENDPATH += $$PWD/../Course

CONFIG(release, debug|release) {
   DESTDIR = release
}

CONFIG(debug, debug|release) {
   DESTDIR = debug
}

win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILE(S) for Windows &
    copyfiles.commands += @call xcopy ..\\..\\GalaxyGame\\Assets Assets /i /s /e /y
}
unix:!macx {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S) for Linux\" &&
    copyfiles.commands += cp -r ../../GalaxyGame/Assets $$DESTDIR
}
macx {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S) for MacOS\" &&
    copyfiles.commands += mkdir -p $$DESTDIR/GalaxyGame.app/Contents/MacOS &&
    copyfiles.commands += cp -r ../../GalaxyGame/Assets $$DESTDIR &&
    copyfiles.commands += cp -r ../../GalaxyGame/Assets $$DESTDIR/GalaxyGame.app/Contents/MacOS/
}

LIBS += -L$$OUT_PWD/../Course/
LIBS += -L$$OUT_PWD/../Course/$${DESTDIR}/ -lCourse


QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

FORMS += \
    mainwindow.ui

DISTFILES += \
    highscores.txt
