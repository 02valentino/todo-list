#include <QApplication>
#include "TodoList.h"
#include "Controller.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    TodoList todoList;
    Controller controller(&todoList);
    MainWindow mainWindow(&todoList, &controller);
    mainWindow.show();

    return QApplication::exec();
}