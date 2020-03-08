#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T16:42:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LinkedOon
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    sources/system.cpp \
    sources/user.cpp \
    signupwindow.cpp \
    userprofilewindow.cpp \
    companyprofilewindow.cpp \
    edituserprofwindow.cpp \
    sources/company.cpp \
    sources/job.cpp \
    sources/skill.cpp \
    sources/utils.cpp \
    editcompanyprofwindow.cpp \
    sources/butler.cpp \
    searchwindow.cpp

HEADERS  += loginwindow.h \
    signupwindow.h \
    userprofilewindow.h \
    companyprofilewindow.h \
    edituserprofwindow.h \
    editcompanyprofwindow.h \
    headers/butler.h \
    headers/education.h \
    headers/experience.h \
    headers/job.h \
    headers/skill.h \
    headers/system.h \
    headers/user.h \
    headers/utils.h \
    headers/company.h \
    searchwindow.h

FORMS    += loginwindow.ui \
    signupwindow.ui \
    userprofilewindow.ui \
    companyprofilewindow.ui \
    edituserprofwindow.ui \
    editcompanyprofwindow.ui \
    searchwindow.ui
