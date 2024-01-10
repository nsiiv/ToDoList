#ifndef SHOWTASKBUTTON_H
#define SHOWTASKBUTTON_H
//------------------------------------------------------------------------------
#include <QtWidgets/QStyledItemDelegate>

class TaskTableView;
class QPushButton;
//------------------------------------------------------------------------------
class ShowTaskButton : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ShowTaskButton(TaskTableView *tableView, QWidget* parent = nullptr);
    ~ShowTaskButton();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
    void showTask(const QModelIndex &index);

public slots:
    void onHoverIndexChanged(const QModelIndex &index);

private:
    TaskTableView* m_taskTableView;
    QPoint m_mousePoint;
    QScopedPointer<QPushButton> m_showButton;

    int m_nType;
    int hover_row;
};
//------------------------------------------------------------------------------
#endif // SHOWTASKBUTTON_H
