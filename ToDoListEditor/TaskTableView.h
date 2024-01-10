#ifndef TASKTABLEVIEW_H
#define TASKTABLEVIEW_H
//------------------------------------------------------------------------------
#include <QtWidgets/QTableView>
//------------------------------------------------------------------------------
class TaskTableView : public QTableView
{
    Q_OBJECT
public:
    explicit TaskTableView(QWidget* parent = nullptr);
    ~TaskTableView();

signals:
    void hoverIndexChanged(const QModelIndex& index);

protected:
    void mouseMoveEvent(QMouseEvent* event);
};
//------------------------------------------------------------------------------
#endif // TASKTABLEVIEW_H
