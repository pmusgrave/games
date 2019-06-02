namespace chess
{
    public class Square
    {
        public Square(int rank, char file)
        {
            Rank = rank;
            File = file;
        }
        public int Rank { get; set; }
        public char File { get; set; }
    }
}