namespace chess
{
    class Knight : Piece
    {
        public Knight(Square position, string color)
        {
            Position = position;
            Color = color;
            Content = Color == "White" ? "\u2658" : "\u265E";
        }
        public Square Position { get; set; }
        public string Content { get; set; }
        public string Color { get; set; }
        
        public bool IsAvailableMove(Square target)
        {
            if ((target.Rank == Position.Rank + 2
                || target.Rank == Position.Rank - 2)
            && (target.File == Position.File + 1
                || target.File == Position.File - 1)
            || (target.Rank == Position.Rank + 1
                || target.Rank == Position.Rank - 1)
            && (target.File == Position.File + 2
                || target.File == Position.File - 2))
            {
                return true;
            }
            else return false;
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
