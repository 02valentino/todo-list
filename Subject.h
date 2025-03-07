#ifndef QT_TO_DO_LIST_SUBJECT_H
#define QT_TO_DO_LIST_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;

    virtual void addObserver(Observer *observer) = 0;

    virtual void removeObserver(Observer *observer) = 0;

    virtual void notify() = 0;
};

#endif //QT_TO_DO_LIST_SUBJECT_H