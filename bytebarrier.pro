DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x050F00

HEADERS += \
    mainwindow.h \
    secondwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    secondwindow.cpp


LIBS += -L/usr/X11R6/lib64 -lGL

CONFIG += c++14
QT += widgets opengl openglwidgets

FORMS += \
    mainwindow.ui \
    secondwindow.ui


