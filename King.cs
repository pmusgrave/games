using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    class King : Piece
    {
        public King(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2654" : "\u265A";
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }

        public void Capture(Piece target)
        {
            throw new NotImplementedException();
        }

        public bool IsAvailableMove(Square target)
        {
            if ((Position.Rank == target.Rank + 1
              || Position.Rank == target.Rank - 1
              || Position.Rank == target.Rank)
             &&(Position.File == target.File + 1
             || Position.File == target.File - 1
             || Position.File == target.File)
             &&(Position.Rank != target.Rank && Position.File != target.File))
            {
                return true;
            }
            else return false;
        }

        public void Move(Square target)
        {
            throw new NotImplementedException();
        }

        public void Remove()
        {
            throw new NotImplementedException();
        }
    }
}
