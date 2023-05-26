#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "db_redactor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_createDB_btn_clicked();
    void on_openDB_btn_clicked();
    void on_about_btn_clicked();
    void closeTab();    //закрыть вкладку из редактора
    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    db_redactor *redctrWindow;
};

#endif // MAINWINDOW_H
