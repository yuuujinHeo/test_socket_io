QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=no_keywords
CONFIG+=c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    socket.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    /home/rainbow/socket.io-client-cpp/build/include
DEPENDPATH += /home/rainbow/socket.io-client-cpp/build/lib

# INCLUDEPATH += /usr/include/boost
# LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system -lboost_thread

# LIBS += \
    # -L/home/rainbow/socket.io-client-cpp/build/lib -lsioclient

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

CONFIG(debug, debug|release):DEFINES +=DEBUG=1


CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build/lib/Release/ -lsioclient
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lsioclient


CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build/lib/Release/ -lboost_random
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lboost_random

CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build/lib/Release/ -lboost_system
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lboost_system

CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build/lib/Release/ -lboost_date_time
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lboost_date_time
