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
    /// Interaction logic for SeatSelectionWindow.xaml
    /// </summary>
    public partial class SeatSelectionWindow : Window
    {
        MainWindow main;
        private GroupModel group;

        public SeatSelectionWindow()
        {
            InitializeComponent();
        }


        public SeatSelectionWindow(GroupModel g)
        {
            group = g;
            InitializeComponent();
            groupList.DataContext = group;
        }


        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            main = new MainWindow();
            var flight = (FlightModel)this.DataContext;
            flight.passengers.Remove(group);

            foreach(var passenger in group.allPassengers)
            {
                passenger.AssignSeat(null);
            }

            main.Show();
            this.Close();
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            main = new MainWindow();
            main.Show();
            this.Close();
        }

        private void Reseat_Click(object sender, RoutedEventArgs e)
        {
            var flight = (FlightModel)this.DataContext;
            MainViewModel.AssignSeats(flight, group, group.groupCategory);
        }

        private void Print_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
