#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <qgraphicsview.h>

class GameView : public QGraphicsView
{
public:
    GameView(QWidget* parent);
    ~GameView();
private slots:
    void updateScene();
    void pauseScene();
};

#endif // GAMEVIEW_H
