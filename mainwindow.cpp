#include "mainwindow.h"
#include "ui_mainwindow.h"

const vector<string> labels = {"PID", "CPUID", "USER", "PRI", "NI", "S", "%CPU", "%MEM", "TIME", "COMMAND"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    timer = new QTimer(this);
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

    QStringList strListlabels;

    /* add all labels readed from file */
    for (string label : labels) {
        strListlabels.append(QString::fromStdString(label));
    }

    QTableWidgetItem *item;
    for(int i = 1; i < rows; i++){
        for(int j = 0; j < columns; j++){
            item = new QTableWidgetItem();
            item->setText(QString::fromStdString(processList.at(i).at(j)));
            ui->processList->setItem(i-1, j, item);
        }
    }
    ui->processList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->processList->setHorizontalHeaderLabels(strListlabels);
    ui->processList->resizeColumnsToContents();
}


void MainWindow::on_filterBtn_clicked()
{
    QString processName = ui->processName->toPlainText();
    processManager.setName(processName.toStdString());
    generateProcessTable();
}

