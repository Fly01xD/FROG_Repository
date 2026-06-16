#ifndef FROGITEM_H
#define FROGITEM_H

#include "CFrog.h"
#include <QGraphicsPixmapItem>

class FrogItem : public QGraphicsPixmapItem
{
    CFrog* logicFrog;
public:
    FrogItem(CFrog* _frog, QGraphicsItem* parent = nullptr);
    ~FrogItem();
};

#endif // FROGITEM_H
