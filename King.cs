using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    public class King : Piece
    {
        public King(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2654" : "\u265A";
            FirstMove = true;
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }
        public bool FirstMove { get; set; }
        
        public bool IsAvailableMove(Square target)
        {
            if (FirstMove)
            {
                return (target.Rank == Position.Rank && Math.Abs(target.File - Position.File) == 1)
                || (target.File == Position.File && Math.Abs(target.Rank - Position.Rank) == 1)
                || (Math.Abs(target.File - Position.File) == 1 && Math.Abs(target.Rank - Position.Rank) == 1)
                || (Math.Abs(target.Rank - Position.Rank) == 1 && Math.Abs(target.File - Position.File) == 1)
                || (Math.Abs(target.File - Position.File) == 2) && target.Rank == Position.Rank;
            }
            else return (target.Rank == Position.Rank && Math.Abs(target.File - Position.File) == 1)
                || (target.File == Position.File && Math.Abs(target.Rank - Position.Rank) == 1)
                || (Math.Abs(target.File - Position.File) == 1 && Math.Abs(target.Rank - Position.Rank) == 1)
                || (Math.Abs(target.Rank - Position.Rank) == 1 && Math.Abs(target.File - Position.File) == 1);
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
