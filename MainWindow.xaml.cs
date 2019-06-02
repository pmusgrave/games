using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace chess
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Button new_button = new Button();
                    new_button.Width = 100;
                    new_button.Height = 100;
                    new_button.FontSize = 60;

                    Grid.SetRow(new_button, i);
                    Grid.SetColumn(new_button, j);
                    ChessBoardGrid.Children.Add(new_button);
                }
            }

            Game game = new Game();
            Board board = new Board(this, game);
            /*while(game.State == "In Progress")
            {

            }
            if (game.Winner != null)
            {
                MessageBox.Show("Player {0} wins!", game.Winner.Color);
            }
            else
            {
                MessageBox.Show("Stalemate!");
            }*/
        }
    }
}
