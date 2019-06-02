using System;

namespace chess
{
    class Bishop : Piece
    {
        public Bishop(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2657" : "\u265D";
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }
       
        public bool IsAvailableMove(Square target)
        {
            if (Math.Abs(target.Rank - Position.Rank) == Math.Abs(target.File - Position.File))
            {
                return true;
            }
            else return false;
        }
        public bool CanCapture(Square target)
        {
            if (IsAvailableMove(target)) return true;
            else return false;
        }
        public void Move(Square target)
        {
            Position.Rank = target.Rank;
            Position.File = target.File;
        }
    }
}
