#ifndef QT_TO_DO_LIST_MAINWINDOW_H
#define QT_TO_DO_LIST_MAINWINDOW_H

#include "Controller.h"
#include "Observer.h"
#include <QMainWindow>
#include <QTableView>
#include "TodoList.h"
#include "TodoTableView.h"

class MainWindow : public QMainWindow, Observer {
    Q_OBJECT
public:
    explicit MainWindow(TodoList *todolist, Controller *controller, QWidget *parent = nullptr);

    ~MainWindow() override;

    void update() override;

public slots:
    void save();
    void saveAs();
    void load();
    void addTodo();
    void removeAll();
    void searchTodos(const QString &searchTerm);

private:
    Controller *controller;
    TodoTableView *tableView;
    QString currentPath;
    TodoList *todoList;
};

#endif //QT_TO_DO_LIST_MAINWINDOW_H