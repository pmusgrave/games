﻿namespace chess
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

        public bool IsValidMove(Piece selected_piece, Square target)
        {
            if (!CurrentPlayer.IsInCheck()
             && !IsSquareOccupied(target)
             && selected_piece.IsAvailableMove(target))
            {
                return true;
            }
            else return false;
        }
        public bool IsSquareOccupied(Square target)
        {
            // only checks if current player's pieces occupy target.
            // This function shouldn't interfere with captures
            foreach(Piece piece in CurrentPlayer.ActivePieces)
            {
                if (piece.Position.Rank == target.Rank 
                    && piece.Position.File == target.File)
                {
                    return true;
                }
            }

            return false;
        }
        public void SwitchPlayers()
        {
            CurrentPlayer = Players[(System.Array.IndexOf(Players, CurrentPlayer) + 1) % 2];
        }
    }
}
