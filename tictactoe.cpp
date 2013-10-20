#include "tictactoe.h"
#include "ui_tictactoe.h"

#include <iostream>

TicTacToe::TicTacToe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);
    turn = 1;
    ItemSetup();
    for (int i; i<=3; i++){
        for (int j;j<=3; j++){
            board[i][j] = 0;
        }
    }

}
void TicTacToe::ItemSetup(){
    QObject::connect(ui->pushButton_1, SIGNAL(clicked(void)),this, SLOT(changeSquare_1()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked(void)),this, SLOT(changeSquare_2()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked(void)),this, SLOT(changeSquare_3()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked(void)),this, SLOT(changeSquare_4()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked(void)),this, SLOT(changeSquare_5()));
    QObject::connect(ui->pushButton_6, SIGNAL(clicked(void)),this, SLOT(changeSquare_6()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked(void)),this, SLOT(changeSquare_7()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked(void)),this, SLOT(changeSquare_8()));
    QObject::connect(ui->pushButton_9, SIGNAL(clicked(void)),this, SLOT(changeSquare_9()));
}

void TicTacToe::changeSquare_1(){
    if (turn == 1 && board[0][0] == 0){
        ui->pushButton_1->setText("X");
        board[0][0] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[0][0] == 0){
        ui->pushButton_1->setText("O");
        board[0][0] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_2(){
    if (turn == 1 && board[0][1] == 0){
        ui->pushButton_2->setText("X");
        board[0][1] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[0][1] == 0){
        ui->pushButton_2->setText("O");
        board[0][1] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_3(){
    if (turn == 1 && board[0][2] == 0){
        ui->pushButton_3->setText("X");
        board[0][2] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[0][2] == 0){
        ui->pushButton_3->setText("O");
        board[0][2] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_4(){
    if (turn == 1 && board[1][0] == 0){
        ui->pushButton_4->setText("X");
        board[1][0] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[1][0] == 0){
        ui->pushButton_4->setText("O");
        board[1][0] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_5(){
    if (turn == 1 && board[1][1] == 0){
        ui->pushButton_5->setText("X");
        board[1][1] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[1][1] == 0){
        ui->pushButton_5->setText("O");
        board[1][1] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_6(){
    if (turn == 1 && board[1][2] == 0){
        ui->pushButton_6->setText("X");
        board[1][2] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[1][2] == 0){
        ui->pushButton_6->setText("O");
        board[1][2] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_7(){
    if (turn == 1 && board[2][0] == 0){
        ui->pushButton_7->setText("X");
        board[2][0] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[2][0] == 0){
        ui->pushButton_7->setText("O");
        board[2][0] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_8(){
    if (turn == 1 && board[2][1] == 0){
        ui->pushButton_8->setText("X");
        board[2][1] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[2][1] == 0){
        ui->pushButton_8->setText("O");
        board[2][1] = 2;
        changePlayer();
    }
}

void TicTacToe::changeSquare_9(){
    if (turn == 1 && board[2][2] == 0){
        ui->pushButton_9->setText("X");
        board[2][2] = 1;
        changePlayer();
    }
    else if (turn ==2 && board[2][2] == 0){
        ui->pushButton_9->setText("O");
        board[2][2] = 2;
        changePlayer();
    }
}

bool TicTacToe::checkIfWon(){
    int rowSum = 0;
    int colSum = 0;
    int diagSum = 0;

    for (int i; i<=3; i++){
        for (int j;j<=3; j++){
            rowSum += board[i][j];
            if (rowSum == 3){
                return 1;
            }
            else if (rowSum == 6){
                return 2;
            }
            else return 0;
        }
        rowSum = 0;
        diagSum += board[i][i];
        if (diagSum == 3){
            return 1;
        }
        else if (diagSum == 6){
            return 2;
        }
        else return 0;
    }
    diagSum = 0;
    for (int i; i<=3; i++){
        for (int j;j<=3; j++){
            colSum += board[j][i];
            if (colSum == 3){
                return 1;
            }
            else if (colSum == 6){
                return 2;
            }
            else return 0;
        }
        colSum = 0;
        diagSum += board[3-i][3-i];
        if (diagSum == 3){
            return 1;
        }
        else if (diagSum == 6){
            return 2;
        }
        else return 0;
    }
}

void TicTacToe::changePlayer(){
    // player 1 -> turn = 1
    // player 2 -> turn = 2
    if (checkIfWon() == 0){
        if (turn == 1){
            turn = 2;
        }
        else turn = 1;
    }
}

TicTacToe::~TicTacToe()
{
    delete ui;
}
