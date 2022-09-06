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
    /// Interaction logic for EnterPassengerDialog.xaml
    /// </summary>
    public partial class EnterPassengerDialog : Window
    {
        private GroupModel group;
        private SeatSelectionWindow sw;
        public EnterPassengerDialog()
        {
            InitializeComponent();
            name.Focus();
        }

        public EnterPassengerDialog(GroupModel g)
        {
            group = g;
            InitializeComponent();
            name.Focus();
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            if (group.groupCategory == "Tourist" || group.allPassengers.Count() == 4)
                add.IsEnabled = false;

            PassengerModel passenger = new PassengerModel();
            passenger.passengerName = name.Text;
            group.AddPassenger(passenger);
            name.Clear();
            name.Focus();
            
        }

        private void Done_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
