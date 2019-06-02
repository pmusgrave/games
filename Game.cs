namespace chess
{
    public class Game
    {
        public Game()
        {
            Player Player1 = new Player("White");
            Player Player2 = new Player("Black");
            Players = new Player[]
            {
                Player1,
                Player2
            };
            CurrentPlayer = Player1;
            State = "In Progress";
        }
        public Board GameBoard { get; set; }
        public Player[] Players { get; set; }
        public Player CurrentPlayer { get; set; }
        public string State { get; set; }
        public Player Winner { get; set; }
    }
}
