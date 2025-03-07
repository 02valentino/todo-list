cmake_minimum_required(VERSION 3.28)
project(qt_to_do_list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(SOURCES
        Todo.cpp
        Todo.h
        TodoList.cpp
        TodoList.h
        Observer.h
        Subject.h
        Controller.cpp
        Controller.h
        TodoEditDialog.cpp
        TodoEditDialog.h
        Serializable.h
        MainWindow.cpp
        MainWindow.h
        TodoTableView.h
        TodoTableView.cpp
        TodoListQAbstractTableModelAdapter.h
        TodoListQAbstractTableModelAdapter.cpp
)

add_library(core ${SOURCES})

target_link_libraries(core
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

add_executable(qt_to_do_list main.cpp)

target_link_libraries(qt_to_do_list core)

add_subdirectory(test)