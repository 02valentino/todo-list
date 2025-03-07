#ifndef QT_TO_DO_LIST_OBSERVER_H
#define QT_TO_DO_LIST_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update() = 0;
};

#endif //QT_TO_DO_LIST_OBSERVER_H