#ifndef QT_TO_DO_LIST_TODOEDITDIALOG_H
#define QT_TO_DO_LIST_TODOEDITDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "Todo.h"

class TodoEditDialog : public QDialog {
    Q_OBJECT
public:
    explicit TodoEditDialog(Todo& todo, QWidget *parent = nullptr);

    Todo& getTodo() const;

private slots:
            void accept() override;

private:
    Todo& todo;
    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;
    QDateTimeEdit *dueDateEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif //QT_TO_DO_LIST_TODOEDITDIALOG_H