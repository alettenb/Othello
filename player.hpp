#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <algorithm>
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
    std::vector<Move*> makeListOfMoves(Board * bo, Side s);
    Move * minimax();
    int HeuristicFunction(Move* move, Side side, Side side2);
    Tuple alphaBeta(Board* currentBoard, int depth, int a, int b, Side yourPlayer);
	Tuple absoluteAlphaBeta(Board* currentBoard, int depth, int a, int b, Side yourPlayer);
    bool onEdge(Move* move);
};

#endif
