#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <stdexcept>


class TicTacToe
{
public:
    enum Mark { NONE, CROSS, CIRCLE };

public:
    TicTacToe(Mark startMark);
    ~TicTacToe();

    void setMark(short row, short col, Mark mark);
    Mark mark(short row, short col) const;

    Mark nextMark() const { return mNextMark; }

    short numOfRows() const { return mNumOfRows; }
    short numOfCols() const { return mNumOfCols; }

    bool gameWon() const;
    bool gameDraw() const;

    void resetGame();

    bool isEmpty(short row, short col) const;

    std::pair<short, short> computerMove();

private:
    const short mNumOfRows = 3, mNumOfCols = 3;
    Mark mNextMark;

    Mark **cells;

    ushort mMove = 0;

    bool equalCells(Mark cell1, Mark cell2, Mark cell3) const;
};

#endif // TICTACTOE_H
