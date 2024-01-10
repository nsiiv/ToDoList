QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_unittest.cpp \
    ../ToDoListEditor/TaskTableModel.cpp

HEADERS += \
    ../ToDoListEditor/TaskTableModel.h

