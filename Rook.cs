using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    class Rook : Piece
    {
        public Rook(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2656" : "\u265C";
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }

        public bool IsAvailableMove(Square target)
        {
            throw new NotImplementedException();
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
