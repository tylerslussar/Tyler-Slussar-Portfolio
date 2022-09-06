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
    /// Interaction logic for PassengerWindow.xaml
    /// </summary>
    public partial class PassengerWindow : Window
    {
        MainWindow main;
        SeatSelectionWindow sw;
        EnterPassengerDialog ep;

        public PassengerWindow()
        {
            InitializeComponent();
            main = new MainWindow();
            sw = new SeatSelectionWindow();
            ep = new EnterPassengerDialog();
            passName.Focus();

        }
        String flightNum = "";
        private void Business_Click(object sender, RoutedEventArgs e)
        {
            if (passName.Text == "")
            {
                MessageBox.Show("Please enter your name.");
                return;
            }
            else if (passFlight.Text == "")
            {
                MessageBox.Show("Please enter flight number");
                return;
            }
            flightNum = passFlight.Text;
            var dc = MainViewModel.GetFlight(flightNum);
            PassengerModel passenger = new PassengerModel();
            GroupModel group = new GroupModel();
            passenger.passengerName = passName.Text;
            group.groupCategory = "Business";
            group.AddPassenger(passenger);
            //group.groupNumber = dc.GetNextGroupNumber();

            this.Close();

            MainViewModel.AssignSeats(dc, group, group.groupCategory);
            group.groupNumber = dc.GetNextGroupNumber();
            sw = new SeatSelectionWindow(group);
            sw.DataContext = dc;
            sw.ShowDialog();
            MainViewModel.SaveToFile(dc);
        }

        private void Tourist_Click(object sender, RoutedEventArgs e)
        {
            if (passName.Text == "")
            {
                MessageBox.Show("Please enter your name.");
                return;
            }
            else if (passFlight.Text == "")
            {
                MessageBox.Show("Please enter flight number");
                return;
            }
            flightNum = passFlight.Text;
            var dc = MainViewModel.GetFlight(flightNum);
            PassengerModel passenger = new PassengerModel();
            GroupModel group = new GroupModel();
            passenger.passengerName = passName.Text;
            group.groupCategory = "Tourist";
            group.AddPassenger(passenger);
            group.groupNumber = dc.GetNextGroupNumber();
            ep = new EnterPassengerDialog(group);
            ep.ShowDialog();

            this.Close();

            MainViewModel.AssignSeats(dc, group, group.groupCategory);
            sw = new SeatSelectionWindow(group);
            sw.DataContext = dc;
            sw.ShowDialog();
            MainViewModel.SaveToFile(dc);
        }

        private void Family_Click(object sender, RoutedEventArgs e)
        {
            if (passName.Text == "")
            {
                MessageBox.Show("Please enter your name.");
                return;
            }
            else if (passFlight.Text == "")
            {
                MessageBox.Show("Please enter flight number");
                return;
            }
            flightNum = passFlight.Text;
            var dc = MainViewModel.GetFlight(flightNum);
            PassengerModel passenger = new PassengerModel();
            GroupModel group = new GroupModel();
            passenger.passengerName = passName.Text;
            group.groupCategory = "Family";
            group.AddPassenger(passenger);
            group.groupNumber = dc.GetNextGroupNumber();

            ep = new EnterPassengerDialog(group);
            ep.ShowDialog();
            ep.add.IsEnabled = true;

            this.Close();

            MainViewModel.AssignSeats(dc, group, group.groupCategory);
            sw = new SeatSelectionWindow(group);
            sw.DataContext = dc;
            sw.ShowDialog();
            MainViewModel.SaveToFile(dc);
        }

        private void PassCancel_Click(object sender, RoutedEventArgs e)
        {
            main.Show();
            this.Close();
        }
    }
}
