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
    /// Interaction logic for ManagerAccessWindow.xaml
    /// </summary>
    public partial class ManagerAccessWindow : Window
    {
        MainWindow main;
        SeatSelectionWindow ss;
        ManagerReportWindow mg;

        public ManagerAccessWindow()
        {
            InitializeComponent();
            main = new MainWindow();
            ss = new SeatSelectionWindow();
            flightNumber.Focus();
        }

        private void LogOut_Click(object sender, RoutedEventArgs e)
        {
            main.Show();
            this.Close();
        }

        private void SeatPlan_Click(object sender, RoutedEventArgs e)
        {
            var dc = MainViewModel.GetFlight(flightNumber.Text, false);
            ss.DataContext = dc;
            ss.ShowDialog();
            this.Close();
        }

        private void GenReport_Click(object sender, RoutedEventArgs e)
        {
            FlightModel info = null;
            try
            {
                info = MainViewModel.GetFlight(flightNumber.Text, false);
            }
            catch (Exception)
            {
                if (info == null)
                {
                    MessageBox.Show("Flight entered does not exist.");
                    flightNumber.Clear();
                    flightNumber.Focus();
                    return;
                }
            }
            mg = new ManagerReportWindow();
           
            int groups = info.passengers.Count();
            switch (groups)
            {
                case int n when groups < 10:
                    MessageBox.Show("Not enough groups to run report.");
                    break;
                case 10:
                    this.Close();
                    mg.DataContext = info.passengers;
                    mg.Show();
                    break;
                default:
                    mg.DataContext = this.GetRandomGroups(info.passengers);
                    this.Close();
                    mg.Show();
                    break;
            }
        }


        public  List<GroupModel> GetRandomGroups<GroupModel>(IEnumerable<GroupModel> list, int elementsCount = 10)
        {
            return list.OrderBy(arg => Guid.NewGuid()).Take(elementsCount).ToList();
        }
    }
}
