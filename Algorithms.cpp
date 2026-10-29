#include <QRandomGenerator>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/core_names.h>
#include "Algorithms.h"


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

    const QByteArray key = QByteArray::fromHex(SecureData.slice(0,32*2).toLatin1());
    const QByteArray iv = QByteArray::fromHex(SecureData.slice(32*2,12*2).toLatin1());
    const QByteArray tag = QByteArray::fromHex(SecureData.slice(32*2 + 12*2,16*2).toLatin1());
    const QByteArray data = QByteArray::fromHex(SecureData.slice(32*2 + 12*2 + 16*2).toLatin1());

    int outlen;
    unsigned char DecBufferData[data.length()];

    EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER *cipher = EVP_CIPHER_fetch(NULL, "AES-256-GCM", NULL);
    OSSL_PARAM params[2] = {OSSL_PARAM_END, OSSL_PARAM_END};
    EVP_DecryptInit_ex2(
        ctx,
        cipher,
        reinterpret_cast<const unsigned char*>(key.constData()),
        reinterpret_cast<const unsigned char*>(iv.constData()),
        params
    );
    // EVP_DecryptUpdate(ctx, &outlen, aad, sizeof(aad));
    // @TODO: Use https://github.com/openssl/openssl/blob/master/demos/cipher/aesgcm.c to complete this

    return actual;
}