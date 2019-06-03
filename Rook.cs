using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    public class Rook : Piece
    {
        public Rook(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2656" : "\u265C";
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
                return (target.Rank == Position.Rank && target.File != Position.File)
                    || (target.File == Position.File && target.Rank != Position.Rank);
            }
            else
            {
                return (target.Rank == Position.Rank && target.File != Position.File)
                 || (target.File == Position.File && target.Rank != Position.Rank);
            }
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
