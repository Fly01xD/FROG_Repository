#ifndef AISCENE_H
#define AISCENE_H

#include "gamescene.h"

class AIScene : protected GameScene
{
public:
    AIScene(gameDifficulty _diff);
    ~AIScene();

    // przechodzenie do menu
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // AISCENE_H
