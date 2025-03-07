#include "TodoEditDialog.h"
#include "Controller.h"
#include <QFile>

void Controller::showCreationDialog() {
    Todo newTodo;
    TodoEditDialog dialog(newTodo);
    if(dialog.exec() == QDialog::Accepted) {
        addTodo(dialog.getTodo());
    }
}

void Controller::addTodo(Todo& todo) {
    todolist->addTodo(todo);
}

void Controller::removeTodo(int i) {
    todolist->removeTodo(i);
}

bool Controller::saveToFile(const QString &path) const {
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(todolist->serialize());
        file.close();
        return file.error() == QFileDevice::NoError;
    }
    return false;
}

bool Controller::loadFromFile(const QString &path) {
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
        todolist->deserialize(file.readAll());
        file.close();
        return file.error() == QFileDevice::NoError;
    }
    return false;
}

void Controller::showEditDialog(int i) {
    Todo newTodo(todolist->getTodo(i));
    TodoEditDialog dialog(newTodo);
    dialog.exec();
    todolist->setTodo(i, newTodo);
}

void Controller::toggleTodo(int i) {
    todolist->toggleDone(i);
}
