#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    yourSide = side;
    if(yourSide == BLACK)
    	otherSide = WHITE;
    else
    	otherSide = BLACK;



    b = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete b;
}


// std::vector<Move*> Player::makeListOfMoves() {
// 	std::vector<Move*> moves;
// 	for(int i = 0; i < 8; i++) {
// 		for(int j = 0; j < 8; j++) {
// 			Move* m = new Move(i, j);
// 			if(b->checkMove(m, yourSide)) {
// 				moves.push_back(m);
// 			}
// 			else {
// 				delete m;
// 			}
// 		}
// 	}
// 	return moves;
// }


std::vector<Move*> Player::makeListOfMoves(Board * bo) {
	std::vector<Move*> moves;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			Move* m = new Move(i, j);
			if(bo->checkMove(m, yourSide)) {
				moves.push_back(m);
			}
			else {
				delete m;
			}
		}
	}
	return moves;
}


int Player::HeuristicFunction(Move* move, Side side, Side side2) {
	Board * newBoard = b->copy();
	newBoard -> doMove(move, side);
	int numberOfChoices = newBoard->count(side) - newBoard->count(side2);
	delete newBoard;
	return numberOfChoices;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 *
 * THIS IS FOR THE FIRST PROBLEM
 */
// Move *Player::doMove(Move *opponentsMove, int msLeft) {

// 	if(opponentsMove) {
// 		b->doMove(opponentsMove, otherSide);
// 	}
// 	if(!b->hasMoves(yourSide)) {
// 		return nullptr;
// 	}
// 	std::vector<Move*> moves = makeListOfMoves();
// 	int moveNum = rand() % moves.size();
// 	srand(msLeft);
// 	b->doMove(moves[moveNum], yourSide);

// 	return moves[moveNum];

// }


Move * Player::minimax() {
	std::vector<Move *> initMoves = makeListOfMoves(b);
	std::vector<int> heuristicNums;
	for(unsigned int i = 0; i < initMoves.size(); i++) {
		Board * newBoard = b->copy();
		newBoard->doMove(initMoves[i], yourSide);
		if(newBoard->hasMoves(yourSide)) {
			std::vector<Move *> newMoves = makeListOfMoves(newBoard);
			int minHeuristic = HeuristicFunction(newMoves[0], yourSide, otherSide);
			for(unsigned int j = 1; j < newMoves.size(); j++) {
				if(HeuristicFunction(newMoves[j], yourSide, otherSide) < minHeuristic)
					minHeuristic = HeuristicFunction(newMoves[j], yourSide, otherSide);
			}
			heuristicNums.push_back(minHeuristic);
		} 
		else 
			heuristicNums.push_back(-65); //This is an impossible value for an 8x8 Othello Board 
	}
	int maximum = heuristicNums[0];
	int index = 0;
	for(int i = 0; i < heuristicNums.size(); i++) {
		if((initMoves[i]->getX() == 0 && initMoves[i]->getY() == 0) || (initMoves[i]->getX() == 7 && initMoves[i]->getY() == 0) 
			|| (initMoves[i]->getX() == 0 && initMoves[i]->getY() == 7) || (initMoves[i]->getX() == 7 && initMoves[i]->getY() == 7)) {

			b->doMove(initMoves[i], yourSide);
			return initMoves[i];
		}
		else if(heuristicNums[i] > maximum) {
			index = i;
			maximum = heuristicNums[i];
		}
	}
	return initMoves[index];

}



/*
 * This is for the second AI that can beat SimplePlayer.
 */
// Move *Player::doMove(Move *opponentsMove, int msLeft) {

// 	if(opponentsMove) {
// 		b->doMove(opponentsMove, otherSide);
// 	}
// 	if(!b->hasMoves(yourSide)) {
// 		return nullptr;
// 	}
// 	std::vector<Move*> moves = makeListOfMoves();
// 	int moveNum = HeuristicFunction(moves[0], yourSide, otherSide);
// 	int index = 0;
// 	if((moves[0]->getX() == 0 && moves[0]->getY() == 0) || (moves[0]->getX() == 7 && moves[0]->getY() == 0) 
// 		|| (moves[0]->getX() == 0 && moves[0]->getY() == 7) || (moves[0]->getX() == 7 && moves[0]->getY() == 7)) {

// 		b->doMove(moves[0], yourSide);
// 		return moves[0];
// 	}
// 	for(unsigned int i = 1; i < moves.size(); i++) {
		// if((moves[i]->getX() == 0 && moves[i]->getY() == 0) || (moves[i]->getX() == 7 && moves[i]->getY() == 0) 
		// 	|| (moves[i]->getX() == 0 && moves[i]->getY() == 7) || (moves[i]->getX() == 7 && moves[i]->getY() == 7)) {

		// 	b->doMove(moves[i], yourSide);
		// 	return moves[i];
		// }
// 		else if(HeuristicFunction(moves[i], yourSide, otherSide) > moveNum) {
// 			index = i;
// 			moveNum = HeuristicFunction(moves[i], yourSide, otherSide);
// 		}
// 	}
// 	b->doMove(moves[index], yourSide);

// 	return moves[index];

// }

/*
 * This is for the minimax function.
 */

Move *Player::doMove(Move *opponentsMove, int msLeft) {

	if(opponentsMove) {
		b->doMove(opponentsMove, otherSide);
	}
	if(!b->hasMoves(yourSide)) {
		return nullptr;
	}
	
	Move * theMove = minimax();
	b->doMove(theMove, yourSide);

	return theMove;

}
