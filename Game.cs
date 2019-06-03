using System;

namespace chess
{
    public class Game
    {
        public Game()
        {
            Player Player1 = new Player("White");
            Player Player2 = new Player("Black");
            Players = new Player[]
            {
                Player1,
                Player2
            };
            CurrentPlayer = Player1;
            State = "In Progress";
        }
        public Board GameBoard { get; set; }
        public Player[] Players { get; set; }
        public Player CurrentPlayer { get; set; }
        public string State { get; set; }
        public Player Winner { get; set; }

        public bool IsValidCastle(Piece selected_piece, Square target)
        {
            if (ReferenceEquals(selected_piece.GetType(), new King(new Square(0, 0), "White").GetType())
            && (target.File - selected_piece.Position.File) == -2
            && target.Rank == selected_piece.Position.Rank
            && (!IsSquareOccupied(new Square(0, selected_piece.Position.File - 1))
                  && !IsSquareOccupied(new Square(0, selected_piece.Position.File - 2))
                  && !IsSquareOccupied(new Square(0, selected_piece.Position.File - 3))))

            {
                King king = (King)selected_piece;
                if (king.FirstMove && CurrentPlayer.Rook1.FirstMove) return true;
            }
            else if (ReferenceEquals(selected_piece.GetType(), new King(new Square(0, 0), "White").GetType())
            && (target.File - selected_piece.Position.File) == 2
            && target.Rank == selected_piece.Position.Rank
            && (!IsSquareOccupied(new Square(0, selected_piece.Position.File + 1))
                  && !IsSquareOccupied(new Square(0, selected_piece.Position.File + 2))))
            {
                King king = (King)selected_piece;
                if (king.FirstMove && CurrentPlayer.Rook2.FirstMove) return true;
            }
            else if (ReferenceEquals(selected_piece.GetType(), new Rook(new Square(0, 0), "White").GetType())
            && (target.File - selected_piece.Position.File) == 3
            && target.Rank == selected_piece.Position.Rank
            && (!IsSquareOccupied(new Square(0, selected_piece.Position.File + 1))
                  && !IsSquareOccupied(new Square(0, selected_piece.Position.File + 2))
                  && !IsSquareOccupied(new Square(0, selected_piece.Position.File + 3))))
            {
                if (CurrentPlayer.KingPiece.FirstMove && CurrentPlayer.Rook1.FirstMove) return true;
            }
            else if (ReferenceEquals(selected_piece.GetType(), new Rook(new Square(0, 0), "White").GetType())
            && (target.File - selected_piece.Position.File) == -2
            && target.Rank == selected_piece.Position.Rank
            && (!IsSquareOccupied(new Square(0, selected_piece.Position.File - 1))
                  && !IsSquareOccupied(new Square(0, selected_piece.Position.File - 2))))
            {
                if (CurrentPlayer.KingPiece.FirstMove && CurrentPlayer.Rook2.FirstMove) return true;
            }

            return false;
        }
        public bool IsValidMove(Piece selected_piece, Square target)
        {
            if (!CurrentPlayer.IsInCheck() 
            && (!IsSquareOccupied(target) && selected_piece.IsAvailableMove(target)))
            {
                return true;
            }
            else return false;
        }
        public bool IsValidCapture(Piece selected_piece, Square target)
        {
            if (IsSquareOccupied(target) && selected_piece.CanCapture(target))
            {
                return true;
            }
            else return false;
        }
        public bool IsSquareOccupied(Square target)
        {
            foreach (Player player in Players)
            {
                foreach (Piece piece in player.ActivePieces)
                {
                    if (piece.Position.Rank == target.Rank
                        && piece.Position.File == target.File)
                    {
                        return true;
                    }
                }
            }

            return false;
        }
        public void SwitchPlayers()
        {
            CurrentPlayer = (CurrentPlayer == Players[0]) ? Players[1] : Players[0];
        }
    }
}
