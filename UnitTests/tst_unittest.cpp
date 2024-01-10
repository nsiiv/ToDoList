#include <QtTest>

#include "../ToDoListEditor/TaskTableModel.h"
//------------------------------------------------------------------------------
class UnitTest : public QObject
{
    Q_OBJECT

private slots:
    void testAddTask_data();
    void testAddTask();

    void testDeleteTask();

    void testEditTask_data();
    void testEditTask();
};
//------------------------------------------------------------------------------
// Private Slots
//------------------------------------------------------------------------------
void UnitTest::testAddTask_data()
{
    QTest::addColumn<QString>("timeDate");
    QTest::addColumn<QString>("title");
    QTest::addColumn<bool>("status");

    // Valid tests
    QTest::newRow("ValidTaskTest1")  << "7:00 06.01.2024"   << "Подъем"     << true;
    QTest::newRow("ValidTaskTest2")  << "7:15 06.01.2024"   << "Зарядка"    << false;
    QTest::newRow("ValidTaskTest3")  << "7:30 06.01.2024"   << "Завтрак"    << true;
    QTest::newRow("ValidTaskTest4")  << "7:50 06.01.2024"   << "На работу"  << true;
    QTest::newRow("ValidTaskTest5")  << "14:30 06.01.2024"  << "Обед"       << true;
    QTest::newRow("ValidTaskTest6")  << "18:00 06.01.2024"  << "Домой"      << false;
    QTest::newRow("ValidTaskTest7")  << "19:00 06.01.2024"  << "Ужин"       << false;
    QTest::newRow("ValidTaskTest8")  << "19:30 06.01.2024"  << "Test 1"     << false;
    QTest::newRow("ValidTaskTest9")  << "22:00 06.01.2024"  << "Test"       << false;
    QTest::newRow("ValidTaskTest10") << "23:00 06.01.2024"  << "Сон"        << false;

    // Invalid tests
    QTest::newRow("InvalidTaskTest1") << "16:00 06.01.2024"  << "" << false;
    QTest::newRow("InvalidTaskTest2") << "23:00 06.01.2024"  << " " << true;
    QTest::newRow("InvalidTaskTest3") << ""  << "test" << true;
}
//------------------------------------------------------------------------------
void UnitTest::testAddTask()
{
    QFETCH(QString, timeDate);
    QFETCH(QString, title);
    QFETCH(bool, status);

    TaskTableModel *m_model = new TaskTableModel;

    int row = m_model->rowCount();

    m_model->addTask(timeDate, title, status);

    QCOMPARE(m_model->rowCount(), row + 1);

    int newRow = m_model->rowCount() - 1;

    QCOMPARE(m_model->data(m_model->index(newRow, 0), Qt::DisplayRole).toString(), timeDate);
    QCOMPARE(m_model->data(m_model->index(newRow, 1), Qt::DisplayRole).toString(), title);
    QCOMPARE(m_model->data(m_model->index(newRow, 2), Qt::DisplayRole).toBool(), status);

    delete m_model;
}
//------------------------------------------------------------------------------
void UnitTest::testDeleteTask()
{
    TaskTableModel *m_model = new TaskTableModel;

    m_model->addTask("14:30 06.01.2024", "Test1", false);
    m_model->addTask("16:30 06.01.2024", "Test2", false);
    m_model->addTask("19:30 06.01.2024", "Test3", false);

    QCOMPARE(m_model->rowCount(), 3);

    m_model->deleteTask(m_model->index(2, 3));
    QCOMPARE(m_model->rowCount(), 2);

    QCOMPARE(m_model->data(m_model->index(2, 3)), QVariant());

    m_model->deleteTask(m_model->index(0, 0));
    m_model->deleteTask(m_model->index(0, 0));
    QCOMPARE(m_model->rowCount(), 0);

    delete m_model;
}
//------------------------------------------------------------------------------
void UnitTest::testEditTask_data()
{
    QTest::addColumn<QString>("timeDateEdit");
    QTest::addColumn<QString>("titleEdit");
    QTest::addColumn<bool>("statusEdit");

    // Valid tests
    QTest::newRow("EditTaskTest1") << "7:00 06.01.2024" << "Test"  << true;
    QTest::newRow("EditTaskTest2") << "7:00 06.01.2024" << "Test2" << true;
    QTest::newRow("EditTaskTest3") << "7:00 06.01.2024" << "Test3" << true;

    // Invalid tests
    QTest::newRow("EditTaskTest4") << "16:00 06.01.2024"  << ""     << false;
    QTest::newRow("EditTaskTest5") << "23:00 06.01.2024"  << " "    << true;
    QTest::newRow("EditTaskTest6") << ""                  << "test" << true;
}
//------------------------------------------------------------------------------
void UnitTest::testEditTask()
{
    QFETCH(QString, timeDateEdit);
    QFETCH(QString, titleEdit);
    QFETCH(bool, statusEdit);

    TaskTableModel *m_model = new TaskTableModel;

    m_model->addTask("14:30 06.01.2024", "TestTask1", false);

    bool timeDateChange = m_model->setData(m_model->index(0, 0), timeDateEdit, Qt::EditRole);
    QVERIFY(timeDateChange);

    bool titleChange = m_model->setData(m_model->index(0, 1), titleEdit, Qt::EditRole);
    QVERIFY(titleChange);

    bool statusChange = m_model->setData(m_model->index(0, 2), statusEdit, Qt::EditRole);
    QVERIFY(statusChange);

    QCOMPARE(m_model->data(m_model->index(0, 0), Qt::DisplayRole).toString(), timeDateEdit);
    QCOMPARE(m_model->data(m_model->index(0, 1), Qt::DisplayRole).toString(), titleEdit);
    QCOMPARE(m_model->data(m_model->index(0, 2), Qt::DisplayRole).toBool(), statusEdit);

    delete m_model;
}
//------------------------------------------------------------------------------
QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
