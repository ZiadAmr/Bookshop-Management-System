#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Programming/db.sqlite");
    db.setUserName("acarlson");
    db.setPassword("1uTbSbAs");
    bool ok = db.open();
    if(!ok){
        qDebug() << "You are an idiot" << Qt::endl;
    } else {
        qDebug() << "it works?" << Qt::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::string username = ui->lineEdit->text().toStdString();
    std::string password = ui->lineEdit_2->text().toStdString();

    if(username == "" || password == ""){
        return;
    }

    ui->stackedWidget->setCurrentIndex(1);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSqlQuery q;
    q.exec(QString("SELECT * FROM books;"));
    int row_counter = 0;

    ui->tableWidget->setColumnCount(4);
    const QStringList name = {"ISBN", "Title", "Author", "Description"};
    ui->tableWidget->setHorizontalHeaderLabels(name);


    while(q.next()){
        ui->tableWidget->insertRow(row_counter);
        QTableWidgetItem *isbn= new QTableWidgetItem(q.value(0).toString());
        QTableWidgetItem *title= new QTableWidgetItem(q.value(1).toString());
        QTableWidgetItem *author= new QTableWidgetItem(q.value(2).toString());
        QTableWidgetItem *desc= new QTableWidgetItem(q.value(3).toString());
        qDebug() << q.value(4).toInt();
        ui->tableWidget->setItem(row_counter, 0, isbn);
        ui->tableWidget->setItem(row_counter, 1, title);
        ui->tableWidget->setItem(row_counter, 2, author);
        ui->tableWidget->setItem(row_counter, 3, desc);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_3_clicked()
{
    QString isbn = ui->lineEdit_3->text();
    QString title = ui->lineEdit_4->text();
    QString author = ui->lineEdit_5->text();
    QString description = ui->textEdit->toPlainText();

    // insert into DB
    QSqlQuery query;
    query.prepare("INSERT INTO books VALUES (:isbn, :title, :author, :description);");
    query.bindValue(":isbn", isbn);
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":description", description);
    query.exec();

    // insert into table
    ui->tableWidget->insertRow((ui->tableWidget->rowCount()));
    QTableWidgetItem *qisbn= new QTableWidgetItem(isbn);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, qisbn);
    QTableWidgetItem *qtitle= new QTableWidgetItem(title);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, qtitle);
    QTableWidgetItem *qauthor= new QTableWidgetItem(author);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, qauthor);
    QTableWidgetItem *qdescription= new QTableWidgetItem(description);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, qdescription);

    // back to previous page
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString isbn = ui->tableWidget->item(row, 0)->text();
    QString title = ui->tableWidget->item(row, 1)->text();
    QString author = ui->tableWidget->item(row, 2)->text();
    QString description = ui->tableWidget->item(row, 3)->text();

    ui->stackedWidget->setCurrentIndex(3);

    ui->lineEdit_6->setText(isbn);
    ui->lineEdit_7->setText(title);
    ui->lineEdit_8->setText(author);
    ui->textEdit_2->setText(description);
}

