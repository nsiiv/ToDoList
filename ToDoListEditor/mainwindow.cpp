#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
//#include <QSqlError>
#include <QCloseEvent>

#include "../ToDoListEditor/TaskTableModel.h"
#include "../ToDoListEditor/TaskDialog.h"
//#include "CloseWindowDialog.h"

#include "../ToDoListEditor/Delegates/OperationButtons.h"
#include "../ToDoListEditor/Delegates/StatusButton.h"
#include "../ToDoListEditor/Delegates/ShowTaskButton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ToDo List");

    m_taskModel = new TaskTableModel(this);

    // Delegates
    m_optionBtn   = new OperationButtons(ui->tableView);
    m_statusBtn   = new StatusButton(ui->tableView);
    m_showTaskBtn = new ShowTaskButton(ui->tableView);

    ui->tableView->setModel(m_taskModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setItemDelegateForColumn(2, m_statusBtn);
    ui->tableView->setItemDelegateForColumn(3, m_optionBtn);
    ui->tableView->setItemDelegateForColumn(4, m_showTaskBtn);

    connect(ui->tableView, &TaskTableView::hoverIndexChanged, m_optionBtn,   &OperationButtons::onHoverIndexChanged);
    connect(ui->tableView, &TaskTableView::hoverIndexChanged, m_showTaskBtn, &ShowTaskButton::onHoverIndexChanged);

    connect(m_taskModel, &TaskTableModel::dataChanged, this, &MainWindow::onSaveStatusChanged);

    connect(m_optionBtn,   &OperationButtons::editTask,   this, &MainWindow::onEditClicked);
    connect(m_optionBtn,   &OperationButtons::deleteTask, this, &MainWindow::onDeleteClicked);
    connect(m_showTaskBtn, &ShowTaskButton::showTask,     this, &MainWindow::onShowButtonClicked);

//    ui->lblLog->setText("Select database");
//    /**
//     * @todo add auto connect database
//     */
//    QDir file = QDir(QCoreApplication::applicationDirPath());
//    filePath = file.path() + "/Tasks_DB.db";
//    qDebug() << filePath;

//    testInit(filePath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbNewTask_clicked()
{
    TaskDialog* taskDialog = new TaskDialog(this);
    if(taskDialog->exec() == QDialog::Accepted)
    {
        QString dateTime = taskDialog->getTime() + " " + taskDialog->getDate();

        m_taskModel->addTask(dateTime, taskDialog->getTitle(), false);

         m_descrData.insert(m_taskModel->rowCount() - 1,
                            taskDialog->getDescription());
    }

    delete  taskDialog;
}

void MainWindow::onEditClicked(const QModelIndex &index)
{
    QString date = m_taskModel->data(m_taskModel->index(index.row(), 0)).toString();
    QString title = m_taskModel->data(m_taskModel->index(index.row(), 1)).toString();
    QString descr = m_descrData[index.row()];

    TaskDialog* taskDialog = new TaskDialog(this, TaskDialog::EditMode);
    QDateTime time = QDateTime::fromString(date, "HH:mm");
    QDateTime dateTime = QDateTime::fromString("dd.MM.yyyy");

    taskDialog->setTime(time.time().toString("HH:mm"));
    taskDialog->setDate(dateTime.date().toString("dd.MM.yyyy"));
    taskDialog->setTitle(title);
    taskDialog->setDescription(descr);

    if(taskDialog->exec() == QDialog::Accepted)
    {
        QString dateTime_ = taskDialog->getTime() + " " + taskDialog->getDate();
        m_taskModel->setData(m_taskModel->index(index.row(), 0), dateTime_);
        m_taskModel->setData(m_taskModel->index(index.row(), 1), taskDialog->getTitle());
        m_descrData.insert(index.row(), taskDialog->getDescription());
    }

    delete  taskDialog;
}

void MainWindow::onDeleteClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    m_taskModel->deleteTask(index);
    m_descrData.remove(index.row());

    qDebug() << "Delete row: " << m_taskModel->rowCount();
}

void MainWindow::onShowButtonClicked(const QModelIndex &index)
{
    QString date = m_taskModel->data(m_taskModel->index(index.row(), 0)).toString();
    QString title = m_taskModel->data(m_taskModel->index(index.row(), 1)).toString();
    QString descr = m_descrData[index.row()];

    TaskDialog* taskDialog = new TaskDialog(this, TaskDialog::ShowMode);
    QDateTime time = QDateTime::fromString(date, "HH:mm");
    QDateTime dateTime = QDateTime::fromString("dd.MM.yyyy");

    taskDialog->setTime(time.time().toString("HH:mm"));
    taskDialog->setDate(dateTime.date().toString("dd.MM.yyyy"));
    taskDialog->setTitle(title);
    taskDialog->setDescription(descr);
    if(taskDialog->exec() == QDialog::Accepted)
    {
    }

    delete  taskDialog;
}

void MainWindow::onSaveStatusChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(topLeft)
    Q_UNUSED(bottomRight)

    m_isSave = false;
}

void MainWindow::on_actionNew_triggered()
{
//    QString file = QFileDialog::getOpenFileName(this, "Select destination SQLite file",
//                                                "",
//                                                "SQLite File (*.sqlite *.db)");

//    if(file.isEmpty())
//        return;

//    m_sqlite = QSqlDatabase::addDatabase("QSQLITE", "SQLiteConn");
//    m_sqlite.setDatabaseName(file);

//    if(m_sqlite.open())
//    {
//        ui->lblLog->setText("Ready");
//    }
//    else
//    {
//        ui->lblLog->setText("Error: " + m_query.lastError().text());
//    }

//    m_query = QSqlQuery(m_sqlite);
}

void MainWindow::on_saveAction_triggered()
{
//    int count = 0;
//    m_query.exec("SELECT COUNT(*) FROM Tasks");

//    while (m_query.next())
//    {
//        count = m_query.value(0).toInt();
//    }

//    if(count > 0)
//    {
//        m_query.prepare("DELETE FROM Tasks");
//        m_query.exec();
//    }

//    m_query.prepare("INSERT INTO Tasks(date, title, status, description) VALUES(:date, :title, :status, :description)");

//    for(int i = 0; i < m_taskModel->rowCount(); i++)
//    {
//        QString date   = m_taskModel->data(m_taskModel->index(i, 0)).toString();
//        QString title  = m_taskModel->data(m_taskModel->index(i, 1)).toString();
//        QString status = m_taskModel->data(m_taskModel->index(i, 2)).toString();
//        QString descr = m_descrData[i];
//        m_query.bindValue(":date", date);
//        m_query.bindValue(":title", title);
//        m_query.bindValue(":status", status);
//        m_query.bindValue(":description", descr);
//        m_query.exec();
//    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    if(m_isSave)
//        return;

//    CloseWindowDialog* d = new CloseWindowDialog(this);

//    if(m_sqlite.open())
//    {
//        if(d->exec() == QDialog::Accepted)
//        {
//            on_saveAction_triggered();
//            event->accept();
//            return;
//        }
//        event->ignore();
//    }

//    delete  d;
}

void MainWindow::testInit(QString file)
{
//    if(file.isEmpty())
//        return;

//    m_sqlite = QSqlDatabase::addDatabase("QSQLITE", "SQLiteConn");
//    m_sqlite.setDatabaseName(file);

//    if(m_sqlite.open())
//    {
//        ui->lblLog->setText("Ready");
//        m_query = QSqlQuery(m_sqlite);
//        loadTasksData();
//    }
//    else
//    {
//        ui->lblLog->setText("Error: " + m_query.lastError().text());
//    }
}

void MainWindow::loadTasksData()
{
//    m_query.exec("SELECT * FROM Tasks");

//    int i = 0;
//    while(m_query.next())
//    {
//        QString date  = m_query.value("date").toString();
//        QString title = m_query.value("title").toString();
//        bool status   = m_query.value("status").toBool();
//        QString descr = m_query.value("description").toString();

//        m_taskModel->addTask(date, title, status);
//        m_descrData.insert(i, descr);

//        i++;
//    }
}
