#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(generateProcessTable()))
    connect(timer, &QTimer::timeout, this, &MainWindow::generateProcessTable);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: generateProcessTable(){
    ui->processList->clear();
    vector<vector<string>> processList;
    processList = processManager.getAllProcess();
    int rows = processList.size();
    int columns = processList.at(0).size();
    ui->processList->setColumnCount(columns);
    ui->processList->setRowCount(rows);
    ui->processList->verticalHeader()->setVisible(false);

    QStringList labels;

    /* add all labels readed from file */
    for (string label : processList.at(0)) {
        labels.append(QString::fromStdString(label));
    }

    QTableWidgetItem *item;
    for(int i = 1; i < rows; i++){
        for(int j = 0; j < columns; j++){
            item = new QTableWidgetItem();
            item->setText(QString::fromStdString(processList.at(i).at(j)));
            ui->processList->setItem(i-1, j, item);
        }
    }

    ui->processList->setHorizontalHeaderLabels(labels);
    ui->processList->resizeColumnsToContents();
}


void MainWindow::on_filterBtn_clicked()
{
    QString processName = ui->processName->toPlainText();
    processManager.setName(processName.toStdString());
    generateProcessTable();
}

