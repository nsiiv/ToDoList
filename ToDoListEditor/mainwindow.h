#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <QSqlDatabase>
//#include <QSqlQuery>
#include <QMap>

class TaskTableModel;
class OperationButtons;
class StatusButton;
class ShowTaskButton;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class TestGui;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbNewTask_clicked();
    void onEditClicked(const QModelIndex &index);
    void onDeleteClicked(const QModelIndex &index);
    void onShowButtonClicked(const QModelIndex &index);
    void onSaveStatusChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    void on_actionNew_triggered();
    void on_saveAction_triggered();

private:
    Ui::MainWindow *ui;
    TaskTableModel* m_taskModel;
    // Delegates
    OperationButtons *m_optionBtn;
    StatusButton     *m_statusBtn;
    ShowTaskButton   *m_showTaskBtn;

//    QSqlDatabase m_sqlite;
//    QSqlQuery m_query;

    QMap<int, QString> m_descrData;
    QString filePath;

    bool m_isSave = true;

    void closeEvent(QCloseEvent *event);

    void testInit(QString file);

    void loadTasksData();
};
#endif // MAINWINDOW_H
