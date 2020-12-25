#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QAction>

MainWindow::MainWindow(TicTacToe *game, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mGame(game)
    , mNumberOfButtons(mGame->numOfRows() * mGame->numOfCols())
    , mButtons(new QPushButton[mNumberOfButtons])
{
    ui->setupUi(this);

    // to place all the customizations in the same place
    initializeBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mGame;
    delete[] mButtons;
}


void MainWindow::clearBoard()
{
    // both reset the board & the game
    for (short i = 0; i < mNumberOfButtons; i++) {
        changeButtonMark(&mButtons[i]);
    }
    mGame->resetGame();
}

void MainWindow::initializeBoard()
{
    for (short i = 0; i < mGame->numOfRows(); i++) {
        for (short j = 0; j < mGame->numOfRows(); j++) {
            const short index = calculateIndex(i, j);
            mButtons[index].setMinimumSize(mButtonSize);
            mButtons[index].setMaximumSize(mButtonSize);
            mButtons[index].setObjectName(encodeButtonName(i, j));
            mButtons[index].setIconSize(mButtonSize);

            ui->gridMain->addWidget(&mButtons[index], i, j);
            connect(&mButtons[index], &QPushButton::clicked, this, &MainWindow::on_buttonClicked);
        }
    }
}

void MainWindow::playerMoveHandler(QPushButton *btn)
{
    std::pair<short, short> rowCol = decodeButtonName(btn->objectName());
    short row = rowCol.first;
    short col = rowCol.second;

    if ( mGame->isEmpty(row, col) ) {
        applyButtonMark(btn, row, col);
    } else {  // the player didn't make a move so we stop processing
        ui->statusbar->showMessage("Already Marked!", 500);
        return;
    }

    if ( mGame->gameWon() ) {
        // the last move was from the player so he is the winner
        gameEnded("You Won");
    } else if ( mGame->gameDraw() ) {
        // if there is no winner and all the cells are filled
        gameEnded("Draw");
    }

    std::pair<short, short> computer = mGame->computerMove();
    short index = calculateIndex(computer.first, computer.second);

    applyButtonMark(&mButtons[index], computer.first, computer.second);

    if ( mGame-> gameWon() ) {
        // the computer made the last move so he is the winner
        gameEnded("You Lost");
    } else if ( mGame->gameDraw() ) {
        // if there is no winner and all the cells are filled
        gameEnded("Draw");
    }
}

void MainWindow::gameEnded(QString msg)
{
    QMessageBox *dialog = new QMessageBox(this);
    dialog->setText(msg);
    dialog->exec();
    clearBoard();
}

short MainWindow::calculateIndex(short row, short col) const
{
    return row * mGame->numOfRows() + col;
}

void MainWindow::applyButtonMark(QPushButton *button, short row, short col)
{
    changeButtonMark(button, true);
    mGame->setNextMarkOn(row, col);
}


void MainWindow::on_buttonClicked()
{
    // sender is to help fetch the button that triggered the event
    QPushButton *button = (QPushButton *)sender();
    playerMoveHandler(button);
}

void MainWindow::changeButtonMark(QPushButton *btn, bool gameNextMark)
{
    if (gameNextMark) {
        if ( mGame->isNextMarkCircle() ) {
            btn->setIcon(mCircleLogo);
        } else if ( mGame->isNextMarkCross() ) {
            btn->setIcon(mCrossLogo);
        }
    } else {
        btn->setIcon(QIcon());
    }
}

QString MainWindow::encodeButtonName(short row, short col) const
{
    return QString("btn%0%1").arg(row).arg(col);
}

std::pair<short, short> MainWindow::decodeButtonName(QString btnName) const
{
    // this is a protocol of our own when setting the objectName in initializeBoard
    QRegExp regex("(\\d)(\\d)");

    regex.indexIn(btnName);
    QStringList indices = regex.capturedTexts();

    short row = indices[1].toShort();
    short col = indices[2].toShort();

    return std::pair<short, short>(row, col);
}
