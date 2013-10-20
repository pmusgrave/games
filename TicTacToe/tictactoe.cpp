#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <iostream>

TicTacToe::TicTacToe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);
    ItemSetup();

}
void TicTacToe::ItemSetup(){
    QObject::connect(ui->pushButton, SIGNAL(clicked(void)),this, SLOT(changeSquare(void)));
}

void TicTacToe::changeSquare(){
    ui->pushButton->setText("X");
}
bool checkIfWon(){

}

void changePlayer(){

}

TicTacToe::~TicTacToe()
{
    delete ui;
}
