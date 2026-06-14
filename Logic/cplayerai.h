#ifndef CPLAYERAI_H
#define CPLAYERAI_H

#include "cplayerbase.h"
#include <qobject.h>
#include <QTimer>
#include <random>

class CPlayerAI : public CPlayerBase, public QObject
{
    Q_OBJECT
private:
    QTimer checkTimer;
    // nie ma timera na reakcje bo może być dynamiczny
    // tzn. usuwany po użyciu - skoro czas reakcji będzie się zmieniał
    std::random_device seed; // ziarno do losowania opóźnienia
    std::mt19937 gen; // generator do losowania opóźnienia
    std::normal_distribution<double> d; // dystrybujca

    int minDelay;
    int maxDelay;
public:
    CPlayerAI(CRoad* _road);
    ~CPlayerAI();

    void jumpOnKey() override;
    void jumpOnCalc() override;

    void playerAIPause() override;

    unsigned n = getN();
private slots:
    bool calculate(); // decyzja o skakaniu dlatego bool
    // 1 - skacze, 0 - stoi
};

#endif // CPLAYERAI_H
