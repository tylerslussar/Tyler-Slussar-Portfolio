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
    /// Interaction logic for ManagerReportWindow.xaml
    /// </summary>
    public partial class ManagerReportWindow : Window
    {
        MainWindow main;
        public ManagerReportWindow()
        {
            InitializeComponent();
        }
        public ManagerReportWindow(String flightNum)
        {
            InitializeComponent();
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            main = new MainWindow();
            this.Close();
            main.Show();
        }
    }
}
