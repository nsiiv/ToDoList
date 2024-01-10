#ifndef TASKDIALOG_H
#define TASKDIALOG_H
//------------------------------------------------------------------------------
#include <QDialog>

#include <QDateTime>

class QCalendarWidget;
//------------------------------------------------------------------------------
namespace Ui {
class TaskDialog;
}
//------------------------------------------------------------------------------
class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    enum TaskMode
    {
        NewTask,
        ShowMode,
        EditMode
    };

    explicit TaskDialog(QWidget *parent = nullptr, TaskMode taskMode = TaskMode::NewTask);
    ~TaskDialog();

    TaskMode taskMode() const;

    QCalendarWidget* calendarWidget();

    QString getTime() const;
    QString minimumTime() const;
    bool timeEditorIsReadOnly() const;
    void setTime(const QString &time);

    QString getDate() const;
    QString minimumDate() const;
    void setDate(const QString &date);

    QString getTitle() const;
    bool titleIsReadOnly() const;
    void setTitle(const QString &title);

    QString getDescription() const;
    bool descriptionIsReadOnly() const;
    void setDescription(const QString &descr);

    bool applyButtonIsEnabled() const;

private slots:
    void on_leTitle_textChanged(const QString &arg1);
    void on_teTime_timeChanged(const QTime &time);
    void on_cwCalendar_selectionChanged();
    void on_pbApply_clicked();
    void on_pbCancel_clicked();

private:
    Ui::TaskDialog *ui;
    TaskMode m_taskMode;
    QDateTime m_dateTime;

    void preInitTaskDialog(TaskMode TaskMode);
    void initNoMode();
    void initShowMode();
};
//------------------------------------------------------------------------------
#endif // TASKDIALOG_H
