#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QString>
#include <QRandomGenerator>

#endif // ALGORITHMS_H

// "PCI-cerified PII storage" - trust
struct CardInfo {
    QString cardNum;
    QString expiration;
    QString cvv;
};


// QString CipherData = "FBF69215AED0B9F863F4CC372541A697050B3D07F6D1962D79B9";
// QString AuthData = "BD1D09529321CA66F3046AC44B203EAF";
// QString IV = "1617681B97A3B9149B3236BA";
// QString Key = "C2BDB694062DF62FB162F76A6FB95580CC8B3510B056F4BB9AB8CB0A06E20224";

QRandomGenerator * GetRNGEngine();
CardInfo genRNGCardData();
CardInfo DecActualCard();