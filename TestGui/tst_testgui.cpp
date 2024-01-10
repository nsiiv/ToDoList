#include <QtTest>
#include <QCoreApplication>

#include <QElapsedTimer>
#include <QCalendarWidget>

#include "../ToDoListEditor/mainwindow.h"
#include "../ToDoListEditor/ui_mainwindow.h"

#include "../ToDoListEditor/TaskDialog.h"
#include "../ToDoListEditor/TitleLineEdit.h"

#include "../ToDoListEditor/TaskTableModel.h"
//------------------------------------------------------------------------------
class TestGui : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testMainWindowDisplayInit();

    void testAddTaskDialogInit();
    void testEditTaskDialogInit();
    void testShowTaskDialogInit();

    void TestTableViewInit();
    void testAddTaskView_data();
    void testAddTaskView();

    void testTaskDialog_data();
    void testTaskDialog();

    void testAddTaskPerformance();
    void testDeleteTaskPerformance();
    void testEditTaskPerformance();

private:
    MainWindow* window;
};
//------------------------------------------------------------------------------
// Private Slots
//------------------------------------------------------------------------------
void TestGui::initTestCase()
{
    window = new MainWindow;
}
//------------------------------------------------------------------------------
void TestGui::cleanupTestCase()
{
    delete window;
}
//------------------------------------------------------------------------------
void TestGui::testMainWindowDisplayInit()
{
    QVERIFY2(window->ui->pbNewTask, "pbNewTask Button not created");
    QVERIFY2(window->ui->tableView, "tableView not created");
    QVERIFY2(window->ui->lblLog, "lblLog not created");

    QVERIFY(!window->windowIcon().isNull());

    QCOMPARE(window->windowTitle(), "ToDo List");
}
//------------------------------------------------------------------------------
void TestGui::testAddTaskDialogInit()
{
    QSignalSpy spy(window->ui->pbNewTask, SIGNAL(clicked()));

    QTest::mouseClick(window->ui->pbNewTask, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);

    TaskDialog* addTaskDialog = new TaskDialog;

    QVERIFY2(addTaskDialog->getTitle().isEmpty(), "Title not empty");
    QVERIFY2(addTaskDialog->getDescription().isEmpty(), "Description not empty");

    // Time test
    const auto time = QTime::currentTime();
    QCOMPARE(addTaskDialog->getTime(), time.toString("HH:mm"));
    QCOMPARE(addTaskDialog->minimumTime(), time.toString("HH:mm"));

    // Date test
    const auto date = QDate::currentDate();
    QCOMPARE(addTaskDialog->getDate(), date.toString("dd.MM.yyyy"));
    QCOMPARE(addTaskDialog->minimumDate(), date.toString("dd.MM.yyyy"));

    QCOMPARE(addTaskDialog->applyButtonIsEnabled(), false);

    delete  addTaskDialog;
}
//------------------------------------------------------------------------------
void TestGui::testEditTaskDialogInit()
{
    TaskDialog* addTaskDialog = new TaskDialog(nullptr, TaskDialog::EditMode);

    addTaskDialog->setTitle("TestTask");
    addTaskDialog->setDescription("Test Description");

    QVERIFY2(!addTaskDialog->getTitle().isEmpty(), "Title is empty");
    QVERIFY2(!addTaskDialog->getDescription().isEmpty(), "Description is empty");

    QCOMPARE(addTaskDialog->getTitle(), "TestTask");
    QCOMPARE(addTaskDialog->getDescription(), "Test Description");

    // Date test
    const auto date = QDate::currentDate();
    addTaskDialog->setDate(date.toString("dd.MM.yyyy"));
    QCOMPARE(addTaskDialog->getDate(), date.toString("dd.MM.yyyy"));

    QCOMPARE(addTaskDialog->applyButtonIsEnabled(), true);

    // Time test
    const auto time = QTime::currentTime();
    addTaskDialog->setTime(time.toString("HH:mm"));
    QCOMPARE(addTaskDialog->getTime(), time.toString("HH:mm"));

    delete  addTaskDialog;
}
//------------------------------------------------------------------------------
void TestGui::testShowTaskDialogInit()
{
    TaskDialog* showTaskDialog = new TaskDialog(nullptr, TaskDialog::ShowMode);

    QVERIFY2(showTaskDialog->titleIsReadOnly(), "Title not read only");
    QVERIFY2(showTaskDialog->timeEditorIsReadOnly(), "Time editor not read only");
    QVERIFY2(showTaskDialog->descriptionIsReadOnly(), "Description not read only");

    QCalendarWidget *calendarWidget = showTaskDialog->calendarWidget();
    QVERIFY2(calendarWidget->selectionMode() == QCalendarWidget::NoSelection, "Calendar not in NoSelection mode");

    delete showTaskDialog;
}
//------------------------------------------------------------------------------
void TestGui::TestTableViewInit()
{
    QVERIFY(window->ui->tableView->horizontalHeader()->sectionResizeMode(0)
            == QHeaderView::Stretch);

    QVERIFY2(window->ui->tableView->model(), "Model is not set");

    QVERIFY2(window->ui->tableView->itemDelegateForColumn(2),
             "StatusButton delegate is not set");
    QVERIFY2(window->ui->tableView->itemDelegateForColumn(3),
             "OperationButtons delegate is not set");
    QVERIFY2(window->ui->tableView->itemDelegateForColumn(4),
             "ShowTaskButton delegate is not set");
}
//------------------------------------------------------------------------------
void TestGui::testAddTaskView_data()
{
    QTest::addColumn<QString>("taskTimeDateView");
    QTest::addColumn<QString>("taskTitleView");
    QTest::addColumn<bool>("taskStatusView");

    QTest::newRow("ViewAddTaskTest1")  << "7:00 06.03.2024"   << "Test1" << true;
    QTest::newRow("ViewAddTaskTest2")  << "7:15 06.03.2024"   << "Test2" << false;
    QTest::newRow("ViewAddTaskTest3")  << "7:30 06.03.2024"   << "Test3" << true;
    QTest::newRow("ViewAddTaskTest4")  << "7:50 06.03.2024"   << "Test4" << true;
    QTest::newRow("ViewAddTaskTest5")  << "14:30 06.03.2024"  << "Test5" << true;
}
//------------------------------------------------------------------------------
void TestGui::testAddTaskView()
{
    QFETCH(QString, taskTimeDateView);
    QFETCH(QString, taskTitleView);
    QFETCH(bool, taskStatusView);

    TaskTableModel *model = new TaskTableModel;

    window->ui->tableView->setModel(model);

    int row = model->rowCount();

    model->addTask(taskTimeDateView, taskTitleView, taskStatusView);

    QCOMPARE(model->rowCount(), row + 1);

    int newRow = model->rowCount() - 1;

    QCOMPARE(model->data(model->index(newRow, 0), Qt::DisplayRole).toString(), taskTimeDateView);
    QCOMPARE(model->data(model->index(newRow, 1), Qt::DisplayRole).toString(), taskTitleView);
    QCOMPARE(model->data(model->index(newRow, 2), Qt::DisplayRole).toBool(), taskStatusView);

    QCOMPARE(window->ui->tableView->model()->data(model->index(newRow, 0), Qt::DisplayRole).toString(),
             taskTimeDateView);
    QCOMPARE(window->ui->tableView->model()->data(model->index(newRow, 1), Qt::DisplayRole).toString(),
             taskTitleView);
    QCOMPARE(window->ui->tableView->model()->data(model->index(newRow, 2), Qt::DisplayRole).toBool(),
             taskStatusView);

    delete model;
}
//------------------------------------------------------------------------------
void TestGui::testTaskDialog_data()
{
    QTest::addColumn<QString>("taskDialogTime");
    QTest::addColumn<QString>("taskDialogDate");
    QTest::addColumn<QString>("taskDialogTitle");
    QTest::addColumn<QString>("taskDialogDescr");

    QTest::addColumn<QString>("curtaskDialogTime");
    QTest::addColumn<QString>("curtaskDialogDate");
    QTest::addColumn<QString>("curtaskDialogTitle");
    QTest::addColumn<QString>("curtaskDialogDescr");


    // Valid tests
    QTest::newRow("ValidTaskDialogTest1")   << "23:00"  << "13.01.2024" << "Новая задача"      << "Описание тестовой задачи"
                                            << "23:00"  << "13.01.2024" << "Новая задача"      << "Описание тестовой задачи";

    QTest::newRow("ValidTaskDialogTest2")   << "23:00"  << "13.01.2024" << "Новая задача"      << ""
                                            << "23:00"  << "13.01.2024" << "Новая задача"      << "";

    QTest::newRow("ValidTaskDialogTest3")   << "23:00"  << "25.01.2024" << "Задача"            << ""
                                            << "23:00"  << "25.01.2024" << "Задача"            << "";

    QTest::newRow("ValidTaskDialogTest4")   << "12:00"  << "16.07.2030" << "Дата будущего"     << ""
                                            << "12:00"  << "16.07.2030" << "Дата будущего"     << "";

    // Invalid tests
    QDateTime dateTime = QDateTime::currentDateTime();
    QString date = dateTime.toString("dd.MM.yyyy");
    QString time = dateTime.toString("HH:mm");

    QTest::newRow("InvalidTaskDialogTest1") << "22:00"  << "4.02.2024"  << "Задача"            << ""
                                            << "22:00"  << date         << "Задача"            << "";

    QTest::newRow("InvalidTaskDialogTest2") << "22:00"  << ""            << "Задача"            << ""
                                            << "22:00"  << date          << "Задача"            << "";

    QTest::newRow("InvalidTaskDialogTest3") << ""       << "25.01.2024" << "Задача"            << ""
                                            << time     << "25.01.2024" << "Задача"            << "";


    QTest::newRow("InvalidTaskDialogTest4") << "28:00"  << "25.01.2024" << "Задача"            << ""
                                            << time     << "25.01.2024" << "Задача"            << "";


    QTest::newRow("InvalidTaskDialogTest5") << "6:00"   << "13.01.2024" << "Новая задача"      << ""
                                            << time     << "13.01.2024" << "Новая задача"      << "";


    QTest::newRow("InvalidTaskDialogTest6") << "23:00"  << "20.11.2017" << "Тестовая задача"   << ""
                                            << "23:00"  << date         << "Тестовая задача"   << "";

    QTest::newRow("InvalidTaskDialogTest7") << "15:00"  << "24.01.2024" << " Task "            << ""
                                            << "15:00"  << "24.01.2024" << "Task"              << "";
}
//------------------------------------------------------------------------------
void TestGui::testTaskDialog()
{
    QFETCH(QString, taskDialogTime);
    QFETCH(QString, taskDialogDate);
    QFETCH(QString, taskDialogTitle);
    QFETCH(QString, taskDialogDescr);

    QFETCH(QString, curtaskDialogTime);
    QFETCH(QString, curtaskDialogDate);
    QFETCH(QString, curtaskDialogTitle);
    QFETCH(QString, curtaskDialogDescr);

    TaskDialog* taskDialog = new TaskDialog(nullptr, TaskDialog::NewTask);

    taskDialog->setDate(taskDialogDate);
    QCOMPARE(taskDialog->getDate(), curtaskDialogDate);

    taskDialog->setTime(taskDialogTime);
    QCOMPARE(taskDialog->getTime(), curtaskDialogTime);

    taskDialog->setTitle(taskDialogTitle);
    QCOMPARE(taskDialog->getTitle(), curtaskDialogTitle);

    taskDialog->setDescription(taskDialogDescr);
    QCOMPARE(taskDialog->getDescription(), curtaskDialogDescr);

        delete  taskDialog;
}
//------------------------------------------------------------------------------
void TestGui::testAddTaskPerformance()
{
    TaskTableModel *model = new TaskTableModel;

    window->ui->tableView->setModel(model);

    QBENCHMARK
    {
        QString timeDate = "22:00 12.01.2024";
        QString title = "Подъем";
        bool status = false;

        for(int i = 0; i < 1000; i++)
            model->addTask(timeDate, title, status);
    }

    delete model;
}
//------------------------------------------------------------------------------
void TestGui::testDeleteTaskPerformance()
{
    TaskTableModel *model = new TaskTableModel;

    window->ui->tableView->setModel(model);

    QBENCHMARK
    {
        QString timeDate = "22:00 12.01.2024";
        QString title = "Подъем";
        bool status = false;

        model->addTask(timeDate, title, status);

        QCOMPARE(model->rowCount(), 1);

        model->deleteTask(model->index(0, 3));
        QCOMPARE(model->rowCount(), 0);

        QCOMPARE(model->data(model->index(0, 3)), QVariant());
        QCOMPARE(model->data(model->index(0, 3)), QVariant());
    }

    delete  model;
}
//------------------------------------------------------------------------------
void TestGui::testEditTaskPerformance()
{
    TaskTableModel *model = new TaskTableModel;

    window->ui->tableView->setModel(model);

    QBENCHMARK
    {
        QString timeDate = "22:00 12.01.2024";
        QString title = "Подъем";
        bool status = false;

        model->addTask(timeDate, title, status);

        QString timeDate2 = "13:00 16.01.2024";
        QString title2 = "Task";
        bool status2 = true;

        bool timeDateChange = model->setData(model->index(0, 0), timeDate2, Qt::EditRole);
        QVERIFY(timeDateChange);

        bool titleChange = model->setData(model->index(0, 1), title2, Qt::EditRole);
        QVERIFY(titleChange);

        bool statusChange = model->setData(model->index(0, 2), status2, Qt::EditRole);
        QVERIFY(statusChange);

        QCOMPARE(model->data(model->index(0, 0), Qt::DisplayRole).toString(), timeDate2);
        QCOMPARE(model->data(model->index(0, 1), Qt::DisplayRole).toString(), title2);
        QCOMPARE(model->data(model->index(0, 2), Qt::DisplayRole).toBool(), status2);
    }

    delete model;
}
//------------------------------------------------------------------------------
QTEST_MAIN(TestGui)

#include "tst_testgui.moc"
