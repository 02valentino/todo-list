#ifndef QT_TO_DO_LIST_CONTROLLER_H
#define QT_TO_DO_LIST_CONTROLLER_H

#include "Todo.h"
#include "TodoList.h"

class Controller {
public:
    explicit Controller(TodoList *todolist) : todolist(todolist) {};

    void showCreationDialog();

    void addTodo(Todo& todo);

    void removeTodo(int i);

    void toggleTodo(int i);

    void showEditDialog(int i);

    bool saveToFile(const QString &path) const;

    bool loadFromFile(const QString &path);

private:
    TodoList *todolist;
};

#endif //QT_TO_DO_LIST_CONTROLLER_H