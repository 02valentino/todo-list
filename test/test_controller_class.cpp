#include <gtest/gtest.h>
#include <QFile>
#include "../Todo.h"
#include "../Controller.h"
#include <QDateTime>
#include <memory>

class ControllerTests : public ::testing::Test {
protected:
    TodoList todoList;

    void SetUp() override {
        auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
        auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

        todoList.addTodo(todo1);
        todoList.addTodo(todo2);
    }

    void TearDown() override {
        QFile::remove("test.todo");
    }
};

TEST_F(ControllerTests, save_load_file) {
Controller controller(&todoList);

controller.saveToFile("test.todo");

TodoList newTodoList;
Controller load_controller(&newTodoList);
load_controller.loadFromFile("test.todo");

EXPECT_EQ(todoList.size(), newTodoList.size());
EXPECT_EQ(todoList.getTodo(0), newTodoList.getTodo(0));
EXPECT_EQ(todoList.getTodo(1), newTodoList.getTodo(1));
}

TEST_F(ControllerTests, add_todo) {
Controller controller(&todoList);
auto newTodo = Todo("New Title", "New Description", false, QDateTime(QDate(), QTime()));
controller.addTodo(newTodo);

EXPECT_EQ(todoList.size(), 3);
EXPECT_EQ(todoList.getTodo(2), newTodo);
}

TEST_F(ControllerTests, remove_todo) {
Controller controller(&todoList);
controller.removeTodo(0);
EXPECT_EQ(todoList.size(), 1);
EXPECT_EQ(todoList.getTodo(0).getTitle(), "Title2");
}

TEST_F(ControllerTests, toggle_todo) {
Controller controller(&todoList);
auto& todoToToggle = todoList.getTodo(0);
controller.toggleTodo(0);
EXPECT_TRUE(todoToToggle.isDone());
controller.toggleTodo(0);
EXPECT_FALSE(todoToToggle.isDone());
}