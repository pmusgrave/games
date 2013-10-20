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

private:
    Ui::TicTacToe *ui;
    int turn;
    void ItemSetup();
    bool checkIfWon();
    void changePlayer();    

public slots:    
    void changeSquare_1();
    void changeSquare_2();
    void changeSquare_3();
    void changeSquare_4();
    void changeSquare_5();
    void changeSquare_6();
    void changeSquare_7();
    void changeSquare_8();
    void changeSquare_9();

};

#endif // TICTACTOE_H
