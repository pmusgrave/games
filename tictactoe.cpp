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
    ui->pushButton_1->setText("X");
}

void TicTacToe::changeSquare_2(){
    ui->pushButton_2->setText("X");
}

void TicTacToe::changeSquare_3(){
    ui->pushButton_3->setText("X");
}

void TicTacToe::changeSquare_4(){
    ui->pushButton_4->setText("X");
}

void TicTacToe::changeSquare_5(){
    ui->pushButton_5->setText("X");
}

void TicTacToe::changeSquare_6(){
    ui->pushButton_6->setText("X");
}

void TicTacToe::changeSquare_7(){
    ui->pushButton_7->setText("X");
}

void TicTacToe::changeSquare_8(){
    ui->pushButton_8->setText("X");
}

void TicTacToe::changeSquare_9(){
    ui->pushButton_9->setText("X");
}

bool checkIfWon(){

}

void changePlayer(){

}

TicTacToe::~TicTacToe()
{
    delete ui;
}
