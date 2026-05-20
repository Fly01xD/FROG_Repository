#ifndef CWRITER_H
#define CWRITER_H
#include "SGameData.h"

class CWriter {
private:
    GameData *MyData;
public:
    CWriter(GameData *_data);
    void SaveScore(GameData *_data);
};

#endif //CWRITER_H