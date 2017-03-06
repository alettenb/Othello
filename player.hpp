#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    Board* b;
    Side yourSide;
    Side otherSide;
    bool testingMinimax;
    std::vector<Move*> makeListOfMoves(Board * bo);
    Move * minimax();
    int HeuristicFunction(Move* move, Side side, Side side2);
};

#endif
