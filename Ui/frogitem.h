#ifndef FROGITEM_H
#define FROGITEM_H

#include "CFrog.h"
#include <QGraphicsPixmapItem>

class FrogItem : public QGraphicsPixmapItem
{
    CFrog* logicFrog;
public:
    FrogItem(CFrog* _frog, QGraphicsItem* parent = nullptr) : QGraphicsPixmapItem(parent)
    {
        setPixmap(QPixmap("assets/frog.png"));

        //ustawiamy wysokość żaby z = 2 żeby była nad pasem i nad przejściem
        setZValue(2);
    }
};

#endif // FROGITEM_H
