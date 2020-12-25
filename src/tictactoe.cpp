#include <tictactoe.h>
#include <math.h>
#include <vector>
#include <stdexcept>

TicTacToe::TicTacToe(bool startWithCircle) : mCurrentMark(NONE)
{
    if (startWithCircle) {
        mNextMark = CIRCLE;
    } else {
        mNextMark = CROSS;
    }

    resetGame();
}

TicTacToe::~TicTacToe()
{
    delete[] cells;
}

void TicTacToe::setNextMarkOn(short row, short col)
{
    if (row >= mNumOfRows || col >= mNumOfCols) {
        throw std::invalid_argument("Invalid row or column requested!");
    }
    cells[row][col] = mCurrentMark = mNextMark;

    if (mNextMark == CIRCLE) {
        mNextMark = CROSS;
    } else if (mNextMark == CROSS) {
        mNextMark = CIRCLE;
    }

    mMove++;
}

bool TicTacToe::gameWon() const
{
    for (short i = 0; i < 3; i++) {
        if (equalCells(cells[i][0], cells[i][1], cells[i][2])
                || equalCells(cells[0][i], cells[1][i], cells[2][i]))
        {
            return true;
        }
    }
    if (equalCells(cells[0][0], cells[1][1], cells[2][2])
            || equalCells(cells[2][0], cells[1][1], cells[0][2])) {
        return true;
    }
    return false;
}

bool TicTacToe::gameDraw() const
{
    if ( mMove == mNumOfRows * mNumOfCols ) {
        return true;
    }
    return false;
}

void TicTacToe::resetGame()
{
    // TODO: should we do this or do the GC takes care of this? 🤔
    delete[] cells;

    cells = new Mark*[mNumOfRows];
    for (short i = 0; i < mNumOfRows; i++) {
        cells[i] = new Mark[mNumOfCols];

        for (short j = 0; j < mNumOfCols; j++) {
            // this initialization is because of unpredicted values in runtime
            cells[i][j] = NONE;
        }
    }

    mMove = 0;
}

bool TicTacToe::isEmpty(short row, short col) const
{
    if (cells[row][col] == NONE) {
        return true;
    }
    return false;
}

shortPair TicTacToe::computerMove()
{
    // first, try to win if possible
    for (short i = 0; i < mNumOfRows; i++) {
        if ( twoEqualOneEmpty(shortPair(i, 0), shortPair(i, 1), shortPair(i, 2), mNextMark) ) {
            return theEmptyOne(shortPair(i, 0), shortPair(i, 1), shortPair(i, 2));
        } else if ( twoEqualOneEmpty(shortPair(0, i), shortPair(1, i), shortPair(2, i), mNextMark) ) {
            return theEmptyOne(shortPair(0, i), shortPair(1, i), shortPair(2, i));
        }
    }
    if ( twoEqualOneEmpty(shortPair(0, 0), shortPair(1, 1), shortPair(2, 2), mNextMark) ) {
        return theEmptyOne(shortPair(0, 0), shortPair(1, 1), shortPair(2, 2));
    } else if ( twoEqualOneEmpty(shortPair(2, 0), shortPair(1, 1), shortPair(0, 2), mNextMark) ) {
        return theEmptyOne(shortPair(2, 0), shortPair(1, 1), shortPair(0, 2));
    }

    // second, try to stop the opponent from winning
    for (short i = 0; i < mNumOfRows; i++) {
        if ( twoEqualOneEmpty(shortPair(i, 0), shortPair(i, 1), shortPair(i, 2), mCurrentMark) ) {
            return theEmptyOne(shortPair(i, 0), shortPair(i, 1), shortPair(i, 2));
        } else if ( twoEqualOneEmpty(shortPair(0, i), shortPair(1, i), shortPair(2, i), mCurrentMark) ) {
            return theEmptyOne(shortPair(0, i), shortPair(1, i), shortPair(2, i));
        }
    }
    if ( twoEqualOneEmpty(shortPair(0, 0), shortPair(1, 1), shortPair(2, 2), mCurrentMark) ) {
        return theEmptyOne(shortPair(0, 0), shortPair(1, 1), shortPair(2, 2));
    } else if ( twoEqualOneEmpty(shortPair(2, 0), shortPair(1, 1), shortPair(0, 2), mCurrentMark) ) {
        return theEmptyOne(shortPair(2, 0), shortPair(1, 1), shortPair(0, 2));
    }

    // some of the steps have been commented to ease the play and make it
    // enjoyable because we don't want the computer to always win.
    // uncommenting them would result in not being able to win at all
    // you've been warned


    // third, try to create a two-way situation without giving the opponent one
    // TODO

    // fourth: place it in the center if possible
    if ( cells[1][1] == NONE ){
        return shortPair(1, 1);
    }

//    // fifth, play the opposite corner of the player
//    if ( ! (cells[0][0] & cells[2][2]) && (mCurrentMark & cells[2][2]) && (cells[0][0] & NONE) ) {
//        return shortPair(0, 0);
//    } else if ( ! (cells[0][0] & cells[2][2]) && (NONE & cells[2][2]) && (cells[0][0] & mCurrentMark) ) {
//        return shortPair(2, 2);
//    } else if ( ! (cells[2][0] & cells[0][2]) && (mCurrentMark & cells[2][0]) && (cells[0][2] & NONE) ) {
//        return shortPair(0, 2);
//    } else if ( ! (cells[2][0] & cells[0][2]) && (NONE & cells[2][0]) && (cells[0][2] & mCurrentMark) ) {
//        return shortPair(2, 0);
//    }

//    // sixth, play the empty corner
//    auto corners = { shortPair(0, 0), shortPair(0, 2), shortPair(2, 0), shortPair(2, 2) };
//    for ( auto it = corners.begin(); it != corners.end(); it++ ){
//        if ( cells[it->first][it->second] == NONE ) {
//            return *it;
//        }
//    }

//    // seventh, play an empty side
//    auto sides = { shortPair(0, 1), shortPair(1, 0), shortPair(1, 2), shortPair(2, 1) };
//    for ( auto it = sides.begin(); it != sides.end(); it++ ){
//        if ( cells[it->first][it->second] == NONE ) {
//            return *it;
//        }
//    }

    // last resort: play a random place
    std::vector<std::pair<short, short>> freeCells;
    for (short i = 0; i < mNumOfRows; i++) {
        for (short j = 0; j < mNumOfCols; j++) {
            if ( cells[i][j] == NONE ) {
                freeCells.push_back(std::pair<short, short>(i, j));
            }
        }
    }
    short freeCellSize = freeCells.size();
    if ( freeCellSize > 0) {
        return freeCells[rand() % freeCellSize];
    }

    throw std::invalid_argument("All cells are filled");
}

bool TicTacToe::equalCells(TicTacToe::Mark cell1, TicTacToe::Mark cell2, TicTacToe::Mark cell3) const
{
    if (cell1 != NONE && cell1 == cell2 && cell2 == cell3) {
        return true;
    }
    return false;
}

bool TicTacToe::twoEqualOneEmpty(shortPair first, shortPair second, shortPair third, TicTacToe::Mark mark) const
{
    Mark firstMark = cells[first.first][first.second];
    Mark secondMark = cells[second.first][second.second];
    Mark thirdMark = cells[third.first][third.second];

    if ( ( firstMark & secondMark && firstMark == mark && thirdMark == NONE )
         || ( firstMark & thirdMark && firstMark == mark && secondMark == NONE )
         || ( secondMark & thirdMark && secondMark == mark && firstMark == NONE ) ) {
        return true;
    }
    return false;
}

std::pair<short, short> TicTacToe::theEmptyOne(shortPair first, shortPair second, shortPair third) const
{
    // we assume that one of them is indeed NONE, hence the last return
    if ( cells[first.first][first.second] == NONE ) {
        return first;
    } else if ( cells[second.first][second.second] == NONE ) {
        return second;
    } else {
        return third;
    }
}
