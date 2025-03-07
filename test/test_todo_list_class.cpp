#include <gtest/gtest.h>
#include "../Todo.h"
#include "../TodoList.h"

TEST(TodoListTests, add_remove_todo) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
todoList.addTodo(todo2);

EXPECT_EQ(todoList.size(), 2);

todoList.removeTodo(todo1);
EXPECT_EQ(todoList.size(), 1);

todoList.removeTodo(todo2);
EXPECT_EQ(todoList.size(), 0);
}

TEST(TodoListTests, remove_todo_not_in_list) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);

todoList.removeTodo(todo2);
EXPECT_EQ(todoList.size(), 1);
}

TEST(TodoListTests, remove_a_copy) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
todoList.addTodo(todo2);

auto todo1Copy = Todo(todo1);
todoList.removeTodo(todo1Copy);
EXPECT_EQ(todoList.size(), 1);
}

TEST(TodoListTests, serialize_deserialize) {
TodoList originalList;
originalList.addTodo(Todo("Title1", "Description1", false, QDateTime(QDate(), QTime())));
originalList.addTodo(Todo("Title2", "Description2", true, QDateTime(QDate(), QTime())));

QByteArray data = originalList.serialize();

TodoList newList;
newList.deserialize(data);

EXPECT_EQ(originalList.size(), newList.size());
EXPECT_EQ(originalList.getTodo(0), newList.getTodo(0));
EXPECT_EQ(originalList.getTodo(1), newList.getTodo(1));
}

TEST(TodoListTests, double_deserialize) {
TodoList originalList;
originalList.addTodo(Todo("Title1", "Description1", false, QDateTime(QDate(), QTime())));
originalList.addTodo(Todo("Title2", "Description2", true, QDateTime(QDate(), QTime())));

QByteArray data = originalList.serialize();

TodoList newList;
newList.deserialize(data);
newList.deserialize(data);

EXPECT_EQ(originalList.size(), newList.size());
EXPECT_EQ(originalList.getTodo(0), newList.getTodo(0));
EXPECT_EQ(originalList.getTodo(1), newList.getTodo(1));
}

TEST(TodoListTests, remove_todo_by_index) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
todoList.addTodo(todo2);

todoList.removeTodo(0);
EXPECT_EQ(todoList.size(), 1);
EXPECT_EQ(todoList.getTodo(0).getTitle(), "Title2");

todoList.removeTodo(0);
EXPECT_EQ(todoList.size(), 0);
}

TEST(TodoListTests, get_todo) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
todoList.addTodo(todo2);

EXPECT_EQ(todoList.getTodo(0).getTitle(), "Title1");
EXPECT_EQ(todoList.getTodo(1).getTitle(), "Title2");
}

TEST(TodoListTests, set_todo) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
todoList.setTodo(0, todo2);

EXPECT_EQ(todoList.getTodo(0).getTitle(), "Title2");
}

TEST(TodoListTests, toggle_done) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
EXPECT_FALSE(todoList.getTodo(0).isDone());

todoList.toggleDone(0);
EXPECT_TRUE(todoList.getTodo(0).isDone());

todoList.toggleDone(0);
EXPECT_FALSE(todoList.getTodo(0).isDone());
}

TEST(TodoListTests, size) {
TodoList todoList;
EXPECT_EQ(todoList.size(), 0);

auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
todoList.addTodo(todo1);
EXPECT_EQ(todoList.size(), 1);
}

TEST(TodoListTests, not_done_count) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
todoList.addTodo(todo2);

EXPECT_EQ(todoList.notDoneCount(), 1);
}

TEST(TodoListTests, done_count) {
TodoList todoList;
auto todo1 = Todo("Title1", "Description1", false, QDateTime(QDate(), QTime()));
auto todo2 = Todo("Title2", "Description2", true, QDateTime(QDate(), QTime()));

todoList.addTodo(todo1);
todoList.addTodo(todo2);

EXPECT_EQ(todoList.doneCount(), 1);
}