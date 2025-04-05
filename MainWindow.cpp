#include "MainWindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QStatusBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QEvent>
#include <QMouseEvent>
#include "TodoListQAbstractTableModelAdapter.h"

MainWindow::MainWindow(TodoList *todolist, Controller *controller, QWidget *parent) {
    MainWindow::controller = controller;
    MainWindow::todoList = todolist;
    MainWindow::todoList->addObserver(this);

    setStatusBar(new QStatusBar(this));
    statusBar()->showMessage("Try creating a new todo (see global menu)");

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search todos...");
    connect(searchBar, &QLineEdit::returnPressed, this, [this](){
        searchTodos(searchBar->text());
    });

    searchResults = new QListWidget(this);
    searchResults->setWindowFlags(Qt::Popup);
    searchResults->setFocusPolicy(Qt::NoFocus);
    searchResults->hide();

    connect(searchResults, &QListWidget::itemClicked, this, [this, controller](QListWidgetItem *item){
        int row = item->data(Qt::UserRole).toInt();
        controller->showEditDialog(row);
        searchResults->hide();
    });

    tableView = new TodoTableView(this, todolist, controller);

    auto layout = new QVBoxLayout;
    layout->addWidget(searchBar);
    layout->addWidget(tableView);

    auto centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setGeometry(100, 100, 800, 600);

    auto fileMenu = menuBar()->addMenu("File");
    auto saveAction = fileMenu->addAction("Save");
    auto saveAsAction = fileMenu->addAction("Save As");
    auto loadAction = fileMenu->addAction("Load");
    auto exitAction = fileMenu->addAction("Exit");

    saveAction->setShortcut(QKeySequence::Save);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    loadAction->setShortcut(QKeySequence::Open);
    exitAction->setShortcut(QKeySequence::Quit);

    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    connect(loadAction, &QAction::triggered, this, &MainWindow::load);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);


    auto newMenu = menuBar()->addMenu("Edit");
    auto addTodoAction = newMenu->addAction("Add Todo");
    auto addRemoveAllAction = newMenu->addAction("Remove All");

    addTodoAction->setShortcut(QKeySequence::New);

    connect(addTodoAction, &QAction::triggered, this, &MainWindow::addTodo);
    connect(addRemoveAllAction, &QAction::triggered, this, &MainWindow::removeAll);

    qApp->installEventFilter(this);
}

void MainWindow::addTodo() {
    controller->showCreationDialog();
}

void MainWindow::save() {
    if (currentPath.isEmpty()) {
        saveAs();
    } else {
        if (controller->saveToFile(currentPath))
            statusBar()->showMessage("Saved.", 1000);
    }
}

void MainWindow::saveAs() {
    auto path = QFileDialog::getSaveFileName(this, "Save Todo List", currentPath, "Todo List (*.todo)");
    if (path.isEmpty()) return;
    if (!path.endsWith(".todo")) {
        path.append(".todo");
    }
    if (controller->saveToFile(path)) {
        statusBar()->showMessage("Saved.", 1000);
        currentPath = path;
    } else {
        statusBar()->showMessage("Error saving file!");
    }
}

void MainWindow::load() {
    auto path = QFileDialog::getOpenFileName(this, "Load Todo List", currentPath, "Todo List (*.todo)");
    if (path.isEmpty()) return;
    if (controller->loadFromFile(path)){
        statusBar()->showMessage("Loaded successfully!", 1000);
        currentPath = path;
    } else {
        statusBar()->showMessage("Error loading file!");
    }

}

void MainWindow::update() {
    statusBar()->showMessage(QString("Todos:%1").arg(todoList->size()) +
                             QString("      Not done:%1").arg(todoList->notDoneCount()));
}

void MainWindow::removeAll() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete all todos?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        for (auto i = todoList->size() - 1; i >= 0; --i) {
            todoList->removeTodo(i);
        }
    }
}

void MainWindow::searchTodos(const QString &searchTerm) {
    auto filtered = todoList->filteredTodos(searchTerm);
    searchResults->clear();
    for (int i = 0; i < filtered.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(filtered[i].getTitle(), searchResults);
        item->setData(Qt::UserRole, i);
    }
    if (!filtered.isEmpty()) {
        QPoint pos = searchBar->mapToGlobal(QPoint(0, searchBar->height()));
        searchResults->setGeometry(pos.x(), pos.y(), searchBar->width(), 200);
        searchResults->show();
    } else {
        searchResults->hide();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (!searchResults->geometry().contains(mouseEvent->globalPos())) {
            searchResults->hide();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

MainWindow::~MainWindow() {
    todoList->removeObserver(this);
}