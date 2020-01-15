#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class Game;
class Board;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Game* current_game;
    Board* board;

private:
    Ui::MainWindow *ui;

private slots:
  //    void SquarePressed();
};

#endif // MAINWINDOW_H
