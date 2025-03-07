#include <QHBoxLayout>
#include <QHeaderView>
#include <QMenu>
#include "TodoTableView.h"
#include "TodoListQAbstractTableModelAdapter.h"

TodoTableView::TodoTableView(QWidget *parent, TodoList *todoList, Controller *controller)
        : QWidget(parent), todoList(todoList), controller(controller) {
    todoList->addObserver(this);

    tableView = new QTableView(this);
    adapter = new TodoListQAbstractTableModelAdapter(todoList, this);
    tableView->setModel(adapter);

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->setLayout(new QHBoxLayout(this));
    this->layout()->addWidget(tableView);

    contextMenu = new QMenu(this);
    toggleAction = new QAction("Toggle", this);
    removeAction = new QAction("Remove", this);
    editAction = new QAction("Edit", this);
    contextMenu->addAction(toggleAction);
    contextMenu->addAction(removeAction);
    contextMenu->addAction(editAction);

    connect(toggleAction, &QAction::triggered, this, &TodoTableView::toggleTodo);
    connect(removeAction, &QAction::triggered, this, &TodoTableView::removeTodo);
    connect(editAction, &QAction::triggered, this, &TodoTableView::editTodo);
    connect(tableView, &QTableView::customContextMenuRequested, this, &TodoTableView::showContextMenu);

    tableView->setContextMenuPolicy(Qt::CustomContextMenu);
}

TodoTableView::~TodoTableView() {
    todoList->removeObserver(this);
}

void TodoTableView::update() {
    adapter->redraw();
}

void TodoTableView::showContextMenu(const QPoint &pos) {
    currentIndex = tableView->indexAt(pos);
    if (currentIndex.isValid()) {
        contextMenu->exec(tableView->viewport()->mapToGlobal(pos));
    }
}

void TodoTableView::removeTodo() {
    if (currentIndex.isValid()) {
        controller->removeTodo(currentIndex.row());
    }
}

void TodoTableView::editTodo() {
    if (currentIndex.isValid()) {
        controller->showEditDialog(currentIndex.row());
    }
}

void TodoTableView::toggleTodo() {
    if (currentIndex.isValid()) {
        controller->toggleTodo(currentIndex.row());
    }
}