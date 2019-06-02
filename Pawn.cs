using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    class Pawn : Piece
    {
        public Pawn(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2659": "\u265F";
            FirstMove = true;
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }
        public bool FirstMove { get; set; }
        public void Capture(Piece target)
        {
            throw new NotImplementedException();
        }

        public bool IsAvailableMove(Square target)
        {
            if (FirstMove)
            {
                if((target.Rank == Position.Rank - 1
                || target.Rank == Position.Rank - 2)
                && target.File == Position.File)
                {
                    return true;
                }
            }
            else if (target.Rank == Position.Rank - 1 && target.File == Position.File)
            {
                return true;
            }

            return false;
        }

        public void Move(Square target)
        {
            if (FirstMove)
            {
                FirstMove = false;
            }
            Position.Rank = target.Rank;
            Position.File = target.File;
        }

        public void Remove()
        {
            throw new NotImplementedException();
        }
    }
}
