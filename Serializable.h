#ifndef QT_TO_DO_LIST_SERIALIZABLE_H
#define QT_TO_DO_LIST_SERIALIZABLE_H

#include <QByteArray>

class Serializable {
public:
    virtual ~Serializable() = default;
    virtual QByteArray serialize() const = 0;
    virtual void deserialize(const QByteArray& data) = 0;
};

#endif //QT_TO_DO_LIST_SERIALIZABLE_H