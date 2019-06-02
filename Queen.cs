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
        public void Capture(Piece target)
        {
            throw new NotImplementedException();
        }

        public void Move()
        {
            throw new NotImplementedException();
        }

        public void Remove()
        {
            throw new NotImplementedException();
        }
    }
}
