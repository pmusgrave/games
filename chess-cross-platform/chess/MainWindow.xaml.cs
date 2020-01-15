using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace chess
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Game CurrentGame { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Button new_button = new Button();
                    new_button.Width = 100;
                    new_button.Height = 100;
                    new_button.FontSize = 75;
                    new_button.Click += new RoutedEventHandler(this.HandleSquareClick);
                    if(i%2 == 0)
                    {
                        new_button.Background = (j % 2 != 0) ? Brushes.Brown : Brushes.White;
                    }
                    else new_button.Background = (j % 2 == 0) ? Brushes.Brown : Brushes.White;

                    Grid.SetRow(new_button, i);
                    Grid.SetColumn(new_button, j);
                    ChessBoardGrid.Children.Add(new_button);
                }
            }

            CurrentGame = new Game();
            Board board = new Board(this, CurrentGame);
            /*while(game.State == "In Progress")
            {

            }
            if (game.Winner != null)
            {
                MessageBox.Show("Player {0} wins!", game.Winner.Color);
            }
            else
            {
                MessageBox.Show("Stalemate!");
            }*/
        }
        private void HandleSquareClick(object sender, RoutedEventArgs e)
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
        }
    }
}
