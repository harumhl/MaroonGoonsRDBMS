        #-------------------------------------------------
    #
    # Project created by QtCreator 2016-02-27T15:20:09
    #
    #-------------------------------------------------

    QT       += core gui
    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
    CONFIG += c++11

    TARGET = SportsStat
    TEMPLATE = app


    SOURCES += main.cpp\
            mainwindow.cpp \
        uniondiffprodjoin.cpp \
        displayrelation.cpp \
        openclosewriteexit.cpp \
    selectrelation.cpp \
    projectrelation.cpp \
    displayhelp.cpp \
    addleagueteamplayer.cpp

    HEADERS  += mainwindow.h \
        uniondiffprodjoin.h \
        displayrelation.h \
        openclosewriteexit.h \
    selectrelation.h \
    projectrelation.h \
    displayhelp.h \
    addleagueteamplayer.h

    FORMS    += mainwindow.ui \
        uniondiffprodjoin.ui \
        displayrelation.ui \
        openclosewriteexit.ui \
    selectrelation.ui \
    projectrelation.ui \
    displayhelp.ui \
    addleagueteamplayer.ui
