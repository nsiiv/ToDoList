#ifndef TASKTABLEMODEL_H
#define TASKTABLEMODEL_H
//------------------------------------------------------------------------------
#include <QtCore/QAbstractTableModel>
//------------------------------------------------------------------------------
class TaskTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TaskTableModel(QObject *parent = nullptr);
    ~TaskTableModel();

    void addTask(const QString &timeDate, const QString &title, const bool &status);
    void deleteTask(const QModelIndex &index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    QVector<QVector<QVariant>*> m_data;
    int m_columnCount;
    int m_rowCount;
};
//------------------------------------------------------------------------------
#endif // TASKTABLEMODEL_H
