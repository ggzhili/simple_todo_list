#include "TodoManager.h"
#include "TodoModel.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

TodoManager::TodoManager(
    TodoModel *model,
    QObject *parent)
    : QObject(parent)
    , m_model(model)
{
    m_filePath =
        QCoreApplication::applicationDirPath()
        + "/todo.json";
}

void TodoManager::addTodo(
    const QString &title)
{
    m_model->addTodo(title);

    saveInternal();
}

void TodoManager::removeTodo(
    int index)
{
    m_model->removeTodo(index);

    saveInternal();
}

void TodoManager::toggleTodo(
    int index)
{
    m_model->toggleTodo(index);

    saveInternal();
}

void TodoManager::clearCompleted()
{
    const auto &items = m_model->items();

    QVector<TodoItem> remaining;

    for (const TodoItem &item : items)
    {
        if (!item.completed)
        {
            remaining.append(item);
        }
    }

    m_model->setItems(remaining);

    saveInternal();
}

void TodoManager::save()
{
    saveInternal();
}

// 加载文件内容，json ----- 持久化内容
void TodoManager::load()
{
    QFile file(m_filePath);

    if (!file.exists())
        return;

    if (!file.open(QIODevice::ReadOnly))
        return;

    const QByteArray data = file.readAll();

    file.close();

    QJsonParseError error;

    QJsonDocument document =
        QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError)
        return;

    if (!document.isArray())
        return;

    QJsonArray array = document.array();

    QVector<TodoItem> items;

    for (const QJsonValue &value : array)
    {
        if (!value.isObject())
            continue;

        QJsonObject object = value.toObject();

        TodoItem item;

        item.title =
            object["title"].toString();

        item.completed =
            object["completed"].toBool(false);

        if (!item.title.isEmpty())
        {
            items.append(item);
        }
    }

    m_model->setItems(items);
}

void TodoManager::saveInternal()
{
    QJsonArray array;

    const auto &items = m_model->items();

    for (const TodoItem &item : items)
    {
        QJsonObject object;

        object["title"] = item.title;
        object["completed"] = item.completed;

        array.append(object);
    }

    QJsonDocument document(array);

    QFile file(m_filePath);

    if (!file.open(
            QIODevice::WriteOnly |
            QIODevice::Truncate))
    {
        return;
    }

    file.write(
        document.toJson(
            QJsonDocument::Indented
            )
        );

    file.close();
}