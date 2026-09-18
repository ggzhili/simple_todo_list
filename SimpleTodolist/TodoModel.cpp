#include "TodoModel.h"

TodoModel::TodoModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

// 返回多少行
int TodoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_items.size();
}

// 返回数据，角色不同返回的数据不同
QVariant TodoModel::data(
    const QModelIndex &index,
    int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() < 0 ||
        index.row() >= m_items.size())
    {
        return {};
    }

    const TodoItem &item = m_items.at(index.row());

    switch (role)
    {
    case TitleRole:
        return item.title;

    case CompletedRole:
        return item.completed;

    default:
        return {};
    }
}

QHash<int, QByteArray> TodoModel::roleNames() const
{
    return {
        { TitleRole, "title" },
        { CompletedRole, "completed" }
    };
}

void TodoModel::addTodo(const QString &title)
{
    if (title.trimmed().isEmpty())
        return;

    const int newRow = m_items.size();

    beginInsertRows(
        QModelIndex(),
        newRow,
        newRow
        );

    TodoItem item;
    item.title = title.trimmed();
    item.completed = false;

    m_items.append(item);

    endInsertRows();
}

void TodoModel::removeTodo(int index)
{
    if (index < 0 || index >= m_items.size())
        return;

    beginRemoveRows(
        QModelIndex(),
        index,
        index
        );

    m_items.removeAt(index);

    endRemoveRows();
}

void TodoModel::toggleTodo(int index)
{
    if (index < 0 || index >= m_items.size())
        return;

    TodoItem &item = m_items[index];

    item.completed = !item.completed;

    QModelIndex modelIndex = this->index(index);

    emit dataChanged(
        modelIndex,
        modelIndex,
        { CompletedRole }
        );
}


void TodoModel::clear()
{
    beginResetModel();

    m_items.clear();

    endResetModel();
}

const QVector<TodoItem>& TodoModel::items() const
{
    return m_items;
}

void TodoModel::setItems(
    const QVector<TodoItem>& items)
{
    beginResetModel();

    m_items = items;

    endResetModel();
}