#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*private void HandleSquareClick()
{
    Button selected_square_button = (Button)sender;
    Square selected_square = new Square(
        Grid.GetRow(selected_square_button),
        Grid.GetColumn(selected_square_button));

    foreach (Piece piece in CurrentGame.CurrentPlayer.ActivePieces)
    {
        if (piece.Position.Rank == selected_square.Rank
        && piece.Position.File == selected_square.File)
        {
            CurrentGame.GameBoard.RenderPieces();
            CurrentGame.CurrentPlayer.SelectedPiece = piece;
            selected_square_button.BorderThickness = new Thickness(5);
            selected_square_button.BorderBrush = Brushes.Blue;
            return;
        }
    }

    if (CurrentGame.CurrentPlayer.SelectedPiece != null
    && selected_square != null
    && CurrentGame.IsValidCastle(CurrentGame.CurrentPlayer.SelectedPiece, selected_square))
    {
        CurrentGame.CurrentPlayer.Castle(selected_square);
        CurrentGame.GameBoard.RenderPieces();
        selected_square_button.BorderThickness = new Thickness(1);
        selected_square_button.BorderBrush = Brushes.Black;
        CurrentGame.SwitchPlayers();
        CurrentGame.CurrentPlayer.SelectedPiece = null;
    }
    else if (CurrentGame.CurrentPlayer.SelectedPiece != null
    && selected_square != null
    && CurrentGame.IsValidMove(CurrentGame.CurrentPlayer.SelectedPiece, selected_square))
    {
        CurrentGame.CurrentPlayer.SelectedPiece.Move(selected_square);
        CurrentGame.GameBoard.RenderPieces();
        selected_square_button.BorderThickness = new Thickness(1);
        selected_square_button.BorderBrush = Brushes.Black;
        CurrentGame.SwitchPlayers();
        CurrentGame.CurrentPlayer.SelectedPiece = null;
    }
    else if (CurrentGame.CurrentPlayer.SelectedPiece != null
    && selected_square != null
    && CurrentGame.IsValidCapture(CurrentGame.CurrentPlayer.SelectedPiece, selected_square))
    {
        CurrentGame.CurrentPlayer.SelectedPiece.Move(selected_square);
        List<Player> player_filter = CurrentGame.Players
            .Where(player => player != CurrentGame.CurrentPlayer).ToList();
        Player OtherPlayer = player_filter[0];

        IEnumerable<Piece> capture = OtherPlayer.ActivePieces
            .Where(piece =>
                piece.Position.Rank == selected_square.Rank
                && piece.Position.File == selected_square.File);
        OtherPlayer.CapturedPieces.Add(capture.First());
        OtherPlayer.ActivePieces.Remove(capture.First());

        CurrentGame.GameBoard.RenderPieces();
        selected_square_button.BorderThickness = new Thickness(1);
        selected_square_button.BorderBrush = Brushes.Black;
        CurrentGame.SwitchPlayers();
        CurrentGame.CurrentPlayer.SelectedPiece = null;
    }
}*/
