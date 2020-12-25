#include "mainwindow.h"
#include <tictactoe.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToe *game = new TicTacToe(TicTacToe::CIRCLE);
    MainWindow w(game);
    w.show();
    return a.exec();
}
