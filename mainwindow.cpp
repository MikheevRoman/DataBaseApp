#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apartment.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->hide();
    connect(ui->actionCreate,SIGNAL(triggered(bool)),this,SLOT(on_createDB_btn_clicked()));
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(on_openDB_btn_clicked()));
    connect(ui->actionAbout_2,SIGNAL(triggered(bool)),this,SLOT(on_about_btn_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete redctrWindow;
}

void MainWindow::on_createDB_btn_clicked()
{
    ui->toolBar->show();
    static uint8_t count = 1;
    ui->tabWidget->addTab(redctrWindow = new db_redactor(this),"New"+QString::number(count));
    redctrWindow->createNewFile();
    ui->tabWidget->setCurrentWidget(redctrWindow);
    count++;
    connect(redctrWindow,SIGNAL(setStatusBarTxt(QString,int)),ui->statusBar,SLOT(showMessage(QString,int)));
    connect(ui->addAction,SIGNAL(triggered(bool)),redctrWindow,SLOT(on_addStr_btn_clicked()));
    connect(ui->delAction,SIGNAL(triggered(bool)),redctrWindow,SLOT(on_deleteStr_btn_clicked()));
    connect(ui->searchAction,SIGNAL(triggered(bool)),redctrWindow,SLOT(on_searchStr_btn_clicked()));
    ui->statusBar->showMessage("New file created");
}

void MainWindow::on_openDB_btn_clicked()
{
    QString dir = QFileDialog::getOpenFileName(this,"Choose the file","C:\\","*.json");
    if (dir != "")
    {
        ui->tabWidget->addTab(redctrWindow = new db_redactor(this),QFileInfo(dir).fileName());
        redctrWindow->openFile(dir);
        ui->tabWidget->setCurrentWidget(redctrWindow);
        connect(redctrWindow,SIGNAL(setStatusBarTxt(QString,int)),ui->statusBar,SLOT(showMessage(QString,int)));
        connect(ui->addAction,SIGNAL(triggered(bool)),redctrWindow,SLOT(on_addStr_btn_clicked()));
        connect(ui->delAction,SIGNAL(triggered(bool)),redctrWindow,SLOT(on_deleteStr_btn_clicked()));
        connect(ui->searchAction,SIGNAL(triggered(bool)),redctrWindow,SLOT(on_searchStr_btn_clicked()));
        ui->statusBar->showMessage("File opened");
    }
}

void MainWindow::on_about_btn_clicked()
{
    QMessageBox::about(this,"About program","Программа является курсовой работой, вариант №15\n"
                                            "работа выполнена студентом группы ИКПИ-11 Михеевым Р.С.");
}

void MainWindow::closeTab()
{
    ui->statusBar->showMessage("");
    if (redctrWindow->saved == false)
        QMessageBox::warning(this,"Внимание!","Вы не сохранили файл перед закрытием");
    else
        ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
        ui->toolBar->hide();
    else
        ui->toolBar->show();
}
