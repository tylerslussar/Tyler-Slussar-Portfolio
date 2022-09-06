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
    /// Interaction logic for BusinessSeatPreferenceWindow.xaml
    /// </summary>
    public partial class BusinessSeatPreferenceWindow : Window
    {
        PassengerWindow pw;
        SeatSelectionWindow sw;
        GroupModel group;
        public BusinessSeatPreferenceWindow()
        {
            InitializeComponent();
        }
        public BusinessSeatPreferenceWindow(GroupModel g)
        {
            group = g;
            InitializeComponent();
        }
        String seatPreference = "";
        private void Window_Checked(object sender, RoutedEventArgs e)
        {

        }

        private void Middle_Checked(object sender, RoutedEventArgs e)
        {

        }

        private void Aisle_Checked(object sender, RoutedEventArgs e)
        {

        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            pw = new PassengerWindow();
            pw.Show();
            this.Close();
        }

        private void Done_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
