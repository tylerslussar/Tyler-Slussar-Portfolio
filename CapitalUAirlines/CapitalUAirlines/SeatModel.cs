using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace CapitalUAirlines
{
     public class SeatModel : INotifyPropertyChanged
     {
        private String _seatColumn;

        public String seatColumn
        {
            get { return _seatColumn; }
            set
            {
                _seatColumn = value;
                OnPropertyChanged("seatColumn");
            }
        }

        private PassengerModel _assignedPassenger;

        public PassengerModel assignedPassenger
        {
            get { return _assignedPassenger; }
            set
            {
                _assignedPassenger = value;
                OnPropertyChanged("assignedPassenger");
                OnPropertyChanged("isTaken");
            }
        }

        private RowModel _assignedRow;

        [XmlIgnore]
        public RowModel assignedRow
        {
            get { return _assignedRow; }
            set
            {
                _assignedRow = value;
                OnPropertyChanged("assignedRow");
            }
        }
        private String _seatType;

        public String seatType
        {
            get
            {
                return _seatType;
            }
            set
            {
                _seatType = value;
                OnPropertyChanged("seatType");
            }
        }

        private bool _isTaken;

        public bool isTaken
        {
            get
            {
                if (assignedPassenger != null)
                {
                   return true;
                }
                return false;
            }
            set
            {
                _isTaken = value;
                
            }
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
