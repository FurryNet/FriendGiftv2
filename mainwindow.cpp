#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Algorithms.h"

bool isValid = false;
char attempts = 0;
uint16_t LuckyNum = 0;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
    LuckyNum = GetRNGEngine()->bounded(0,1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_GenNum_clicked()
{
    CardInfo data = genRNGCard();
    isValid = (GetRNGEngine()->bounded(0,1000) == LuckyNum);
    if(isValid)
        data = DecActualCard();

    if(isValid && data.cardNum == "0000000000000000")
        ui->Status->setText("Although you got lucky, the SecureData was tampered with and can no longer ensure the number is still valid. Please redownload and try again.");


    ui->CardNum->setText(data.cardNum);
    ui->ExpDate->setText(data.expiration);
    ui->CVVNum->setText(data.cvv);
}

