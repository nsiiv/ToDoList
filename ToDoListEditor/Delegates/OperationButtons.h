#ifndef OPERATIONBUTTONS_H
#define OPERATIONBUTTONS_H
//------------------------------------------------------------------------------
#include <QtWidgets/QStyledItemDelegate>

class TaskTableView;
class QPushButton;
//------------------------------------------------------------------------------
class OperationButtons : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit OperationButtons(TaskTableView *tableView, QWidget* parent = nullptr);
    ~OperationButtons();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
    void editTask(const QModelIndex &idnex);
    void deleteTask(const QModelIndex &index);

public slots:
    void onHoverIndexChanged(const QModelIndex &index);

private:
    TaskTableView* m_taskTableView;
    QPoint m_mousePoint;
    QScopedPointer<QPushButton> m_editButton;
    QScopedPointer<QPushButton> m_deleteButton;

    int m_nType;
    int hover_row;
    QStringList m_list;
    QList<QImage> m_imageList;
};
//------------------------------------------------------------------------------
#endif // OPERATIONBUTTONS_H
