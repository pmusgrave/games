using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    class Pawn : Piece
    {
        public Pawn(Square position)
        {
            Position = position;
            FirstMove = true;
        }
        public Square Position { get; set; }
        bool FirstMove { get; set; }
        public void Capture(Piece target)
        {
            throw new NotImplementedException();
        }

        public void Move()
        {
            if (FirstMove)
            {
                FirstMove = false;
            }
            else
            {
                
            }
        }

        public void Remove()
        {
            throw new NotImplementedException();
        }
    }
}
