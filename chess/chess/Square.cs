namespace chess
{
    public class Square
    {
        public Square(int rank, int file)
        {
            Rank = rank;
            File = file;
        }
        public int Rank { get; set; }
        public int File { get; set; }
    }
}