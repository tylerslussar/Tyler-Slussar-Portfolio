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
using System.Windows.Shapes;

namespace CapitalUAirlines
{
    /// <summary>
    /// Interaction logic for PassengerLoginWindow.xaml
    /// </summary>
    public partial class PassengerLoginWindow : Window
    {
        MainWindow main = new MainWindow();
        SeatSelectionWindow sw = new SeatSelectionWindow();
        public PassengerLoginWindow()
        {
            InitializeComponent();
        }
        int flightNum = 123;
        private void PassEnter_Click(object sender, RoutedEventArgs e)
        {
            if (passName.Text != "" && passFlight.Text == flightNum.ToString())
            {
                sw.Show();
                this.Close();
            }
        }

        private void PassCancel_Click(object sender, RoutedEventArgs e)
        {
            main.Show();
            this.Close();
        }
    }
}
