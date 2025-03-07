#include <gtest/gtest.h>
#include "../Todo.h"

TEST(TodoClassTest, todo_set_description) {
Todo todo;
QString description = "New Description";
todo.setDescription(description);
EXPECT_EQ(todo.getDescription(), description);
}

TEST(TodoClassTest, todo_set_done) {
Todo todo;
todo.setDone(true);
EXPECT_TRUE(todo.isDone());
todo.setDone(false);
EXPECT_FALSE(todo.isDone());
}

TEST(TodoClassTest, todo_equality) {
Todo todo1;
Todo todo2;
todo1.setDescription("Task");
todo2.setDescription("Task");
todo1.setDone(true);
todo2.setDone(true);
EXPECT_EQ(todo1, todo2);
todo2.setDone(false);
EXPECT_NE(todo1, todo2);
}

TEST(TodoClassTest, todo_serialization) {
Todo todo;
todo.setTitle("Title");
todo.setDescription("Description");
todo.setDone(true);
QByteArray data = todo.serialize();
Todo deserializedTodo;
deserializedTodo.deserialize(data);
EXPECT_EQ(todo.getTitle(), deserializedTodo.getTitle());
EXPECT_EQ(todo.getDescription(), deserializedTodo.getDescription());
EXPECT_EQ(todo.isDone(), deserializedTodo.isDone());
}

TEST(TodoClassTest, todo_set_title) {
Todo todo;
QString title = "New Title";
todo.setTitle(title);
EXPECT_EQ(todo.getTitle(), title);
}

TEST(TodoClassTest, todo_set_start_date) {
Todo todo;
QDateTime startDate = QDateTime::currentDateTime();
todo.setStartDate(startDate);
EXPECT_EQ(todo.getStartDate(), startDate);
}