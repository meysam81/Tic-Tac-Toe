#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "tictactoe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(TicTacToe *game, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonClicked();  // being used by all the buttons in the game

private:
    Ui::MainWindow *ui;

    TicTacToe *mGame;

    // added from Resources section of the project
    QIcon mCrossLogo = QIcon(":/images/cross.png");
    QIcon mCircleLogo = QIcon(":/images/circle.png");

    ushort mNumberOfButtons;
    QPushButton *mButtons; // an array of push buttons

    const QSize mButtonSize = QSize(50, 50);  // used both for buttonSize & iconSize

    void changeButtonMark(QPushButton *btn, bool gameNextMark = false);

    QString encodeButtonName(short row, short col) const;
    std::pair<short, short> decodeButtonName(QString btnName) const;

    void clearBoard();

    void initializeBoard();

    void playerMoveHandler(QPushButton* btn);

    void gameEnded(QString msg);

    short calculateIndex(short row, short col) const;

    void applyButtonMark(QPushButton* button, short row, short col);
};
#endif // MAINWINDOW_H
