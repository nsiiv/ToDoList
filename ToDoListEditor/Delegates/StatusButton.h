#ifndef STATUSBUTTON_H
#define STATUSBUTTON_H
//------------------------------------------------------------------------------
#include <QtWidgets/QStyledItemDelegate>
//------------------------------------------------------------------------------
class StatusButton : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit StatusButton(QWidget *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index);

private:
    // Style
    QColor m_doneBtnColor;
    QColor m_notDoneBtnColor;
};
//------------------------------------------------------------------------------
#endif // STATUSBUTTON_H
