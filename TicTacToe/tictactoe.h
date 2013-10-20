#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>

namespace Ui {
class TicTacToe;
}

class TicTacToe : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TicTacToe(QWidget *parent = 0);
    ~TicTacToe();
    int turns;

private:
    Ui::TicTacToe *ui;
    void ItemSetup();

public slots:
    void changeSquare();

};

#endif // TICTACTOE_H
