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

namespace CapitalUAirlines
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        PassengerWindow pw;
        ManagerLoginWindow mw;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Passenger_Click(object sender, RoutedEventArgs e)
        {
            pw = new PassengerWindow();
            pw.Show();
            this.Close();
        }

        private void Manager_Click(object sender, RoutedEventArgs e)
        {
            mw = new ManagerLoginWindow();
            mw.Show();
            this.Close();
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }
    }
}
