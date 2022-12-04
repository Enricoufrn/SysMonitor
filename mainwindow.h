#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ProcessManager.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generateProcessTable();

private slots:
    void on_filterBtn_clicked();

private:
    Ui::MainWindow *ui;
    ProcessManager processManager;
    QTimer *timer;
};
#endif // MAINWINDOW_H
