#ifndef QT_TO_DO_LIST_TODOLISTQABSTRACTTABLEMODELADAPTER_H
#define QT_TO_DO_LIST_TODOLISTQABSTRACTTABLEMODELADAPTER_H

#include <QAbstractTableModel>
#include "TodoList.h"

class TodoListQAbstractTableModelAdapter : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit TodoListQAbstractTableModelAdapter(TodoList *todoList, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void redraw();

private:
    TodoList *todoList;
};

#endif //QT_TO_DO_LIST_TODOLISTQABSTRACTTABLEMODELADAPTER_H