#include "TaskTableModel.h"
//------------------------------------------------------------------------------
TaskTableModel::TaskTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_rowCount = 0;
    m_columnCount = 5;
}
//------------------------------------------------------------------------------
TaskTableModel::~TaskTableModel()
{
}
//------------------------------------------------------------------------------
void TaskTableModel::addTask(const QString &timeDate, const QString &title, const bool &status)
{   
    if(title.isEmpty() || title.trimmed().isEmpty() || timeDate.isEmpty())
        return;

    insertRows(m_rowCount, 1);
    QVector<QVariant>* data = new QVector<QVariant>(m_columnCount);

    data->replace(0, timeDate);
    data->replace(1, title);
    data->replace(2, status);
    m_data.append(data);
}
//------------------------------------------------------------------------------
void TaskTableModel::deleteTask(const QModelIndex &index)
{
    if(index.isValid())
        removeRows(index.row(), 1);
}
//------------------------------------------------------------------------------
int TaskTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}
//------------------------------------------------------------------------------
int TaskTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}
//------------------------------------------------------------------------------
QVariant TaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();        

    if(orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0: return "Time";      break;
        case 1: return "Title";     break;
        case 2: return "Status";    break;
        case 3: return "Operation"; break;
        case 4: return "Action";    break;
        default:
            return "";              break;
        }
    }

    return  QVariant();
}
//------------------------------------------------------------------------------
QVariant TaskTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_data[index.row()]->at(index.column());

    if(role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    return QVariant();
}
//------------------------------------------------------------------------------
bool TaskTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if(role == Qt::EditRole)
    {
        m_data[index.row()]->replace(index.column(), value);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------
bool TaskTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    m_rowCount++;

    endInsertRows();

    return true;
}
//------------------------------------------------------------------------------
bool TaskTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 )
        return false;

    beginRemoveRows(parent, row, row + count - 1);

    for(int i = 0; i < count; i++)
        m_data.removeAt(row);

    m_rowCount -= count;

    endRemoveRows();

    return true;
}
//------------------------------------------------------------------------------
