#include <QList>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/core_names.h>
#include <QMediaPlayer>
#include <QFile>
#include <QAudioOutput>

#include "Algorithms.h"


QRandomGenerator * RNGEngine = QRandomGenerator::system();

// Key is intentionally left expose for the purpose of reverse engineering as a solution
// Format KEY + IV + AuthData + CipherData
QString SecureData = "C2BDB694062DF62FB162F76A6FB95580CC8B3510B056F4BB9AB8CB0A06E202241617681B97A3B9149B3236BABD1D09529321CA66F3046AC44B203EAFFBF69215AED0B9F863F4CC372541A697050B3D07F6D1962D79B9";

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
    QString cardType = QString::number(RNGEngine->bounded(4,5 + 1)); // Master or Visa LOL
    QString ActualNum = QString::number(RNGEngine->bounded(10000000000000,99999999999999 + 1)); // All possible combo
    for(int CheckSum=0; CheckSum < 10; CheckSum++) {
        QString strNum = cardType + ActualNum + QString::number(CheckSum);
        if(checkLuhn(strNum.toStdString())) {
            sample.cardNum = strNum;
            break;
        }
    }

    // Expiration
    QString month = QString::number(RNGEngine->bounded(1,12 + 1));
    QString year = QString::number(RNGEngine->bounded(27, 36 + 1));
    sample.expiration = month + "/" + year;

    // CVV
    quint64 intcvv = RNGEngine->bounded(0,999 + 1);
    sample.cvv = QString::number(intcvv);
    if(intcvv%100 == intcvv)
        sample.cvv = "0" + sample.cvv;

    return sample;
}

CardInfo DecActualCard() {
    CardInfo actual;

    const QByteArray key = QByteArray::fromHex(SecureData.sliced(0,32*2).toLatin1());
    const QByteArray iv = QByteArray::fromHex(SecureData.sliced(32*2,12*2).toLatin1());
    const QByteArray tag = QByteArray::fromHex(SecureData.sliced(32*2 + 12*2,16*2).toLatin1());
    const QByteArray data = QByteArray::fromHex(SecureData.sliced(32*2 + 12*2 + 16*2).toLatin1());

    int outlen, rv;
    unsigned char * DecBufferData = (unsigned char*)malloc(data.length()*sizeof(unsigned char));

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
    EVP_DecryptUpdate(ctx, DecBufferData, &outlen, reinterpret_cast<const unsigned char*>(data.constData()), data.length());
    params[0] = OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_AEAD_TAG, (void *)tag.constData(), tag.length());
    EVP_CIPHER_CTX_set_params(ctx, params);
    rv = EVP_DecryptFinal_ex(ctx, DecBufferData, &outlen);

    if(rv <= 0) {
        // Data tampered, return default cred
        free(DecBufferData);
        actual.cardNum = "0000000000000000";
        actual.expiration = "00/00";
        actual.cvv = "000";
        return actual;
    }

    QString plaintxt = QString(QByteArray::fromRawData(reinterpret_cast<const char*>(DecBufferData), data.length()));
    QList<QString> split_txt = plaintxt.split("|");
    actual.cardNum = split_txt[0];
    actual.expiration = split_txt[1];
    actual.cvv = split_txt[2];

    free(DecBufferData);
    return actual;
}

QRandomGenerator * GetRNGEngine() {
    return RNGEngine;
}

QMediaPlayer *player = NULL;
QAudioOutput *audio = NULL;

void PlayBackgroundOnRepeat(QWidget* parent) {
    if(player != NULL) return;
    player = new QMediaPlayer(parent);
    audio = new QAudioOutput(parent);

    player->setAudioOutput(audio);
    audio->setVolume(1);
    player->setSource(QUrl("qrc:/audio/mainSound"));
    player->setLoops(QMediaPlayer::Infinite);
    player->play();
}