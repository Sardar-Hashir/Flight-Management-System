#include <iostream>
#include <regex>
#include <fstream>
#include <string>
using namespace std;

struct passengerNode
{
    string passengerID;
    string Firstname;
    string Lastname;
    string email;
    string phone_number;
    string passportId;
    string password;
    passengerNode *next;
};

struct FlightNode
{
    string flightID;
    string departure;
    string arrival;
    string departureTime;
    int availableSeats;
    int priceperseat;
    FlightNode *next;
};

struct bookingNode
{

    string passengerID;
    string flightID;
    int seatsBooked;
    int totalPrice;
    bookingNode *next;
};

void displayFlights(FlightNode *head)
{
    FlightNode *temp = head;
    if (head == 0)
    {
        cout << endl;
        cout << "No Flight available" << endl;
    }
    while (temp != 0)
    {
        cout << "************************************" << endl;
        cout << "| Flight ID: " << temp->flightID << "                     |" << endl;
        cout << "| Departure: " << temp->departure << "                    |" << endl;
        cout << "| Arrival: " << temp->arrival << "                        |" << endl;
        cout << "| Departure Time: " << temp->departureTime << "  |" << endl;
        cout << "| Available Seats: " << temp->availableSeats << "|" << endl;
        cout << "| Price per Seat: " << temp->priceperseat << "|" << endl;
        cout << "************************************" << endl;

        temp = temp->next;
    }
}

void addPassenger(passengerNode *&head, string passengerID, string Firstname,
                  string Lastname, string email, string phone_number, string passportId, string password)
{

    passengerNode *newpassenger = new passengerNode;
    passengerNode *temp = head;
    while (temp != nullptr)
    {
        if (temp->passengerID == passengerID)
        {
            cout << "Error: A passenger with the same ID (" << passengerID << ") already exists. Cannot add duplicate flight." << endl;
            return; // Exit the function if duplicate is found
        }
        temp = temp->next;
    }
    newpassenger->passengerID = passengerID;
    newpassenger->Firstname = Firstname;
    newpassenger->Lastname = Lastname;
    newpassenger->email = email;
    newpassenger->phone_number = phone_number;
    newpassenger->passportId = passportId;
    newpassenger->password = password;
    newpassenger->next = head;
    head = newpassenger;
}

void displayPassengers(passengerNode *head)
{
    passengerNode *temp = head;
    if (head == 0)
    {
        cout << endl;
        cout << "No Passenger registerd" << endl;
    }
    while (temp != 0)
    {
        cout << "************************************" << endl;
        cout << "| Passenger ID: " << temp->passengerID << "          |" << endl;
        cout << "| First name: " << temp->Firstname << "         |" << endl;
        cout << "| Last name: " << temp->Lastname << "             |" << endl;
        cout << "| Email: " << temp->email << "  |" << endl;
        cout << "| phone number: " << temp->phone_number << "|" << endl;
        cout << "| Passport Id: " << temp->passportId << "|" << endl;

        cout << "************************************" << endl;

        temp = temp->next;
    }
}

void displayPassengerById(passengerNode *head, string passengerID)
{
    passengerNode *temp = head;
    bool found = false;

    while (temp != nullptr)
    {

        if (temp->passengerID == passengerID)
        {
            cout << "************************************" << endl;
            cout << "| Passenger ID: " << temp->passengerID << "          |" << endl;
            cout << "| First name: " << temp->Firstname << "         |" << endl;
            cout << "| Last name: " << temp->Lastname << "             |" << endl;
            cout << "| Email: " << temp->email << "  |" << endl;
            cout << "| Phone number: " << temp->phone_number << "|" << endl;
            cout << "| Passport Id: " << temp->passportId << "|" << endl;
            cout << "************************************" << endl;

            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Passenger with ID " << passengerID << " not found." << endl;
    }
}

void cancelBooking(bookingNode *&bookingHead, FlightNode *flightHead, string passengerID)
{
    if (bookingHead == 0)
    {
        cout << "No bookings available to cancel." << endl;
        return;
    }

    bookingNode *temp = bookingHead;
    bookingNode *prev = nullptr;

    while (temp != 0 && temp->passengerID != passengerID)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == 0)
    {
        cout << "No booking found for this passenger." << endl;
        return;
    }

    if (prev == 0)
    {

        bookingHead = temp->next;
    }
    else
    {

        prev->next = temp->next;
    }

    FlightNode *flight = flightHead;
    while (flight != 0 && flight->flightID != temp->flightID)
    {
        flight = flight->next;
    }

    if (flight != 0)
    {
        flight->availableSeats += temp->seatsBooked;
        cout << "Booking canceled successfully! " << temp->seatsBooked << " seats have been restored." << endl;
    }
    delete temp;
}
void partialCancelBooking(bookingNode *&bookingHead, FlightNode *flightHead, const string &passengerID)
{
    if (!bookingHead)
    {
        cout << "No bookings available to cancel." << endl;
        return;
    }

    bookingNode *temp = bookingHead;
    bookingNode *prev = nullptr;

    while (temp && temp->passengerID != passengerID)
    {
        prev = temp;
        temp = temp->next;
    }

    if (!temp)
    {
        cout << "No booking found for this passenger." << endl;
        return;
    }

    cout << "You have booked " << temp->seatsBooked << " seats on flight " << temp->flightID << "." << endl;
    cout << "How many seats do you want to cancel? ";
    int cancelSeats;
    cin >> cancelSeats;

    if (cancelSeats <= 0 || cancelSeats > temp->seatsBooked)
    {
        cout << "Invalid number of seats to cancel." << endl;
        return;
    }

    FlightNode *flight = flightHead;
    while (flight && flight->flightID != temp->flightID)
    {
        flight = flight->next;
    }

    if (flight)
    {
        flight->availableSeats += cancelSeats;
    }

    temp->seatsBooked -= cancelSeats;
    temp->totalPrice = temp->seatsBooked * flight->priceperseat;

    if (temp->seatsBooked == 0)
    {
        if (prev)
            prev->next = temp->next;
        else
            bookingHead = temp->next;

        delete temp;
        cout << "All seats canceled and booking deleted." << endl;
    }
    else
    {
        cout << cancelSeats << " seats canceled successfully. Remaining seats: " << temp->seatsBooked << endl;
    }
}


void popLatestBooking(bookingNode *&bookingHead, FlightNode *flightHead)
{
    if (bookingHead == nullptr)
    {
        cout << "No bookings available to cancel." << endl;
        return;
    }
    bookingNode *latestBooking = bookingHead;
    FlightNode *flight = flightHead;
    while (flight != nullptr && flight->flightID != latestBooking->flightID)
    {
        flight = flight->next;
    }

    if (flight != nullptr)
    {

        flight->availableSeats += latestBooking->seatsBooked;
        cout << "Seats restored to the flight: " << flight->flightID << endl;
    }
    else
    {
        cout << "Flight not found. Could not restore seats." << endl;
    }
    bookingHead = bookingHead->next;
    cout << "Latest booking removed successfully!" << endl;
    cout << "Passenger ID: " << latestBooking->passengerID << endl;
    cout << "Flight ID: " << latestBooking->flightID << endl;
    cout << "Seats Booked: " << latestBooking->seatsBooked << endl;
    cout << "Total Price: " << latestBooking->totalPrice << endl;
    delete latestBooking;
}

void paymentMethod(bookingNode *&bookingHead, FlightNode *flightHead)
{
    string choice;
    cout << "Select Payment Method:" << endl;
    cout << "1. Card" << endl;
    cout << "2. Cash" << endl;
    cout << "3. Cancel Reservation" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == "1")
    {
        cout << "Payment completed using Card." << endl;
    }
    else if (choice == "2")
    {
        cout << "Payment completed using Cash." << endl;
    }
    else if (choice == "3")
    {
        popLatestBooking(bookingHead, flightHead);
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }
}

void bookSeat(passengerNode *passengerHead, FlightNode *flightHead, bookingNode *&bookingHead, string passengerID)
{
    string flightID;
    int seatsToBook;

    cout << "Enter the Flight ID to book: ";
    cin >> flightID;

    FlightNode *flight = flightHead;
    while (flight != nullptr && flight->flightID != flightID)
    {
        flight = flight->next;
    }

    if (flight == nullptr)
    {
        cout << "Flight ID not found. Booking failed." << endl;
        return;
    }

    cout << "Available Seats: " << flight->availableSeats << endl;
    cout << "Enter the number of seats to book: ";
    cin >> seatsToBook;

    if (seatsToBook > flight->availableSeats || seatsToBook <= 0)
    {
        cout << "Invalid number of seats. Booking failed." << endl;
        return;
    }

    flight->availableSeats -= seatsToBook;

    bookingNode *newBooking = new bookingNode;

    newBooking->passengerID = passengerID;
    newBooking->flightID = flightID;
    newBooking->seatsBooked = seatsToBook;
    newBooking->totalPrice = seatsToBook * flight->priceperseat;
    newBooking->next = nullptr;

    if (bookingHead == nullptr)
    {

        bookingHead = newBooking;
        bookingHead->next = nullptr;
    }
    else
    {

        newBooking->next = bookingHead;
        bookingHead = newBooking;
    }

    cout << "Booking successful! Total Price: " << newBooking->totalPrice << endl;

    paymentMethod(bookingHead, flightHead);
}

void passengerOptions(passengerNode *&head, FlightNode *&flighthead, string passengerId, bookingNode *&Bookinghead)
{
    while (true)
    {
        cout << "==========================================" << endl;
        cout << "          Passenger Options               " << endl;
        cout << "==========================================" << endl;
        cout << "| 1. View Available Flights              |" << endl;
        cout << "| 2. Book a Seat                         |" << endl;
        cout << "| 3. View My Details                     |" << endl;
        cout << "| 4. Cancel My Booking (Partial/Full)    |" << endl;
        cout << "| 5. Logout                              |" << endl;
        cout << "==========================================" << endl;
        cout << "| Enter your choice:                     |" << endl;
        cout << "| ";

        string choice;
        cin >> choice;

        if (choice == "1")
        {
            displayFlights(flighthead);
        }
        else if (choice == "2")
        {
            bookSeat(head, flighthead, Bookinghead, passengerId);
        }
        else if (choice == "3")
        {
            displayPassengerById(head, passengerId);
        }
        else if (choice == "4")
{
    string subChoice;
    cout << "1. Cancel Entire Booking\n";
    cout << "2. Cancel Part of Booking\n";
    cout << "Enter your choice: ";
    cin >> subChoice;

    if (subChoice == "1")
        cancelBooking(Bookinghead, flighthead, passengerId);
    else if (subChoice == "2")
        partialCancelBooking(Bookinghead, flighthead, passengerId);
    else
        cout << "Invalid choice.\n";
    }
        else if (choice == "5")
        {
            cout << "Logging out..." << endl;
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Findpassenger(passengerNode *&head, string passengerId, string password, FlightNode *&flighthead, bookingNode *&Bookinghead)
{

    if (head == 0)
    {
        cout << "Account not found\n";
        return;
    }
    passengerNode *current = head;

    while (current != 0)
    {
        if (current->passengerID == passengerId && current->password == password)
        {
            cout << "*****************************" << endl;
            cout << "|";
            cout << " Login successful!" << "        |" << endl;
            cout << "*****************************" << endl;
            passengerOptions(head, flighthead, passengerId, Bookinghead);
            return;
        }
        current = current->next;
    }

    cout << "Account not found or incorrect password.\n";
}

void login(passengerNode *&passengerhead, FlightNode *&flighthead, bookingNode *&Bookinghead)
{
    string passengerId;
    string password;
    cout << "*****************************" << endl;
    cout << "Enter Passenger Id: " << endl;
    cout << "*****************************" << endl;
    cout << "|";
    cin >> passengerId;

    cout << "*****************************" << endl;
    cout << "Enter Password: " << endl;
    cout << "*****************************" << endl;
    cout << "|";
    cin >> password;
    Findpassenger(passengerhead, passengerId, password, flighthead, Bookinghead);
}

void addFlight(FlightNode *&head, string flightID, string departure, string arrival, string departureTime, int availableSeats, int priceperseat)
{
    FlightNode *newFlight = new FlightNode;
    FlightNode *temp = head;
    while (temp != nullptr)
    {
        if (temp->flightID == flightID)
        {
            cout << "Error: A flight with the same ID (" << flightID << ") already exists. Cannot add duplicate flight." << endl;
            return;
        }
        temp = temp->next;
    }
    newFlight->flightID = flightID;
    newFlight->departure = departure;
    newFlight->departureTime = departureTime;
    newFlight->availableSeats = availableSeats;
    newFlight->priceperseat = priceperseat;
    newFlight->next = head;
    head = newFlight;
    cout << "Flight added successfully!" << endl;
}

void displayAllBookings(bookingNode *bookingHead, FlightNode *flightHead)
{
    if (bookingHead == 0)
    {
        cout << "No bookings available." << endl;
        return;
    }

    bookingNode *temp = bookingHead;
    while (temp != nullptr)
    {
        cout << "Passenger ID: " << temp->passengerID << endl;
        cout << "Flight ID: " << temp->flightID << endl;
        cout << "Seats Booked: " << temp->seatsBooked << endl;
        cout << "Total Price: " << temp->totalPrice << endl;
        cout << "-------------------------------" << endl;

        temp = temp->next;
    }

    return;
}

class Admin
{

private:
    string username;

private:
    string password;

public:
    Admin(FlightNode *&head, passengerNode *&passengerhead, bookingNode *&Bookinghead)
    {
    x:
        cout << "***********************" << endl;
        cout << "| Enter Username:    |" << endl;
        cout << "| ";
        cin >> username;
        cout << "|--------------------|" << endl;
        cout << "| Enter Password:    |" << endl;
        cout << "| ";
        cin >> password;
        cout << "|--------------------|" << endl;
        cout << "***********************" << endl;
        if (username != "mirza" || password != "mirza123")
        {
            cout << "Invalid Username and Password" << endl;
            goto x;
        }
        else
        {

            string choice;

            while (true)
            {

                cout << "****************************" << endl;
                cout << "|    Welcome, Hashir!     |" << endl;
                cout << "****************************" << endl;

                cout << "| Admin Portal:           |" << endl;
                cout << "|-------------------------|" << endl;
                cout << "| 1. Add Flight           |" << endl;
                cout << "| 2. View Reservations    |" << endl;
                cout << "| 3. View Flights         |" << endl;
                cout << "| 4. View Users           |" << endl;
                cout << "| 5. Exit                 |" << endl;
                cout << "|-------------------------|" << endl;
                cout << "| Enter your choice:      |" << endl;
                cout << "| ";
                cin >> choice;
                cout << "|-------------------------|" << endl;

                if (choice == "1")
                {
                    string flightID, departure, arrival, departureTime;
                    int availableSeats, priceperseat;

                    cout << "******************************" << endl;
                    cout << "|      Add Flight Details    |" << endl;
                    cout << "******************************" << endl;

                    do
                    {
                        cout << "| Enter Flight ID (Alphanumeric, Max 10 characters): | " << endl;
                        cout << "| ";
                        cin >> flightID;
                        if (!regex_match(flightID, regex("^[a-zA-Z0-9]{1,10}$")))
                        {
                            cout << "| Invalid Flight ID! Please try again.               |" << endl;
                        }
                    } while (!regex_match(flightID, regex("^[a-zA-Z0-9]{1,10}$")));

                    cout << "|----------------------------|" << endl;

                    do
                    {
                        cout << "| Enter Departure Location (Alphabetic only):        | " << endl;
                        cout << "| ";
                        cin >> departure;
                        if (!regex_match(departure, regex("^[a-zA-Z]+$")))
                        {
                            cout << "| Invalid Departure Location! Please try again.      |" << endl;
                        }
                    } while (!regex_match(departure, regex("^[a-zA-Z]+$")));

                    cout << "|----------------------------|" << endl;

                    do
                    {
                        cout << "| Enter Arrival Location (Alphabetic only):          | " << endl;
                        cout << "| ";
                        cin >> arrival;
                        if (!regex_match(arrival, regex("^[a-zA-Z]+$")))
                        {
                            cout << "| Invalid Arrival Location! Please try again.        |" << endl;
                        }
                    } while (!regex_match(arrival, regex("^[a-zA-Z]+$")));

                    cout << "|----------------------------|" << endl;

                    do
                    {

                        cout << "| Enter Departure Time (YYYY-MM-DD HH:MM):           | " << endl;
                        cout << "| ";
                        cin.ignore();
                        getline(cin, departureTime);

                        if (regex_match(departureTime, regex("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}$")))
                        {
                            break;
                        }
                        else if (!regex_match(departureTime, regex("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}$")))
                        {
                            cout << "| Invalid Date/Time Format! Please try again. |" << endl;
                        }
                    } while (true);

                    cout << "|----------------------------|" << endl;
                    do
                    {
                        cout << "| Enter Available Seats (Positive Integer):          | " << endl;
                        cout << "| ";
                        cin >> availableSeats;
                        if (availableSeats <= 0)
                        {
                            cout << "| Invalid Number of Seats! Please try again.         |" << endl;
                        }
                    } while (availableSeats <= 0);

                    cout << "|----------------------------|" << endl;

                    do
                    {
                        cout << "| Enter Seats Price (Positive Integer):              | " << endl;
                        cout << "| ";
                        cin >> priceperseat;
                        if (priceperseat <= 0)
                        {
                            cout << "| Invalid Price! Please try again.                   |" << endl;
                        }
                    } while (priceperseat <= 0);

                    cout << "******************************" << endl;

                    addFlight(head, flightID, departure, arrival, departureTime, availableSeats, priceperseat);
                }
                else if (choice == "2")
                {
                    displayAllBookings(Bookinghead, head);
                }

                else if (choice == "3")
                {
                    displayFlights(head);
                }
                else if (choice == "4")
                {
                    displayPassengers(passengerhead);
                }
                else if (choice == "5")
                {
                    cout << "Exiting portal..." << endl;
                    return;
                }
                else
                {
                    cout << "Invalid choice, please try again." << endl;
                }
            }
        }
    }
};

class passenger
{
public:
    passenger(passengerNode *&passengerhead, FlightNode *&flighthead, bookingNode *&Bookinghead)
    {
        while (true)
        {

            string choice;
            cout << "==========================================" << endl;
            cout << "          Welcome to Our System           " << endl;
            cout << "==========================================" << endl;
            cout << "| Press 1 to Create an account           |" << endl;
            cout << "| Press 2 to Login to an account         |" << endl;
            cout << "| Press 3 to exit                        |" << endl;
            cout << "==========================================" << endl;
            cout << "| Enter your choice                      |" << endl;
            cout << "| ";
            cin >> choice;
            cout << "==========================================" << endl;

            if (choice == "1")
            {

                string passengerID, Firstname, Lastname, email, phone_number, password;
                string passportId;

                cout << "*********************************" << endl;
                cout << "|      Add Passenger Details    |" << endl;
                cout << "*********************************" << endl;
                cout << "|-------------------------------|" << endl;

                do
                {
                    cout << "| Enter Passenger ID (Alphanumeric, Max 10 characters): | " << endl;
                    cout << "| ";
                    cin >> passengerID;
                    if (!regex_match(passengerID, regex("^[a-zA-Z0-9]{1,10}$")))
                    {
                        cout << "| Invalid Flight ID! Please try again.               |" << endl;
                    }
                } while (!regex_match(passengerID, regex("^[a-zA-Z0-9]{1,10}$")));
                cout << "|-------------------------------|" << endl;

                do
                {
                    cout << "| Enter First name:             | " << endl;
                    cout << "| ";
                    cin >> Firstname;
                    if (!regex_match(Firstname, regex("^[a-zA-Z]+$")))
                    {
                        cout << "| Invalid name! Please try again.      |" << endl;
                    }
                } while (!regex_match(Firstname, regex("^[a-zA-Z]+$")));
                cout << "|-------------------------------|" << endl;

                do
                {
                    cout << "| Enter Last name:             | " << endl;
                    cout << "| ";
                    cin >> Lastname;
                    if (!regex_match(Lastname, regex("^[a-zA-Z]+$")))
                    {
                        cout << "| Invalid name! Please try again.      |" << endl;
                    }
                } while (!regex_match(Lastname, regex("^[a-zA-Z]+$")));
                cout << "|-------------------------------|" << endl;
                do
                {
                    cout << "| Enter Email ID:               | " << endl;
                    cout << "| ";
                    cin >> email;
                    if (!regex_match(email, regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$")))
                    {
                        cout << "| Invalid Email! Please try again.                     |" << endl;
                    }
                } while (!regex_match(email, regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$")));

                cout << "|-------------------------------|" << endl;
                do
                {
                    cout << "| Enter Phone Number:           | " << endl;
                    cout << "| ";
                    cin >> phone_number;
                    if (!regex_match(phone_number, regex("^[0-9]{11}$")))
                    {
                        cout << "| Invalid Phone Number! Must be exactly 11 digits.     |" << endl;
                    }
                } while (!regex_match(phone_number, regex("^[0-9]{11}$")));
                cout << "|-------------------------------|" << endl;
                do
                {
                    cout << "| Enter Passport Number:        | " << endl;
                    cout << "| ";
                    cin >> passportId;
                    if (!regex_match(passportId, regex("^[a-zA-Z0-9]{6,9}$")))
                    {
                        cout << "| Invalid Passport Number! Must be 6-9 alphanumeric characters. |" << endl;
                    }
                } while (!regex_match(passportId, regex("^[a-zA-Z0-9]{6,9}$")));
                cout << "|-------------------------------|" << endl;
                do
                {
                    cout << "| Enter Password (8 digits):    | " << endl;
                    cout << "| ";
                    cin >> password;
                    if (!regex_match(password, regex("^[0-9]{8}$")))
                    {
                        cout << "| Invalid Password! Must contain exactly 8 digits.     |" << endl;
                    }
                } while (!regex_match(password, regex("^[0-9]{8}$")));
                cout << "|-------------------------------|" << endl;
                cout << "*********************************" << endl;

                addPassenger(passengerhead, passengerID, Firstname, Lastname, email, phone_number, passportId, password);
                cout << "Passenger added successfully!" << endl;
            }
            else if (choice == "2")
            {

                login(passengerhead, flighthead, Bookinghead);
            }

            else if (choice == "3")
            {
                cout << "| ";
                cout << "Exiting portal..." << endl;
                return;
            }
            else
            {
                cout << "Invalid choice, please try again." << endl;
            }
        }
    }
};

void saveFlightsToFile(FlightNode *head)
{
    ofstream fout("flights.txt");
    FlightNode *temp = head;
    while (temp)
    {
        fout << temp->flightID << "," << temp->departure << "," << temp->arrival << ","
             << temp->departureTime << "," << temp->availableSeats << "," << temp->priceperseat << "\n";
        temp = temp->next;
    }
    fout.close();
}
void loadFlightsFromFile(FlightNode *&head)
{
    ifstream fin("flights.txt");
    string flightID, departure, arrival, departureTime;
    int availableSeats, priceperseat;

    while (getline(fin, flightID, ','))
    {
        getline(fin, departure, ',');
        getline(fin, arrival, ',');
        getline(fin, departureTime, ',');
        fin >> availableSeats;
        fin.ignore(); // to skip the comma
        fin >> priceperseat;
        fin.ignore(); // to skip the newline

        addFlight(head, flightID, departure, arrival, departureTime, availableSeats, priceperseat);
    }
    fin.close();
}
void savePassengersToFile(passengerNode *head)
{
    ofstream fout("passengers.txt");
    while (head)
    {
        fout << head->passengerID << "," << head->Firstname << "," << head->Lastname << ","
             << head->email << "," << head->phone_number << "," << head->passportId << "," << head->password << "\n";
        head = head->next;
    }
    fout.close();
}
void loadPassengersFromFile(passengerNode *&head)
{
    ifstream fin("passengers.txt");
    string passengerID, Firstname, Lastname, email, phone, passportId, password;

    while (getline(fin, passengerID, ','))
    {
        getline(fin, Firstname, ',');
        getline(fin, Lastname, ',');
        getline(fin, email, ',');
        getline(fin, phone, ',');
        getline(fin, passportId, ',');
        getline(fin, password);
        addPassenger(head, passengerID, Firstname, Lastname, email, phone, passportId, password);
    }
    fin.close();
}
void saveBookingsToFile(bookingNode *head)
{
    ofstream fout("bookings.txt");
    while (head)
    {
        fout << head->passengerID << "," << head->flightID << "," << head->seatsBooked << "," << head->totalPrice << "\n";
        head = head->next;
    }
    fout.close();
}
void loadBookingsFromFile(bookingNode *&head)
{
    ifstream fin("bookings.txt");
    string passengerID, flightID;
    int seats, total;
    while (getline(fin, passengerID, ','))
    {
        getline(fin, flightID, ',');
        fin >> seats;
        fin.ignore();
        fin >> total;
        fin.ignore();

        bookingNode *newBooking = new bookingNode{passengerID, flightID, seats, total, head};
        head = newBooking;
    }
    fin.close();
}

int main()
{

    FlightNode *head = 0;
    passengerNode *passengerhead = 0;
    bookingNode *Bookinghead = 0;
    loadFlightsFromFile(head);
    loadPassengersFromFile(passengerhead);
    loadBookingsFromFile(Bookinghead);

    for (int i = 0; i < 80; i++)
    {
        cout << "~";
    }

    cout << endl;
    cout << "                    Flight Reservation System" << endl;

    for (int i = 0; i < 80; i++)
    {
        cout << "~";
    }
    cout << endl
         << endl;
    string option;

t:
    cout << "**********************************" << endl;
    cout << "| Enter 1 (if you're admin):    |" << endl;
    cout << "| Enter 2 (if you're passenger):|" << endl;
    cout << "| Enter 3 (Exit)               :|" << endl;
    cout << "|-------------------------------|" << endl;
    cout << "| Enter Your Choice:            |" << endl;
    cout << "| ";
    cin >> option;
    cout << "|-------------------------------|" << endl;
    cout << "**********************************" << endl
         << endl;

    if (option == "1")
    {
        Admin admin(head, passengerhead, Bookinghead);
        goto t;
    }
    if (option == "2")
    {
        passenger p(passengerhead, head, Bookinghead);
        goto t;
    }
    if (option == "3")
    {
         saveFlightsToFile(head);
    savePassengersToFile(passengerhead);
    saveBookingsToFile(Bookinghead);

        return 0;
    }
    else
    {

        cout << "Invalid Entry. Please enter 1 or 2 or 3.\n";
        goto t;
    }
    saveBookingsToFile(Bookinghead);
   
    return 0;
}
