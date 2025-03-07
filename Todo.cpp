#include <QDataStream>
#include <QIODevice>
#include "Todo.h"

const QString & Todo::getTitle() const {
    return title;
}

void Todo::setTitle(const QString &title) {
    Todo::title = title;
}

const QString & Todo::getDescription() const {
    return description;
}

void Todo::setDescription(const QString &desc) {
    Todo::description = desc;
}

bool Todo::isDone() const {
    return done;
}

void Todo::setDone(bool done) {
    Todo::done = done;
}

bool Todo::operator==(const Todo &rhs) const {
    return title == rhs.title && description == rhs.description && done == rhs.done &&
           startDate == rhs.startDate;
}

bool Todo::operator!=(const Todo &rhs) const {
    return !(rhs == *this);
}

QByteArray Todo::serialize() const {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << title << description << done << startDate;
    return data;
}

void Todo::deserialize(const QByteArray &data) {
    QDataStream stream(data);
    stream >> title >> description >> done >> startDate;
}

const QDateTime &Todo::getStartDate() const {
    return startDate;
}

void Todo::setStartDate(const QDateTime &startDate) {
    Todo::startDate = startDate;
}