#include "tictactoe.h"
#include "math.h"
#include "stdexcept"
#include "vector"

TicTacToe::TicTacToe(bool startWithCircle)
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
    cells[row][col] = mNextMark;

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

std::pair<short, short> TicTacToe::computerMove()
{
    // TODO: make computer more intelligent
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
