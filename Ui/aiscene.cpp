#include "aiscene.h"
#include <qevent.h>

AIScene::AIScene(gameDifficulty _diff)
   : GameScene(_diff)
{}

// trzeba napisać logikę skakania żaby Ai,
// po tym tutaj uruchomienie tej logiki z każdym updatem gry

void AIScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        // trzeba napisać zamrożenie gry i wywalenie do menu
    }
}
