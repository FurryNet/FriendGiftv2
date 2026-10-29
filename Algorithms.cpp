#include "Algorithms.h"
#include <QRandomGenerator>

QRandomGenerator * RNGEngine = QRandomGenerator::system();
// Can be improve but honestly, I'll just keep it shitty LOL
bool checkLuhn(const std::string& cardNo)
{
    int nDigits = cardNo.length();

    int nSum = 0, isSecond = false;
    for (int i = nDigits - 1; i >= 0; i--) {

        int d = cardNo[i] - '0';

        if (isSecond == true)
            d = d * 2;

        // We add two digits to handle
        // cases that make two digits after
        // doubling
        nSum += d / 10;
        nSum += d % 10;

        isSecond = !isSecond;
    }
    return (nSum % 10 == 0);
}

CardInfo genRNGCard()
{
    CardInfo sample;

    // Card Number
    QString cardType = QString::number(RNGEngine->bounded(4,5)); // Master or Visa LOL
    QString ActualNum = QString::number(RNGEngine->bounded(10000000000000,99999999999999)); // All possible combo
    for(int CheckSum=0; CheckSum < 10; CheckSum++) {
        QString strNum = cardType + ActualNum + QString::number(CheckSum);
        if(checkLuhn(strNum.toStdString())) {
            sample.cardNum = strNum;
            break;
        }
    }

    // Expiration
    QString month = QString::number(RNGEngine->bounded(1,12));
    QString year = QString::number(RNGEngine->bounded(2027, 2036));
    sample.expiration = month + "/" + year;

    // CVV
    sample.cvv = QString::number(RNGEngine->bounded(0,999));

    return sample;
}

CardInfo DecActualCard() {
    CardInfo actual;

    return actual;
}