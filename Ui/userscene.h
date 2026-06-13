#ifndef USERSCENE_H
#define USERSCENE_H

#include "gamescene.h"

class UserScene : public GameScene
{
public:
    UserScene(gameDifficulty _diff);
    ~UserScene();

    // skakanie żaby
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // USERSCENE_H
