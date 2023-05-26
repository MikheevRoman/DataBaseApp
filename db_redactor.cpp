#include "db_redactor.h"
#include "ui_db_redactor.h"
#include "mainwindow.h"

db_redactor::db_redactor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::db_redactor)
{
    ui->setupUi(this);
    connect(ui->closeTab_btn,SIGNAL(clicked(bool)),this->parentWidget(),SLOT(closeTab()));
    connect(ui->cancel_btn,SIGNAL(clicked(bool)),this,SLOT(on_addStr_btn_clicked()));
    connect(ui->cancel_btn_find,SIGNAL(clicked(bool)),this,SLOT(on_searchStr_btn_clicked()));

    ui->addItemWindow->hide();
    ui->findItemWindow->hide();
}

db_redactor::~db_redactor()
{
    delete ui;
    if (model != nullptr)
        delete model;
    if (itemCol_1 != nullptr)
        delete itemCol_1;
    if (itemCol_2 != nullptr)
        delete itemCol_2;
    if (itemCol_3 != nullptr)
        delete itemCol_3;
    if (itemCol_4 != nullptr)
        delete itemCol_4;
}

void db_redactor::openFile(QString dir)
{
    dBase.setPath(dir);
    dBase.read();
    model = new QStandardItemModel(nullptr);
    model->setHorizontalHeaderLabels(QStringList()<<"Кол-во комнат"<<"Площадь (кв.м)"<<"Цена (руб.)"<<"Район");

    for (int i = 0; i < dBase.getDb().size(); i++)
    {
        itemCol_1 = new QStandardItem(QString::number(dBase.getDb()[i].getRooms()));
        itemCol_2 = new QStandardItem(QString::number(dBase.getDb()[i].getSquare()));
        itemCol_3 = new QStandardItem(QString::number((int)dBase.getDb()[i].getCost()));
        itemCol_4 = new QStandardItem(dBase.getDb()[i].getLocate());
        model->appendRow(QList<QStandardItem*>()<<itemCol_1<<itemCol_2<<itemCol_3<<itemCol_4);
    }

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void db_redactor::createNewFile()
{
    model = new QStandardItemModel(nullptr);
    model->setHorizontalHeaderLabels(QStringList()<<"Кол-во комнат"<<"Площадь (кв.м)"<<"Цена (руб.)"<<"Район");
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void db_redactor::on_addStr_btn_clicked()
{
    if (ui->addItemWindow->isHidden() == true)
        ui->addItemWindow->show();
    else
        ui->addItemWindow->hide();
}

void db_redactor::on_searchStr_btn_clicked()
{
    if (ui->findItemWindow->isHidden() == true)
        ui->findItemWindow->show();
    else
        ui->findItemWindow->hide();
}

void db_redactor::on_addItem_btn_clicked()
{
    if (ui->roomLineEdit->text() != "" && ui->squareLineEdit->text() != "" && ui->costLineEdit->text() != "" &&
            ui->locateLineEdit->text() != "")
    {
        saved = false;
        dBase.add(ui->roomLineEdit->text().toInt(), ui->squareLineEdit->text().toDouble(),
                  ui->costLineEdit->text().toDouble(), ui->locateLineEdit->text());
        itemCol_1 = new QStandardItem(QString::number(dBase.getDb()[dBase.getDb().size() - 1].getRooms()));
        itemCol_2 = new QStandardItem(QString::number(dBase.getDb()[dBase.getDb().size() - 1].getSquare()));
        itemCol_3 = new QStandardItem(QString::number((int)dBase.getDb()[dBase.getDb().size() - 1].getCost()));
        itemCol_4 = new QStandardItem(dBase.getDb()[dBase.getDb().size() - 1].getLocate());
        model->appendRow(QList<QStandardItem*>()<<itemCol_1<<itemCol_2<<itemCol_3<<itemCol_4);
        emit setStatusBarTxt("Добавлен новый элемент",0);
    }
    else
        QMessageBox::warning(this,"","Для добавления элемента все поля должны быть заполнены");
}

void db_redactor::on_save_btn_clicked()
{
    QString dir = QFileDialog::getSaveFileName(nullptr,"Сохранить как","C:\\SPBGUT\\OOP\\","*.json");
    dBase.setPath(dir);
    dBase.write();
    saved = true;
    emit setStatusBarTxt("Файл сохранен",3000);
}

void db_redactor::on_findItem_btn_clicked()
{
    int count = 0;
    if (ui->roomLineEdit_find->text() != ""
            || ui->squareLineEdit_find->text() != ""
            || ui->costLineEdit_find->text() != ""
            || ui->locateLineEdit_find->text() != "")
    {
        for (int i = 0; i <= model->columnCount(); i++)
        {
            for (int j = 0; j <= model->rowCount(); j++)
            {
                QModelIndex index = model->index(j,i);
                if (ui->roomLineEdit_find->text() != "")
                {
                    if (index.column() == 0 && index.data().toString() == ui->roomLineEdit_find->text())
                    {
                        model->item(j,i)->setBackground(Qt::yellow);
                        count++;
                    }
                }
                if (ui->squareLineEdit_find->text() != "")
                {
                    if (index.column() == 1 && index.data().toString() == ui->squareLineEdit_find->text())
                    {
                        model->item(j,i)->setBackground(Qt::yellow);
                        count++;
                    }
                }
                if (ui->costLineEdit_find->text() != "")
                {
                    if (index.column() == 2 && index.data().toString() == ui->costLineEdit_find->text())
                    {
                        model->item(j,i)->setBackground(Qt::yellow);
                        count++;
                    }
                }
                if (ui->locateLineEdit_find->text() != "")
                {
                    if (index.column() == 3 && index.data().toString() == ui->locateLineEdit_find->text())
                    {
                        model->item(j,i)->setBackground(Qt::yellow);
                        count++;
                    }
                }
            }
        }
    }
    emit setStatusBarTxt("По вашему запросу найдено " + QString::number(count) + " записей",0);
}

void db_redactor::on_clearMarkedItem_btn_clicked()
{
    for (int i = 0; i <= model->columnCount(); i++)
        for (int j = 0; j <= model->rowCount(); j++)
        {
            QModelIndex index = model->index(j,i);
            model->setData(index,QBrush(Qt::white),Qt::BackgroundRole);
        }
}

void db_redactor::on_deleteStr_btn_clicked()
{
    if (curIndex == QModelIndex())
        QMessageBox::about(this,"","Вы не выбрали элемент для удаления");
    else
    {
        if (model->rowCount() != 0)
        {
            dBase.removeData(curIndex.row());
            model->removeRow(curIndex.row());
            emit setStatusBarTxt("Удалена запись №" + QString::number(curIndex.row() + 1),0);
            saved = false;
            curIndex = QModelIndex();
        }
        else
            QMessageBox::warning(this,"Ошибка","База данных пуста");
    }
}

void db_redactor::on_tableView_clicked(const QModelIndex &index)
{
    curIndex = index;
    for (int i = 0; i <= model->columnCount(); i++) //очищаем выделенные при поиске элементы
        for (int j = 0; j <= model->rowCount(); j++)
        {
            QModelIndex idx = model->index(j,i);
            model->setData(idx,QBrush(Qt::white),Qt::BackgroundRole);
        }
}

void db_redactor::on_unionWith_btn_clicked()
{
    QString dir = QFileDialog::getOpenFileName(this,"Выберите файл","C:\\","*.json");
    if (dir != "")
    {
        saved = false;
        dataBase tempDB;
        tempDB.setPath(dir);
        tempDB.read();
        for (int i = 0; i < tempDB.getDb().size(); i++)
        {
            dBase.add(tempDB.getDb()[i].getRooms(),
                      tempDB.getDb()[i].getSquare(),
                      tempDB.getDb()[i].getCost(),
                      tempDB.getDb()[i].getLocate());
            itemCol_1 = new QStandardItem(QString::number(tempDB.getDb()[i].getRooms()));
            itemCol_2 = new QStandardItem(QString::number(tempDB.getDb()[i].getSquare()));
            itemCol_3 = new QStandardItem(QString::number((int)tempDB.getDb()[i].getCost()));
            itemCol_4 = new QStandardItem(tempDB.getDb()[i].getLocate());
            model->appendRow(QList<QStandardItem*>()<<itemCol_1<<itemCol_2<<itemCol_3<<itemCol_4);
        }
        emit setStatusBarTxt("Файлы объединены",0);
    }
}

void db_redactor::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        QString temp = QInputDialog::getText(this,"Изменение данных","Кол-во комнат:");
        if (temp != "")
        {
            dBase.changeData(index.column(),index.row(),temp);
            itemCol_1 = new QStandardItem(QString::number(dBase.getDb()[index.row()].getRooms()));
            model->setItem(index.row(),index.column(),itemCol_1);
            saved = false;
            emit setStatusBarTxt("Запись отредактирована",0);
        }
    }
    else if (index.column() == 1)
    {
        QString temp = QInputDialog::getText(this,"Изменение данных","Площадь:");
        if (temp != "")
        {
            dBase.changeData(index.column(),index.row(),temp);
            itemCol_2 = new QStandardItem(QString::number(dBase.getDb()[index.row()].getSquare()));
            model->setItem(index.row(),index.column(),itemCol_2);
            saved = false;
            emit setStatusBarTxt("Запись отредактирована",0);
        }
    }
    else if (index.column() == 2)
    {
        QString temp = QInputDialog::getText(this,"Изменение данных","Цена:");
        if (temp != "")
        {
            dBase.changeData(index.column(),index.row(),temp);
            itemCol_3 = new QStandardItem(QString::number(dBase.getDb()[index.row()].getCost()));
            model->setItem(index.row(),index.column(),itemCol_3);
            saved = false;
            emit setStatusBarTxt("Запись отредактирована",0);
        }
    }
    else if (index.column() == 3)
    {
        QString temp = QInputDialog::getText(this,"Изменение данных","Район:");
        if (temp != "")
        {
            dBase.changeData(index.column(),index.row(),temp);
            itemCol_4 = new QStandardItem(dBase.getDb()[index.row()].getLocate());
            model->setItem(index.row(),index.column(),itemCol_4);
            saved = false;
            emit setStatusBarTxt("Запись отредактирована",0);
        }
    }
}
