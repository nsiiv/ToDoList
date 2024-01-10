#include "OperationButtons.h"

#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>

#include "../ToDoListEditor/TaskTableView.h"
//------------------------------------------------------------------------------
OperationButtons::OperationButtons(TaskTableView *tableView, QWidget *parent)
    : QStyledItemDelegate(parent)
    , m_taskTableView(tableView)
    , m_editButton(new QPushButton)
    , m_deleteButton(new QPushButton)
{
    m_list << "Edit" << "Delete";
    m_imageList << QImage(":/Icons/editing.png") << QImage(":/Icons/delete.png");

    hover_row = -1;
}
//------------------------------------------------------------------------------
OperationButtons::~OperationButtons()
{
    delete m_taskTableView;
}
//------------------------------------------------------------------------------
void OperationButtons::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);

    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    if (index.row() == hover_row)
    {
        viewOption.state |= QStyle::State_MouseOver;
    }
    QStyledItemDelegate::paint(painter, viewOption, index);

    if (index.column() == 3)
    {
        int nCount = 2;
        int nHalf = (option.rect.width() - 25 * nCount - 5 * (nCount - 1)) / 2;
        int nTop = (option.rect.height() - 25) / 2;

        for (int i = 0; i < nCount; ++i)
        {
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() + nHalf + 25 * i + 5 * i,
                option.rect.top() + nTop, 25, 20);
            QRect imageRect = button.rect;
            imageRect.adjust(4, 4, -4, -4);

            button.state |= QStyle::State_Enabled;

            if (button.rect.contains(m_mousePoint))
            {
                if (m_nType == 0)
                    button.state |= QStyle::State_MouseOver;
                else if (m_nType == 1)
                    button.state |= QStyle::State_Sunken;
            }

            QWidget *pWidget = (i == 0) ? m_editButton.data() : m_deleteButton.data();
            QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, pWidget);
            painter->drawImage(imageRect, m_imageList[i]);
        }
    }
}
//------------------------------------------------------------------------------
bool OperationButtons::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(model)

    if (index.column() != 3)
        return false;

        m_nType = -1;
        bool bRepaint = false;
        QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
        m_mousePoint = pEvent->pos();

        int nCount = 2;
        int nHalf = (option.rect.width() - 25 * nCount - 5 * (nCount - 1)) / 2;
        int nTop = (option.rect.height() - 20) / 2;

        QApplication::restoreOverrideCursor();

        for (int i = 0; i < nCount; ++i) {
            QStyleOptionButton button;
            button.rect = QRect(option.rect.left() + nHalf + 25 * i + 5 * i,
                option.rect.top() + nTop, 25, 20);

            if (!button.rect.contains(m_mousePoint))
                continue;

            bRepaint = true;
            switch (event->type())
            {
                case QEvent::MouseMove:
                {
                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                    m_nType = 0;
                    break;
                }
                case QEvent::MouseButtonPress:
                {
                    m_nType = 1;
                    break;
                }
                case QEvent::MouseButtonRelease:
                {
                    if (i == 0)
                        emit editTask(index);
                    else
                        emit deleteTask(index);

                    break;
                }
                default:
                    break;
            }
        }

        return bRepaint;
}
//------------------------------------------------------------------------------
void OperationButtons::onHoverIndexChanged(const QModelIndex &index)
{
    hover_row = index.row();
    m_taskTableView->viewport()->update();
}
//------------------------------------------------------------------------------
