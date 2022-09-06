using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CapitalUAirlines
{
    public class GroupModel : INotifyPropertyChanged
    {
        private List<PassengerModel> _allPassengers = new List<PassengerModel>();

        public List<PassengerModel> allPassengers
        {
            get { return _allPassengers; }
            set
            {
                _allPassengers = value;
                OnPropertyChanged("allPassengers");
            }
        }


        public String passengerNames
        {

            get
            {
                return String.Join(", ", allPassengers.Select(s => $"{s.passengerName} - {s.seatAssigned}" ));
            }
        }

        private int _groupNumber;

        public int groupNumber
        {
            get { return _groupNumber; }
            set
            {
                _groupNumber = value;
                OnPropertyChanged("groupNumber");
            }
        }

        private String _groupCategory;

        public String groupCategory
        {
            get { return _groupCategory; }
            set
            {
                _groupCategory = value;
                OnPropertyChanged("groupCategory");
            }
        }

        private int _groupSatisfactionScore;

        public int groupSatisfactionScore
        {
            get
            {
                return _groupSatisfactionScore;
            }
            set
            {
                _groupSatisfactionScore = value;
                OnPropertyChanged("groupSatisfactionScore");
            }
        }

        public void AddPassenger(PassengerModel p)
        {
            allPassengers.Add(p);
        }

        #region OnPropertyChangedImplementation

        public event PropertyChangedEventHandler PropertyChanged;

        void OnPropertyChanged(string propName)
        {
            if (this.PropertyChanged != null)
                this.PropertyChanged(
                    this, new PropertyChangedEventArgs(propName));
        }
        #endregion
    }
}
