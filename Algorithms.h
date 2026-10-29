#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <string>
#include <QString>

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

// Key is intentionally left expose for the purpose of reverse engineering as a solution
// Format KEY + IV + AuthData + CipherData
QString SecureData = "C2BDB694062DF62FB162F76A6FB95580CC8B3510B056F4BB9AB8CB0A06E202241617681B97A3B9149B3236BABD1D09529321CA66F3046AC44B203EAF FBF69215AED0B9F863F4CC372541A697050B3D07F6D1962D79B9";

bool checkLuhn(const std::string& cardNo);
CardInfo genRNGCardData();
CardInfo DecActualCard();