#include "board.hpp"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}


int Board::cornersOccupied(Side s) {
    int cornersSoFar = 0;
    if(get(s, 0, 0))
        cornersSoFar++;
    if(get(s, 0, 7))
        cornersSoFar++;
    if(get(s, 7, 7))
        cornersSoFar++;
    if(get(s, 7, 0))
        cornersSoFar++;
    return cornersSoFar;
}

int Board::weightedCount(Side s) {
    int count = 0;
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            if(get(s, x, y)) {
                if((x == 0 && y == 0) || (x == 7 && y == 0) 
                    || (x == 0 && y == 7) || (x == 7 && y == 7))
                    count += 100;
                else if((x == 0 && (y == 1 || y == 6)) || 
                    (x == 1 && (y == 0 ||  
                         y == 7 )) || 
                            (x == 6 && (y == 0 ||  
                             y == 7 )) || 
                            (x == 7 && (y == 1 || y == 6)))
                    count -= 20;
                else if((x == 1 && (y == 1 || y == 6)) ||
                    (x == 6 && (y == 1 || y == 6)))
                    count -= 50;
                else if(x == 0 && (y == 2 || y == 5))
                    count += 10;
                else if(x == 7 && !(y == 2 || y == 5))
                    count += 10;
                else if(y == 0 && !(x == 2 || x == 5))
                    count += 10;
                else if(y == 7 && !(x == 2 || x == 5))
                    count += 10;
                else if(x == 0 && (y == 3 || y == 4))
                    count += 5;
                else if(x == 7 && !(y == 3 || y == 4))
                    count += 5;
                else if(y == 0 && !(x == 3 || x == 4))
                    count += 5;
                else if(y == 7 && !(x == 3 || x == 4))
                    count += 5;
                else if(x >= 2 && x <= 5 && y >= 2 && y <= 5) {
                    count -= 1;
                }
                else {
                    count -= 2;
                }
            }

        }
    }
    return count;
}
