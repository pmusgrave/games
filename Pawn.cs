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
            DirectionMultiplier = Color == "White" ? -1 : 1;
            FirstMove = true;
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }
        private int DirectionMultiplier { get; set; }
        public bool FirstMove { get; set; }
        public void Capture(Piece target)
        {
            throw new NotImplementedException();
        }

        public bool IsAvailableMove(Square target)
        {
            if (FirstMove)
            {
                if((target.Rank == Position.Rank + DirectionMultiplier
                || target.Rank == Position.Rank + 2 * DirectionMultiplier)
                && target.File == Position.File)
                {
                    return true;
                }
            }
            else if (target.Rank == Position.Rank + DirectionMultiplier 
                  && target.File == Position.File)
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
