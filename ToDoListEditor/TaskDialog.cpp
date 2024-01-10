#include <QDebug>

#include "../ToDoListEditor/TaskDialog.h"
#include "../ToDoListEditor/ui_TaskDialog.h"

TaskDialog::TaskDialog(QWidget *parent, TaskMode taskMode) :
    QDialog(parent),
    ui(new Ui::TaskDialog),
    m_taskMode(taskMode)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    preInitTaskDialog(m_taskMode);
}
//------------------------------------------------------------------------------
TaskDialog::~TaskDialog()
{
    delete ui;
}
//------------------------------------------------------------------------------
TaskDialog::TaskMode TaskDialog::taskMode() const
{
    return m_taskMode;
}

QCalendarWidget *TaskDialog::calendarWidget()
{
    return ui->cwCalendar;
}
//------------------------------------------------------------------------------
QString TaskDialog::getTime() const
{
    return ui->teTime->time().toString("HH:mm");
}
//------------------------------------------------------------------------------
QString TaskDialog::minimumTime() const
{
    return ui->teTime->minimumTime().toString("HH:mm");
}
//------------------------------------------------------------------------------
bool TaskDialog::timeEditorIsReadOnly() const
{
    return ui->teTime->isReadOnly();
}
//------------------------------------------------------------------------------
void TaskDialog::setTime(const QString &time)
{
    QDateTime dateTime = QDateTime::fromString(time, "HH:mm");
//    QDate curentDate = QDate::currentDate();

//    if(m_dateTime.date() >= curentDate)
//    {
        ui->teTime->setTime(dateTime.time());
//    }
}
//------------------------------------------------------------------------------
QString TaskDialog::getDate() const
{
    return ui->cwCalendar->selectedDate().toString("dd.MM.yyyy");
}
//------------------------------------------------------------------------------
QString TaskDialog::minimumDate() const
{
    return ui->cwCalendar->minimumDate().toString("dd.MM.yyyy");
}
//------------------------------------------------------------------------------
void TaskDialog::setDate(const QString &date)
{
    QDateTime dateTime = QDateTime::fromString(date, "dd.MM.yyyy");

    ui->cwCalendar->setSelectedDate(dateTime.date());
}
//------------------------------------------------------------------------------
QString TaskDialog::getTitle() const
{
    return ui->leTitle->text();
}
//------------------------------------------------------------------------------
bool TaskDialog::titleIsReadOnly() const
{
    return ui->leTitle->isReadOnly();
}
//------------------------------------------------------------------------------

//QString removeExtraSpaces(const QString& str)
//{
//    QString result = str.simplified(); // Удаляем лишние пробелы в начале и конце строки и заменяем последовательности пробелов одним пробелом
//    result.replace(QRegularExpression("\\s+"), " "); // Заменяем все последовательности пробелов одним пробелом
//    return result;
//}

void TaskDialog::setTitle(const QString &title)
{
    try
    {
        if (!title.isEmpty())
        {
            QString curTitle = title.simplified();
            curTitle.replace(QRegularExpression("\\s+"), " ");
            ui->leTitle->setText(curTitle);
        }
        else
          throw std::runtime_error("Empty title");
      }
    catch (const std::exception& e)
    {
        qDebug() << "Exception caught: " << e.what();
    }
}
//------------------------------------------------------------------------------
QString TaskDialog::getDescription() const
{
    return ui->teDescription->toPlainText();
}
//------------------------------------------------------------------------------
bool TaskDialog::descriptionIsReadOnly() const
{
    return ui->teDescription->isReadOnly();
}
//------------------------------------------------------------------------------
void TaskDialog::setDescription(const QString &descr)
{
    ui->teDescription->setText(descr);
}
//------------------------------------------------------------------------------
bool TaskDialog::applyButtonIsEnabled() const
{
    return ui->pbApply->isEnabled();
}
//------------------------------------------------------------------------------
void TaskDialog::on_leTitle_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || arg1.trimmed().isEmpty())
    {
        ui->leTitle->setStyleSheet("QLineEdit {border: 1px solid red;}");
        ui->pbApply->setEnabled(false);
    }
    else
    {
        ui->leTitle->setStyleSheet("");
        ui->pbApply->setEnabled(true);
    }
}
//------------------------------------------------------------------------------
void TaskDialog::on_teTime_timeChanged(const QTime &time)
{
    m_dateTime.setTime(time);
}
//------------------------------------------------------------------------------
void TaskDialog::on_cwCalendar_selectionChanged()
{
    m_dateTime.setDate(ui->cwCalendar->selectedDate());

    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    if (m_dateTime.date() == currentDate)
        ui->teTime->setMinimumTime(currentTime);
    else
        ui->teTime->setMinimumTime(QTime(0, 0, 0));
}
//------------------------------------------------------------------------------
void TaskDialog::on_pbApply_clicked()
{
    QDialog::accept();
}
//------------------------------------------------------------------------------
void TaskDialog::on_pbCancel_clicked()
{
    QDialog::reject();
}
//------------------------------------------------------------------------------
void TaskDialog::preInitTaskDialog(TaskDialog::TaskMode TaskMode)
{
    switch (TaskMode)
    {
    case NewTask:
    {
        initNoMode();
        break;
    }
    case EditMode:
    {
        setWindowTitle("Edit task");
        break;
    }
    case ShowMode:
    {
        initShowMode();
        break;
    }
    default:
        break;
    }
}
//------------------------------------------------------------------------------
void TaskDialog::initNoMode()
{
    setWindowTitle("Add a new task");

    // Calendar
    const auto date = QDate::currentDate();
    ui->cwCalendar->setSelectedDate(date);
    ui->cwCalendar->setMinimumDate(date);

    // Time
    const auto time = QTime::currentTime();
    ui->teTime->setTime(time);    
    ui->teTime->setMinimumTime(time);

    ui->leTitle->setValidator(new QRegExpValidator(QRegExp(".+"), this));

    ui->pbApply->setEnabled(false);
}
//------------------------------------------------------------------------------
void TaskDialog::initShowMode()
{
    setWindowTitle("Show task");
    ui->leTitle->setReadOnly(true);
    ui->teTime->setReadOnly(true);
    ui->teDescription->setReadOnly(true);
    ui->cwCalendar->setSelectionMode(QCalendarWidget::NoSelection);
}
//------------------------------------------------------------------------------
