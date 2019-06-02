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

        public bool CanCapture(Square target)
        {
            throw new NotImplementedException();
        }

        public void Capture(Square target)
        {
            throw new NotImplementedException();
        }

        public bool IsAvailableMove(Square target)
        {
            if ((Position.Rank == target.Rank + 1
              || Position.Rank == target.Rank - 1
              || Position.Rank == target.Rank)
             && (Position.File == target.File + 1
             || Position.File == target.File - 1
             || Position.File == target.File))
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
