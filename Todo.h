#ifndef QT_TO_DO_LIST_TODO_H
#define QT_TO_DO_LIST_TODO_H

#include <string>
#include <QList>
#include <QDate>
#include <QString>
#include "Serializable.h"

class Todo : public Serializable {
public:
    Todo() = default;

    Todo(const Todo &todo)
            : title(todo.title), description(todo.description), done(todo.done),
              dueDate(todo.dueDate) {}

    Todo(const QString &title, const QString &desc, bool done, const QDateTime &startDate)
            : title(title), description(desc), done(done), dueDate(startDate) {}

    const QString &getTitle() const;

    void setTitle(const QString &title);

    const QString &getDescription() const;

    void setDescription(const QString &desc);

    bool isDone() const;

    void setDone(bool done);

    const QDateTime &getDueDate() const;

    void setDueDate(const QDateTime &startDate);

    QByteArray serialize() const override;

    void deserialize(const QByteArray &data) override;

    bool operator==(const Todo &rhs) const;

    bool operator!=(const Todo &rhs) const;

private:
    QString title;
    QString description;
    bool done = false;
    QDateTime dueDate;
};

#endif //QT_TO_DO_LIST_TODO_H