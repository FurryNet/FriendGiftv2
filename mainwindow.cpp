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
    PlayBackgroundOnRepeat(this);
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

    if(isValid && data.cardNum == "0000000000000000") {
        ui->Status->setText("Although you got lucky, the SecureData was tampered with and can no longer ensure the number is still valid. Please redownload and try again.");
        isValid = false;
    }
    ui->ChkNum->setDisabled(false);


    ui->CardNum->setText(data.cardNum);
    ui->ExpDate->setText(data.expiration);
    ui->CVVNum->setText(data.cvv);
}


void MainWindow::on_ChkNum_clicked()
{
    ui->ChkNum->setDisabled(true);

    if(isValid) {
        ui->Status->setText("Congratulation, the card number is valid! Please redeem your $10 dalla reward.");
        ui->GenNum->setDisabled(true);
        return;
    }

    ui->Status->setText(QString("Sorry, not a valid number, attempt used: %1/3 (software will shutdown after 3rd attempt)").arg(QString::number(++attempts)));
    if(attempts >= 3)
        QApplication::quit();

}

