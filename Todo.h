#ifndef QT_TO_DO_LIST_TODO_H
#define QT_TO_DO_LIST_TODO_H

#include <string>
#include <QList>
#include <QDate>
#include <QString>
#include "Subject.h"
#include "Serializable.h"

class Todo : public Serializable {
public:
    Todo() = default;

    Todo(const Todo &todo)
            : title(todo.title), description(todo.description), done(todo.done),
              startDate(todo.startDate) {}

    Todo(const QString &title, const QString &desc, bool done, const QDateTime &startDate)
            : title(title), description(desc), done(done), startDate(startDate) {}

    const QString &getTitle() const;

    void setTitle(const QString &title);

    const QString &getDescription() const;

    void setDescription(const QString &desc);

    bool isDone() const;

    void setDone(bool done);

    const QDateTime &getStartDate() const;

    void setStartDate(const QDateTime &startDate);

    QByteArray serialize() const override;

    void deserialize(const QByteArray &data) override;

    bool operator==(const Todo &rhs) const;

    bool operator!=(const Todo &rhs) const;

private:
    QString title;
    QString description;
    bool done = false;
    QDateTime startDate;
};

#endif //QT_TO_DO_LIST_TODO_H