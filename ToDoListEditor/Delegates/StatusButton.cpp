#include "StatusButton.h"

#include <QPainter>
#include <QMouseEvent>
//------------------------------------------------------------------------------
StatusButton::StatusButton(QWidget *parent)
    : QStyledItemDelegate(parent)
{
    // on common style
    m_doneBtnColor    = Qt::green;
    m_notDoneBtnColor = Qt::red;
}
//------------------------------------------------------------------------------
void StatusButton::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    QRect btnRect = option.rect.adjusted(7, 2, -7, -2);

    QColor btnColor = m_doneBtnColor;

    QString statusText = "Done";

    if (index.data(Qt::DisplayRole).toBool())
    {
        btnColor = m_notDoneBtnColor;
        statusText = "Not done";
    }

    painter->fillRect(btnRect, btnColor);

    // draw text
    painter->drawText(btnRect, Qt::AlignCenter, statusText);
}
//------------------------------------------------------------------------------
bool StatusButton::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (option.rect.contains(mouseEvent->pos()))
        {
            bool currentState = index.data(Qt::DisplayRole).toBool();
            model->setData(index, !currentState, Qt::EditRole);
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
//------------------------------------------------------------------------------
