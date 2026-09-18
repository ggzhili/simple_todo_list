#pragma once

// 时间紧任务重
// 设计取舍： 将Model的工作直接交给Manager来实现
// 类似数据库那种增删改查

// ----- 属于是业务层 ----
// 其实就是负责弄一下持久化的问题

#include <QObject>
#include <QString>

class TodoModel;

class TodoManager : public QObject
{
    Q_OBJECT

public:

    explicit TodoManager(
        TodoModel *model,
        QObject *parent = nullptr
        );

    Q_INVOKABLE void addTodo(
        const QString &title
        );

    Q_INVOKABLE void removeTodo(
        int index
        );

    Q_INVOKABLE void toggleTodo(
        int index
        );

    Q_INVOKABLE void clearCompleted();

    Q_INVOKABLE void save();

    Q_INVOKABLE void load();

private:

    void saveInternal();

    TodoModel *m_model;

    QString m_filePath;
};