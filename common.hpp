#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

class Tuple
{
public:
    Move * move;
    int value;
    Tuple(Move* a, int b) {
        move = a;
        value = b;
    }
    ~Tuple() {

    }
    int getVal() {
        return value;
    }
    Move* getMove() {
        return move;
    }

    void setMove(Move * m) {
        move = m;
    }

    void setVal(int v) {
        value = v;
    }
};

#endif


