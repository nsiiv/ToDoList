#include "ShowTaskButton.h"

#include <QPushButton>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

#include "../ToDoListEditor/TaskTableView.h"
//------------------------------------------------------------------------------
ShowTaskButton::ShowTaskButton(TaskTableView *tableView, QWidget *parent)
    : QStyledItemDelegate(parent)
    , m_taskTableView(tableView)
    , m_showButton(new QPushButton)
{
    hover_row = -1;
}
//------------------------------------------------------------------------------
ShowTaskButton::~ShowTaskButton()
{
    delete m_taskTableView;
}
//------------------------------------------------------------------------------
void ShowTaskButton::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() != 4)
        return;

    QStyleOptionViewItem viewOption(option);

    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    if (index.row() == hover_row)
    {
        viewOption.state |= QStyle::State_MouseOver;
    }

    QStyledItemDelegate::paint(painter, viewOption, index);

    // Painting
    QStyleOptionButton button;
    button.rect = option.rect;
    button.text = QString("Show");
    button.state |= QStyle::State_Enabled;

    if (button.rect.contains(m_mousePoint))
    {
        if (m_nType == 0)
            button.state |= QStyle::State_MouseOver;
        else if (m_nType == 1)
            button.state |= QStyle::State_Sunken;
    }

    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, m_showButton.data());
}
//------------------------------------------------------------------------------
bool ShowTaskButton::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(model)

    if (index.column() != 4)
        return false;

    m_nType = -1;
    bool bRepaint = false;
    QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
    m_mousePoint = pEvent->pos();

    QApplication::restoreOverrideCursor();

    QStyleOptionButton button;
    button.rect = option.rect;

    if (button.rect.contains(m_mousePoint))
    {
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
                emit showTask(index);
                break;
            }
            default:
                break;
        }
    }

    return bRepaint;
}
//------------------------------------------------------------------------------
void ShowTaskButton::onHoverIndexChanged(const QModelIndex &index)
{
    hover_row = index.row();
    m_taskTableView->viewport()->update();
}
//------------------------------------------------------------------------------
