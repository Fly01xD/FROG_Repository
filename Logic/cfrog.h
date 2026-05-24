#ifndef CFROG_H
#define CFROG_H

enum frogState {
    alive,
    dead
};

class CFrog
{
    int HP;
    int Points;
    frogState State;

public:
    CFrog(int _hp);
    ~CFrog();

    // gettery settery
    int getPoints();
    void setPoints(int _points);
    void addPoint();
    int getHP();
    void setHP(int _hp);
    void addHP();
    frogState getState();
    void setState(frogState _state);
};

#endif // CFROG_H
