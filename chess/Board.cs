using System.Windows;
using System.Windows.Media;

namespace chess
{
    public class Board
    {
        MainWindow UI { get; set; }
        public Board(MainWindow ui, Game game)
        {
            CurrentGame = game;
            CurrentGame.GameBoard = this;
            UI = ui;
            RenderPieces();
        }
        Game CurrentGame { get; set; }

        public void RenderPieces()
        {
            ClearBoard();
            foreach (Player player in CurrentGame.Players)
            {
                foreach(Piece piece in player.ActivePieces)
                {
                    System.Windows.Controls.Button piece_button = GetButton(piece.Position);
                    if (piece_button != null)
                    {
                        piece_button.Content = piece.Content;
                    }
                }
            }
        }
        public void ClearBoard()
        {
            foreach(System.Windows.Controls.Button button in UI.ChessBoardGrid.Children)
            {
                button.Content = "";
                button.BorderThickness = new Thickness(1);
                button.BorderBrush = Brushes.Black;
            }
        }
        private System.Windows.Controls.Button GetButton(Square position)
        {
            foreach (System.Windows.Controls.Button button in UI.ChessBoardGrid.Children)
            {
                if(System.Windows.Controls.Grid.GetRow(button) == position.Rank
                && System.Windows.Controls.Grid.GetColumn(button) == position.File)
                {
                    return button;
                }
            }
            return null;
        }
    }
}
