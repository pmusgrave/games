#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "piece.h"
#include "game.h"
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,800);

    for(int i = 0; i < ui->gridLayout->count(); ++i) {
      QWidget *widget = ui->gridLayout->itemAt(i)->widget();
      if(widget != NULL){
        //widget->setStyleSheet("background-color:black;");
        connect(widget, SIGNAL(released()), this, SLOT(SquareClickTesting()));
      }
    }

    this->current_game = new Game();
    this->board = new Board(this, current_game);

    std::cout << "main cg: " << current_game << "\n";
    std::cout << "main b: " << board << "\n";
    std::cout << current_game->Players[0] << "\n";
    std::cout << "current player: " << current_game->CurrentPlayer << "\n";
}

MainWindow::~MainWindow()
{
    delete current_game;
    delete board;
    delete ui;
}

void MainWindow::SquareClickTesting(){
  QObject* button = QObject::sender();
  QWidget* button_widget = qobject_cast<QWidget*>(button);
  int index = ui->gridLayout->indexOf(button_widget);
  int row, col, col_span, row_span;
  ui->gridLayout->getItemPosition(index, &row, &col, &col_span, &row_span);
  Square selected_square(row,col);

  std::cout << selected_square.Rank << " " << selected_square.File << "\n";
  std::cout << "click cg: " << current_game << "\n";
  std::cout << "click b: " << board << "\n";
  std::cout << current_game->CurrentPlayer->Color << "\n";
  std::cout << board->CurrentGame->CurrentPlayer << "\n";
}

void MainWindow::HandleSquareClick() {
  QObject* button = QObject::sender();
  QWidget* button_widget = qobject_cast<QWidget*>(button);
  int index = ui->gridLayout->indexOf(button_widget);
  //if(index != -1) {
    int row, col, col_span, row_span;
    ui->gridLayout->getItemPosition(index, &row, &col, &col_span, &row_span);
    Square selected_square(row,col);
    //  }

    /*if(piece->Position->Rank == selected_square.Rank && piece->Position->File == selected_square.File) {
      current_game->GameBoard->RenderPieces();
      current_game->CurrentPlayer->SelectedPiece = *piece;
      //button.BorderThickness = new Thickness(5);
      //button.BorderBrush = Brushes.Blue;
      return;
    }*/


  if (current_game->CurrentPlayer->SelectedPiece != NULL
      && current_game->IsValidCastle(current_game->CurrentPlayer->SelectedPiece, &selected_square))
    {
      current_game->CurrentPlayer->Castle(&selected_square);
      current_game->GameBoard->RenderPieces();
      // selected_square_button.BorderThickness = new Thickness(1);
      // selected_square_button.BorderBrush = Brushes.Black;
      current_game->SwitchPlayers();
      current_game->CurrentPlayer->SelectedPiece = NULL;
    }
  else if (current_game->CurrentPlayer->SelectedPiece != NULL
           && current_game->IsValidMove(current_game->CurrentPlayer->SelectedPiece, &selected_square))
    {
      current_game->CurrentPlayer->SelectedPiece->Move(&selected_square);
      current_game->GameBoard->RenderPieces();
      //selected_square_button.BorderThickness = new Thickness(1);
      //selected_square_button.BorderBrush = Brushes.Black;
      current_game->SwitchPlayers();
      current_game->CurrentPlayer->SelectedPiece = NULL;
    }
  else if (current_game->CurrentPlayer->SelectedPiece != NULL
           && current_game->IsValidCapture(current_game->CurrentPlayer->SelectedPiece, &selected_square))
    {
      current_game->CurrentPlayer->SelectedPiece->Move(&selected_square);
        //      List<Player> player_filter = current_game->Players
        //        .Where(player => player != current_game->CurrentPlayer).ToList();
      Player* OtherPlayer = current_game->CurrentPlayer == current_game->Players[0] ?
        current_game->Players[1] :
        current_game->Players[0];

      Piece* capture;
      for(int i = 0; i < OtherPlayer->ActivePieces.size(); i++) {
        Piece* piece = OtherPlayer->ActivePieces[i];
        if(piece->Position->Rank == selected_square.Rank
           && piece->Position->File == selected_square.File){
          capture = piece;
        }
      }

      //      IEnumerable<Piece> capture = OtherPlayer.ActivePieces
      //        .Where(piece =>
      //               piece.Position.Rank == selected_square.Rank
      //               && piece.Position.File == selected_square.File);
      OtherPlayer->CapturedPieces.push_back(capture);
      int capture_index = -1;
      for(int i = 0; i < OtherPlayer->ActivePieces.size(); i++){
        if(OtherPlayer->ActivePieces[i] == capture) {
          capture_index = i;
        }
      }
      if(capture_index != -1) {
        OtherPlayer->ActivePieces.erase(OtherPlayer->ActivePieces.begin() + capture_index);
      }

      current_game->GameBoard->RenderPieces();
      //selected_square_button.BorderThickness = new Thickness(1);
      //selected_square_button.BorderBrush = Brushes.Black;
      current_game->SwitchPlayers();
      current_game->CurrentPlayer->SelectedPiece = NULL;
    }
}

