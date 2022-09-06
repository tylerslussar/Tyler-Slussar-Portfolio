using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace CapitalUAirlines
{
    public class MainViewModel
    {
        public MainViewModel()
        {

        }

        public static void AssignSeats(FlightModel flight, GroupModel group, String category)
        {


            if (category == "Business")
            {
                BusinessSeatAssignment(flight, group);
            }
            if (category == "Tourist")
            {
                TouristSeatAssignment(flight, group);
            }
            if (category == "Family")
            {
                FamilySeatAssignment(flight, group);
            }
            if (!flight.passengers.Contains(group))
            {
                flight.passengers.Add(group);
            }
        }

        public static void BusinessSeatAssignment(FlightModel flight, GroupModel group)
        {
            BusinessSeatPreferenceWindow sp = new BusinessSeatPreferenceWindow();
            sp.ShowDialog();
            String seatPref = "";
            if (sp.window.IsChecked == true)
            {
                seatPref = "Window";
            }
            else if (sp.middle.IsChecked == true)
            {
                seatPref = "Middle";
            }
            else
            {
                seatPref = "Aisle";
            }
            switch (seatPref)
            {
                case "Window":
                    for (int i = 0; i < 2; i++)
                    {
                        RowModel row = flight.flightRows[i];
                        if (row.seats[0].isTaken == false)
                        {
                            group.allPassengers[0].AssignSeat(row.seats[0]);
                            group.groupSatisfactionScore += 5;
                            break;
                        }
                        if (row.seats[5].isTaken == false)
                        {
                            group.allPassengers[0].AssignSeat(row.seats[5]);
                            group.groupSatisfactionScore += 5;
                            break;
                        }
                    }
                    if (!group.allPassengers[0].seatAssigned.Equals(""))
                    {
                        break;
                    }
                    for (int i = 0; i < 2; i++)
                    {
                        RowModel row = flight.flightRows[i];
                        foreach (var seat in row.seats)
                        {
                            if (seat.isTaken == false)
                            {
                                group.allPassengers[0].AssignSeat(seat);
                                break;
                            }
                        }
                        break;
                    }                   
                    break;
                case "Middle":
                    for (int i = 0; i < 2; i++)
                    {
                        RowModel row = flight.flightRows[i];
                        if (row.seats[1].isTaken == false)
                        {
                            group.allPassengers[0].AssignSeat(row.seats[1]);
                            group.groupSatisfactionScore += 5;
                            break;
                        }
                        if (row.seats[4].isTaken == false)
                        {
                            group.allPassengers[0].AssignSeat(row.seats[4]);
                            group.groupSatisfactionScore += 5;
                            break;
                        }
                    }
                    if (!group.allPassengers[0].seatAssigned.Equals(""))
                    {
                        break;
                    }
                    for (int i = 0; i < 2; i++)
                    {
                        RowModel row = flight.flightRows[i];
                        foreach (var seat in row.seats)
                        {
                            if (seat.isTaken == false)
                            {
                                group.allPassengers[0].AssignSeat(seat);
                                break;
                            }
                        }
                        break;
                    }
                    break;
                case "Aisle":
                    for (int i = 0; i < 2; i++)
                    {
                        RowModel row = flight.flightRows[i];
                        if (row.seats[2].isTaken == false)
                        {
                            group.allPassengers[0].AssignSeat(row.seats[2]);
                            group.groupSatisfactionScore += 5;
                            break;
                        }
                        if (row.seats[3].isTaken == false)
                        {
                            group.allPassengers[0].AssignSeat(row.seats[3]);
                            group.groupSatisfactionScore += 5;
                            break;
                        }
                    }
                    if (!group.allPassengers[0].seatAssigned.Equals(""))
                    {
                        break;
                    }
                    for (int i = 0; i < 2; i++)
                    {
                        RowModel row = flight.flightRows[i];
                        foreach (var seat in row.seats)
                        {
                            if (seat.isTaken == false)
                            {
                                group.allPassengers[0].AssignSeat(seat);
                                break;
                            }
                        }
                        break;
                    }
                    break;
                default:
                    break;
            }
        }
        public static void TouristSeatAssignment(FlightModel flight, GroupModel group)
        {

            foreach (var row in flight.flightRows)
            {
                if (row.rowNumber == 1 || row.rowNumber == 2)
                {
                    continue;
                }

                if (row.seats[0].isTaken == false && row.seats[1].isTaken == false)
                {
                    group.allPassengers[0].AssignSeat(row.seats[0]);
                    group.allPassengers[1].AssignSeat(row.seats[1]);
                    group.groupSatisfactionScore += 15;
                    break;
                }
                else if (row.seats[4].isTaken == false && row.seats[5].isTaken == false)
                {
                    group.allPassengers[0].AssignSeat(row.seats[4]);
                    group.allPassengers[1].AssignSeat(row.seats[5]);
                    group.groupSatisfactionScore += 15;
                    break;
                }
            }
            for (int i = 2; i < 20; i++)
            {
                RowModel row = flight.flightRows[i];
                foreach (var seat in row.seats)
                {
                    if (seat.isTaken == false)
                    {
                        group.allPassengers[0].AssignSeat(seat);
                        break;
                    }
                }
               
                if (!group.allPassengers[0].seatAssigned.Equals(""))
                {
                    break;
                }
            }
            for (int i = 2; i < 20; i++)
            {
                RowModel row = flight.flightRows[i];
                foreach (var seat in row.seats)
                {
                    if (seat.isTaken == false)
                    {
                        group.allPassengers[1].AssignSeat(seat);
                        break;
                    }
                }
                if (!group.allPassengers[1].seatAssigned.Equals(""))
                {
                    break;
                }
            }
            group.groupSatisfactionScore -= 10;
        }
        public static void FamilySeatAssignment(FlightModel flight, GroupModel group)
        {
            int passengerNumber = group.allPassengers.Count();
            switch (passengerNumber)
            {
                case 3:
                    foreach (var row in flight.flightRows)
                    {
                        if (row.rowNumber == 1 || row.rowNumber == 2)
                        {
                            continue;
                        }

                        if (row.seats[2].isTaken == false && row.seats[3].isTaken == false && row.seats[4].isTaken == false)
                        {
                            for (int i = 0; i < group.allPassengers.Count(); i++)
                            {
                                group.allPassengers[i].AssignSeat(row.seats[i + 2]);
                            }
                            group.groupSatisfactionScore += 20;
                            break;
                        }
                        else if (row.seats[1].isTaken == false && row.seats[2].isTaken == false && row.seats[3].isTaken == false)
                        {
                            for (int i = 0; i < group.allPassengers.Count(); i++)
                            {
                                group.allPassengers[i].AssignSeat(row.seats[i + 1]);
                            }
                            group.groupSatisfactionScore += 20;
                            break;
                        }
                    }
                    break;
                case 4:
                    foreach (var row in flight.flightRows)
                    {
                        if (row.rowNumber == 1 || row.rowNumber == 2)
                        {
                            continue;
                        }

                        if (row.seats[1].isTaken == false && row.seats[2].isTaken == false && row.seats[3].isTaken == false && row.seats[4].isTaken == false)
                        {
                            for (int i = 0; i < group.allPassengers.Count(); i++)
                            {
                                group.allPassengers[i].AssignSeat(row.seats[i + 1]);
                            }
                            group.groupSatisfactionScore += 20;
                            break;
                        }
                        else if (row.seats[0].isTaken == false && row.seats[1].isTaken == false && row.seats[2].isTaken == false && row.seats[3].isTaken == false)
                        {
                            for (int i = 0; i < group.allPassengers.Count(); i++)
                            {
                                group.allPassengers[i].AssignSeat(row.seats[i]);
                            }
                            group.groupSatisfactionScore += 20;
                            break;
                        }
                        else if (row.seats[2].isTaken == false && row.seats[3].isTaken == false && row.seats[4].isTaken == false && row.seats[5].isTaken == false)
                        {
                            for (int i = 0; i < group.allPassengers.Count(); i++)
                            {
                                group.allPassengers[i].AssignSeat(row.seats[i + 2]);
                            }
                            group.groupSatisfactionScore += 20;
                            break;
                        }
                    }
                    break;
                default:
                    foreach (var row in flight.flightRows)
                    {
                        if (row.rowNumber == 1 || row.rowNumber == 2)
                        {
                            continue;
                        }

                        if (row.seats[0].isTaken == false && row.seats[1].isTaken == false && row.seats[2].isTaken == false && row.seats[3].isTaken == false && row.seats[4].isTaken == false)
                        {
                            for (int i = 0; i < group.allPassengers.Count(); i++)
                            {
                                group.allPassengers[i].AssignSeat(row.seats[i]);
                            }
                            group.groupSatisfactionScore += 20;
                            break;
                        }
                        else if (row.seats[1].isTaken == false && row.seats[2].isTaken == false && row.seats[3].isTaken == false && row.seats[4].isTaken == false && row.seats[5].isTaken == false)
                        {
                            for (int i = 0; i < group.allPassengers.Count(); i++)
                            {
                                group.allPassengers[i].AssignSeat(row.seats[i + 1]);
                            }
                            group.groupSatisfactionScore += 20;
                            break;
                        }
                    }
                    break;
            }           
        }
        public static FlightModel GetFlight(String flightNum, bool allowFlightCreation = true)
        {
            try
            {
                return LoadFromSerialization(flightNum);
            } catch (Exception e)
            {
                if (allowFlightCreation)
                {
                    return GenerateNewFlight(flightNum);
                } else
                {
                    return null;
                }

            }
        }

        private static FlightModel GenerateNewFlight(String flightNum)
        {
            FlightModel newFlight = new FlightModel();
            newFlight.flightNumber = flightNum;

            List<GroupModel> passengers = new List<GroupModel>();

            for (int i = 1; i <= 20; i++)
            {
                RowModel currentRow = new RowModel();
                currentRow.rowNumber = i;
                switch (i)
                {
                    case int n when (n <= 2):
                        currentRow.fareCategory = "Business";
                        break;
                    default:
                        currentRow.fareCategory = "Economy";
                        break;
                }
                currentRow.seats.Add(new SeatModel() { seatColumn = "A", assignedRow = currentRow, seatType = "Window" });
                currentRow.seats.Add(new SeatModel() { seatColumn = "B", assignedRow = currentRow, seatType = "Middle" });
                currentRow.seats.Add(new SeatModel() { seatColumn = "C", assignedRow = currentRow, seatType = "Aisle" });
                currentRow.seats.Add(new SeatModel() { seatColumn = "D", assignedRow = currentRow, seatType = "Aisle" });
                currentRow.seats.Add(new SeatModel() { seatColumn = "E", assignedRow = currentRow, seatType = "Middle" });
                currentRow.seats.Add(new SeatModel() { seatColumn = "F", assignedRow = currentRow, seatType = "Window" });

                newFlight.flightRows.Add(currentRow);
            }
            return newFlight;
        }

        private static FlightModel LoadFromSerialization(String flightNumber)
        {
            System.Xml.Serialization.XmlSerializer x = new System.Xml.Serialization.XmlSerializer(typeof(FlightModel));
            FileStream f = new FileStream($"{ Path.GetTempPath()}/{ flightNumber }.xml", FileMode.Open);

           
            FlightModel flight = x.Deserialize(f) as FlightModel;
            f.Close();

            foreach (var row in flight.flightRows)
                foreach (var seat in row.seats)
                    seat.assignedRow = row;

            return flight;
        }



        public static void SaveToFile(FlightModel flight)
        {
            try
            {
                System.Xml.Serialization.XmlSerializer x = new System.Xml.Serialization.XmlSerializer(typeof(FlightModel));
                FileStream f = new FileStream($"{ Path.GetTempPath()}/{ flight.flightNumber }.xml", FileMode.Create);
                x.Serialize(f, flight);
                f.Close();
            }
            catch (Exception)
            {

                throw;
            }
        }
    }
}
