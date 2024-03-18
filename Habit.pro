QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    login.cpp \
    main.cpp \
    habittracker.cpp \
    signup.cpp \
    welcome.cpp

HEADERS += \
    admin.h \
    habittracker.h \
    login.h \
    signup.h \
    welcome.h

FORMS += \
    admin.ui \
    habittracker.ui \
    login.ui \
    signup.ui \
    test.ui \
    welcome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    habits.txt
