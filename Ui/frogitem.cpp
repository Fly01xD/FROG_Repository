#include "frogitem.h"

FrogItem::FrogItem(CFrog *_frog, QGraphicsItem* parent)
    : logicFrog(_frog), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap("assets/frog.png"));

    //ustawiamy wysokość żaby z = 2 żeby była nad pasem i nad przejściem
    setZValue(2);
}

FrogItem::~FrogItem()
{}
