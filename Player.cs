namespace chess
{
    public class Player
    {
        public Player(string color)
        {
            Color = color;
            ActivePieces = new Piece[16] 
            {
                new King(new Square(0,'e')),
                new Queen(new Square(0,'d')),
                new Rook(new Square(0,'a')),
                new Rook(new Square(0,'h')),
                new Bishop(new Square(0,'c')),
                new Bishop(new Square(0,'f')),
                new Knight(new Square(0,'b')),
                new Knight(new Square(0,'g')),
                new Pawn(new Square(1,'a')),
                new Pawn(new Square(1,'b')),
                new Pawn(new Square(1,'c')),
                new Pawn(new Square(1,'d')),
                new Pawn(new Square(1,'e')),
                new Pawn(new Square(1,'f')),
                new Pawn(new Square(1,'g')),
                new Pawn(new Square(1,'h')),
            };
            CapturedPieces = new Piece[16];
        }
        public string Color { get; set; }
        public Piece[] ActivePieces { get; set; }
        public Piece[] CapturedPieces { get; set; }
    }
}
