using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CapitalUAirlines
{
    public class PassengerModel : INotifyPropertyChanged
    {
        private String _passengerName = "";

        public String passengerName
        {
            get { return _passengerName; }
            set
            {
                _passengerName = value;
                OnPropertyChanged("passengerName");
            }
        }

        private String _seatAssigned = "";

        public String seatAssigned
        {
            get { return _seatAssigned; }
            set
            {
                _seatAssigned = value;
                OnPropertyChanged("seatAssigned");
            }
        }

        private int _reseatCount = 0;

        public int reseatCount
        {
            get { return _reseatCount; }
            set
            {
                if (value == 3)
                {
                    allowReseat = false;
                }
                _reseatCount = value;
                OnPropertyChanged("reseatCount");
            }
        }

        private bool _allowReseat = true;

        public bool allowReseat
        {
            get { return _allowReseat; }
            set
            {
                _allowReseat = value;
                OnPropertyChanged("allowReseat");
            }
        }

        private SeatModel assignedSeat;

        public void AssignSeat(SeatModel s)
        {
            if(assignedSeat != null)
            {
                assignedSeat.assignedPassenger = null;
            }

            if (s == null)
                return;

            assignedSeat = s;
            s.assignedPassenger = this;

            if (seatAssigned != "")
            {
                reseatCount++;
            }

             seatAssigned = $"{s.assignedRow.rowNumber}{s.seatColumn}";

        }

        private int _satisfactionScore;

        public int satisfactionScore
        {
            get { return _satisfactionScore; }
            set
            {
                _satisfactionScore = value;
                OnPropertyChanged("satisfactionScore");
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
