#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <string>
#include <QString>

#endif // ALGORITHMS_H

// PCI-cerified algorithm - trust
struct CardInfo {
    QString cardNum;
    QString expiration;
    QString cvv;
};


bool checkLuhn(const std::string& cardNo);
CardInfo genRNGCardData();
CardInfo DecActualCard();