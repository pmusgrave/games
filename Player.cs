using System.Collections.Generic;

namespace chess
{
    public class Player
    {
        public Player(string color)
        {
            Color = color;
            if (Color == "White")
            {
                ActivePieces = new List<Piece>()
                {
                    new King(new Square(7,4), color),
                    new Queen(new Square(7,3), color),
                    new Rook(new Square(7,0), color),
                    new Rook(new Square(7,7), color),
                    new Bishop(new Square(7,2), color),
                    new Bishop(new Square(7,5), color),
                    new Knight(new Square(7,1), color),
                    new Knight(new Square(7,6), color),
                    new Pawn(new Square(6,0), color),
                    new Pawn(new Square(6,1), color),
                    new Pawn(new Square(6,2), color),
                    new Pawn(new Square(6,3), color),
                    new Pawn(new Square(6,4), color),
                    new Pawn(new Square(6,5), color),
                    new Pawn(new Square(6,6), color),
                    new Pawn(new Square(6,7), color),
                };
            }
            else
            {
                ActivePieces = new List<Piece>()
                {
                    new King(new Square(0,4), color),
                    new Queen(new Square(0,3), color),
                    new Rook(new Square(0,0), color),
                    new Rook(new Square(0,7), color),
                    new Bishop(new Square(0,2), color),
                    new Bishop(new Square(0,5), color),
                    new Knight(new Square(0,1), color),
                    new Knight(new Square(0,6), color),
                    new Pawn(new Square(1,0), color),
                    new Pawn(new Square(1,1), color),
                    new Pawn(new Square(1,2), color),
                    new Pawn(new Square(1,3), color),
                    new Pawn(new Square(1,4), color),
                    new Pawn(new Square(1,5), color),
                    new Pawn(new Square(1,6), color),
                    new Pawn(new Square(1,7), color),
                };
            }
            //store rook and king references to make checking for castles easier
            Rook1 = (Rook)ActivePieces[2];
            Rook2 = (Rook)ActivePieces[3];
            KingPiece = (King)ActivePieces[0];
            CapturedPieces = new List<Piece>();
        }
        public string Color { get; set; }
        public List<Piece> ActivePieces { get; set; }
        public List<Piece> CapturedPieces { get; set; }
        public Piece SelectedPiece { get; set; }
        public King KingPiece { get; set; }
        public Rook Rook1 { get; set; }
        public Rook Rook2 { get; set; }
        public void Castle(Square target)
        {
            if(target.File == 2)
            {
                KingPiece.Position.File = 2;
                Rook1.Position.File = 3;
            }
            else if(target.File == 6)
            {
                KingPiece.Position.File = 6;
                Rook2.Position.File = 5;
            }
        }
        public bool IsInCheck()
        {
            return false;
        }
    }
}
