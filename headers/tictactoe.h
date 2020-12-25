#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>
#define shortPair std::pair<short, short>


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

    shortPair computerMove();

    bool isNextMarkCircle() const {return mNextMark == CIRCLE; }
    bool isNextMarkCross() const {return mNextMark == CROSS; }

private:
    enum Mark { NONE, CROSS, CIRCLE };

    const short mNumOfRows = 3, mNumOfCols = 3;
    Mark mNextMark, mCurrentMark;

    Mark **cells;

    ushort mMove = 0;

    bool equalCells(Mark cell1, Mark cell2, Mark cell3) const;

    bool twoEqualOneEmpty(shortPair first, shortPair second, shortPair third, Mark mark) const;
    shortPair theEmptyOne(shortPair first, shortPair second, shortPair third) const;
};

#endif // TICTACTOE_H
