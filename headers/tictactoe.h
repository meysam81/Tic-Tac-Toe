#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>


class TicTacToe
{
public:
    TicTacToe(bool startWithCircle = true);
    ~TicTacToe();

    void setNextMarkOn(short row, short col);

    short numOfRows() const { return mNumOfRows; }
    short numOfCols() const { return mNumOfCols; }

    bool gameWon() const;
    bool gameDraw() const;

    void resetGame();

    bool isEmpty(short row, short col) const;

    std::pair<short, short> computerMove();

    bool isNextMarkCircle() const {return mNextMark == CIRCLE; }
    bool isNextMarkCross() const {return mNextMark == CROSS; }

private:
    enum Mark { NONE, CROSS, CIRCLE };

    const short mNumOfRows = 3, mNumOfCols = 3;
    Mark mNextMark;

    Mark **cells;

    ushort mMove = 0;

    bool equalCells(Mark cell1, Mark cell2, Mark cell3) const;
};

#endif // TICTACTOE_H
