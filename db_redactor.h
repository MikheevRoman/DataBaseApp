#ifndef DB_REDACTOR_H
#define DB_REDACTOR_H

#include <QString>
#include <QWidget>
#include <QStandardItem>
#include <QFileDialog>
#include <QInputDialog>

#include "database.h"

namespace Ui {
class db_redactor;
}

class db_redactor : public QWidget
{
    Q_OBJECT

public:
    explicit db_redactor(QWidget *parent = 0);
    ~db_redactor();

    void on_closeTab_btn_clicked();
    void openFile(QString);
    void createNewFile();

    bool saved = true;

signals:
    void setStatusBarTxt(QString,int);

private slots:
    void on_addStr_btn_clicked();
    void on_searchStr_btn_clicked();
    void on_addItem_btn_clicked();
    void on_save_btn_clicked();
    void on_findItem_btn_clicked();
    void on_clearMarkedItem_btn_clicked();
    void on_deleteStr_btn_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_unionWith_btn_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::db_redactor *ui;
    QModelIndex curIndex;
    dataBase dBase;
    QStandardItemModel* model = nullptr;
    QStandardItem* itemCol_1 = nullptr;
    QStandardItem* itemCol_2 = nullptr;
    QStandardItem* itemCol_3 = nullptr;
    QStandardItem* itemCol_4 = nullptr;
};

#endif // DB_REDACTOR_H
