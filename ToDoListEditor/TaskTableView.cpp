#include "TaskTableView.h"

#include <QMouseEvent>
//------------------------------------------------------------------------------
TaskTableView::TaskTableView(QWidget *parent)
    : QTableView(parent)
{
}
//------------------------------------------------------------------------------
TaskTableView::~TaskTableView()
{
}
//------------------------------------------------------------------------------
void TaskTableView::mouseMoveEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    emit hoverIndexChanged(index);
    QTableView::mouseMoveEvent(event);
}
//------------------------------------------------------------------------------
