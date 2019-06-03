using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    class Queen : Piece
    {
        public Queen(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2655" : "\u265B";
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }

        public bool IsAvailableMove(Square target)
        {
            return ((Math.Abs(target.Rank - Position.Rank) == Math.Abs(target.File - Position.File))
            || ((target.Rank == Position.Rank && target.File != Position.File)
                || (target.File == Position.File && target.Rank != Position.Rank)));
        }
        public bool CanCapture(Square target)
        {
            return IsAvailableMove(target);
        }
        public void Move(Square target)
        {
            Position.Rank = target.Rank;
            Position.File = target.File;
        }
    }
}
