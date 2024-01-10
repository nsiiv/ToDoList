QT += widgets testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../ToDoListEditor

SOURCES += \
    tst_testgui.cpp \
    ../ToDoListEditor/mainwindow.cpp \
    ../ToDoListEditor/Delegates/OperationButtons.cpp \
    ../ToDoListEditor/Delegates/ShowTaskButton.cpp \
    ../ToDoListEditor/Delegates/StatusButton.cpp \
    ../ToDoListEditor/TaskDialog.cpp \
    ../ToDoListEditor/TaskTableModel.cpp \
    ../ToDoListEditor/TaskTableView.cpp \
    ../ToDoListEditor/TitleLineEdit.cpp \

HEADERS += \
    ../ToDoListEditor/mainwindow.h \
    ../ToDoListEditor/Delegates/OperationButtons.h \
    ../ToDoListEditor/Delegates/ShowTaskButton.h \
    ../ToDoListEditor/Delegates/StatusButton.h \
    ../ToDoListEditor/TaskDialog.h \
    ../ToDoListEditor/TaskTableModel.h \
    ../ToDoListEditor/TaskTableView.h \
    ../ToDoListEditor/TitleLineEdit.h \


FORMS += \
    ../ToDoListEditor/TaskDialog.ui \
    ../ToDoListEditor/mainwindow.ui

