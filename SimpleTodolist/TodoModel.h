#pragma once

#include <QAbstractListModel>
#include <QVector>

#include "TodoItem.h"

// Todo模型，给QML中的list提供模型
class TodoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // 普通枚举类型，有时间可以使用class -- enhancement
    enum TodoRoles
    {
        TitleRole = Qt::UserRole + 1, // 这个用来代表标题，从Qt内置角色最大编号+1开始
                                      // 类似ID的作用了
        CompletedRole
    };

    explicit TodoModel(QObject *parent = nullptr);

    // 必须实现的方法
    int rowCount(
        const QModelIndex &parent = QModelIndex()
        ) const override;

    QVariant data(
        const QModelIndex &index,
        int role = Qt::DisplayRole
        ) const override;

    QHash<int, QByteArray> roleNames() const override;

    // todo操作，增删改查
    void addTodo(const QString &title);

    void removeTodo(int index);

    void toggleTodo(int index);

    void clear();

    // 获取 Todo list中所有的内容
    const QVector<TodoItem>& items() const;

    // 设置 Todo list中所有内容
    void setItems(const QVector<TodoItem>& items);

private:

    QVector<TodoItem> m_items;
};