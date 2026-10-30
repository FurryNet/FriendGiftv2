#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Algorithms.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool isValid = false;

void MainWindow::on_GenNum_clicked()
{
    CardInfo data = DecActualCard();
    ui->CardNum->setText(data.cardNum);
    ui->ExpDate->setText(data.expiration);
    ui->CVVNum->setText(data.cvv);
}

