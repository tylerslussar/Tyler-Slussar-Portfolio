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
    /// Interaction logic for ManagerLoginWindow.xaml
    /// </summary>
    public partial class ManagerLoginWindow : Window
    {
        MainWindow main;
        ManagerAccessWindow mw;
        public ManagerLoginWindow()
        {
            InitializeComponent();
            main = new MainWindow();
            mw = new ManagerAccessWindow();
            managName.Focus();
        }

        List<string> managers = new List<string>(new string[] { "Javier", "Tyler", "Dr. Feng" });
        bool didEnterPwd = false;
        String password = "admin";
        private void ManagEnter_Click(object sender, RoutedEventArgs e)
        {
            if (managName.Text == "")
            {
                MessageBox.Show("Pleaser enter your username.");
                managName.Focus();
                return;
            }
            else if (didEnterPwd == false)
            {
                MessageBox.Show("Please enter your password.");
                return;
            }
            else if (managName.Text != "" && didEnterPwd == true)
            {
                foreach (string n in managers)
                {
                    if (n == managName.Text && managPw.Password == password)
                    {
                        mw.Show();
                        this.Close();
                    }
                    else if (n == managName.Text && managPw.Password != password)
                    {
                        MessageBox.Show("Password is incorrect. Please try again");
                        managPw.Clear();
                        managPw.Focus();
                        return;
                    }
                }
            }
        }

        private void ManagCancel_Click(object sender, RoutedEventArgs e)
        {
            main.Show();
            this.Close();
        }

        private void ManagPw_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (String.IsNullOrWhiteSpace(managPw.Password))
            {
                didEnterPwd = false;
            }
            else
                didEnterPwd = true;
        }
    }
}
