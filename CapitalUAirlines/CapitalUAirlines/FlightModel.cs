using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CapitalUAirlines
{
    [Serializable]
    public class FlightModel : INotifyPropertyChanged
    {

        public FlightModel()
        {
            _passengers = new List<GroupModel>();
            _flightRows = new List<RowModel>();

        }

        private List<GroupModel> _passengers;

        public List<GroupModel> passengers
        {
            get { return _passengers; }
            set
            {
                _passengers = value;
                OnPropertyChanged("passengers");
            }
        }

        public List<PassengerModel> peoples
        {
            get
            {
                return flightRows.SelectMany(s => s.seats).Where(q => q.assignedPassenger != null).Select(t => t.assignedPassenger).ToList();
            }
        }

        private List<RowModel> _flightRows;

        public List<RowModel> flightRows
        {
            get { return _flightRows; }
            set
            {
                _flightRows = value;
                OnPropertyChanged("flightRows");
            }
        }

        private int lastGroupNumber;
        public int GetNextGroupNumber()
        {
            LastGroupNumber += 1;
            return LastGroupNumber;
        }

        private String _flightNumber;

        public String flightNumber
        {
            get { return _flightNumber; }
            set
            {
                _flightNumber = value;
                OnPropertyChanged("flightNumber");
            }
        }

        private DateTime _flightDate;

        public DateTime flightDate
        {
            get { return _flightDate; }
            set
            {
                _flightDate = value;
                OnPropertyChanged("flightDate");
            }
        }

        public int LastGroupNumber { get => lastGroupNumber; set => lastGroupNumber = value; }

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
