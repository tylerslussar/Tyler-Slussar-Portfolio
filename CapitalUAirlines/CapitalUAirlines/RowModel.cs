using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CapitalUAirlines
{
    public class RowModel : INotifyPropertyChanged
    {
        private List<SeatModel> _seats = new List<SeatModel>();

        public List<SeatModel> seats
        {
            get { return _seats; }
            set
            {
                _seats = value;
                OnPropertyChanged("seats");
            }
        }

        private int _rowNumber;

        public int rowNumber
        {
            get { return _rowNumber; }
            set
            {
                _rowNumber = value;
                OnPropertyChanged("rowNumber");
            }
        }
        private String _fareCategory;

        public String fareCategory
        {
            get
            {
                if (rowNumber == 1 || rowNumber == 2)
                {
                    fareCategory = "Business";
                }
                return _fareCategory;
            }
            set
            {
                _fareCategory = value;
                OnPropertyChanged("fareCategory");
            }
        }

        private bool _isFull = false;

        public bool isFull
        {
            get { return _isFull; }
            set
            {
                _isFull = value;
                OnPropertyChanged("isFull");
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
