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
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }
        public bool FirstMove { get; set; }
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
