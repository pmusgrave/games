using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        public Player[] Players { get; set; }
        public Player CurrentPlayer { get; set; }
        public string State { get; set; }
        public Player Winner { get; set; }
    }
}
