#include <iostream>
#include <string>

using namespace std;
// Main class of Bus Reservation System
class bus
{
    // Structure to store bus information
    struct Bus
    {
        int busNo;
        string busName;
        int totalSeats;
    };
    // Structure to store route and schedule information
    struct Route
    {
        int routeId;
        int busNo;
        string from, to;
        string departure, arrival;
        float fare;
    };
    // Structure to store passenger booking information
    struct Booking
    {
        int ticketId;
        int busNo;
        int routeId;
        int seatNo;
        string passengerName;
        float fare;
        bool active;
    };
    // Arrays to store buses, routes and bookings
    Bus buses[10];
    Route routes[10];
    Booking bookings[50];
    // Variables to maintain record counts and ticket ID
    int busCount, routeCount, bookingCount;
    int nextTicketId;
    // Function to search a bus using bus number
    int findBus(int no)
    {
        for(int i = 0; i < busCount; i++)
        {
            if(buses[i].busNo == no)
                return i;
        }
        return -1;
    }
    // Function to search a route using route ID
    int findRoute(int id)
    {
        for(int i = 0; i < routeCount; i++)
        {
            if(routes[i].routeId == id)
               return i;

        }
        return -1;
    }
    // Function to count booked seats of a bus
    int bookedSeats(int no)
    {
        int count = 0;
        for(int i = 0; i < bookingCount; i++)
        {
            if(bookings[i].busNo == no && bookings[i].active)
                count++;
        }
        return count;
    }
public:
    // Constructor to initialize buses, routes and counters
    bus()
    {
        buses[0] = {101, "Volvo", 40};
        buses[1] = {102, "Mercedes", 35};
        routes[0] = {1, 101, "Jaipur", "Delhi", "06:00AM", "11:00AM", 500};
        routes[1] = {2, 102, "Jaipur", "Agra", "08:00AM", "01:00PM", 400};
        busCount = 2;
        routeCount = 2;
        bookingCount = 0;
        nextTicketId = 1001;
    }
    // Function to add a new bus
    void addBus()
    {
        if(busCount >= 10)
        {
            cout << "Bus Limit Reached!\n";
            return;
        }
        int no, seats;
        string name;
        cout << "Enter Bus Number: ";
        cin >> no;
        if(findBus(no) != -1)
        {
            cout << "Bus Already Exists!\n";
            return;
        }
        cout << "Enter Bus Name: ";
        cin >> name;
        cout << "Enter Total Seats: ";
        cin >> seats;
        if(seats <= 0)
        {
            cout << "Invalid Seat Count!\n";
            return;
        }
        buses[busCount] = {no, name, seats};
        busCount++;
        cout << "Bus Added Successfully!\n";
    }
    // Function to display all bus details
    void viewBus()
    {
        cout << "\n----- BUS DETAILS -----\n";
        for(int i = 0; i < busCount; i++)
        {
            cout << "\nBus Number: " << buses[i].busNo;
            cout << "\nBus Name: " << buses[i].busName;
            cout << "\nTotal Seats: " << buses[i].totalSeats;
            cout << "\n";
        }
    }
    // Function to add a new route and schedule
    void addRoute()
    {
        if(routeCount >= 10)
        {
            cout << "Route Limit Reached!\n";
            return;
        }
        int id, no;
        string from, to, dep, arr;
        float fare;
        cout << "Enter Route ID: ";
        cin >> id;
        if(findRoute(id) != -1)
        {
            cout << "Route ID Already Exists!\n";
            return;
        }
        cout << "Enter Bus Number: ";
        cin >> no;
        if(findBus(no) == -1)
        {
            cout << "Bus Not Found!\n";
            return;
        }
        cout << "Enter Starting City: ";
        cin >> from;
        cout << "Enter Destination City: ";
        cin >> to;
        cout << "Enter Departure Time: ";
        cin >> dep;
        cout << "Enter Arrival Time: ";
        cin >> arr;
        cout << "Enter Fare: ";
        cin >> fare;
        if(fare < 0)
        {
            cout << "Invalid Fare!\n";
            return;
        }
        routes[routeCount] = {id, no, from, to, dep, arr, fare};
        routeCount++;
        cout << "Route Added Successfully!\n";
    }
    // Function to display all route details
    void viewRoutes()
    {
        cout << "\n----- ROUTE DETAILS -----\n";
        for(int i = 0; i < routeCount; i++)

        {
            cout << "\nRoute ID: " << routes[i].routeId;
            cout << "\nBus Number: " << routes[i].busNo;
            cout << "\nFrom: " << routes[i].from;
            cout << "\nTo: " << routes[i].to;
            cout << "\nDeparture: " << routes[i].departure;
            cout << "\nArrival: " << routes[i].arrival;
            cout << "\nFare: Rs. " << routes[i].fare;
            cout << "\n";
        }
    }
    // Function to manage routes using a submenu
    void manageRoutes()
    {
        int choice;
        do
        {
            cout << "\n----- ROUTE MANAGEMENT -----\n";
            cout << "1. Add Route\n";
            cout << "2. View Routes\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter Choice: ";
            cin >> choice;
            // Switch statement to perform route management operations
            switch(choice)
            {
                case 1:
                    addRoute();
                    break;
                case 2:
                    viewRoutes();
                    break;
                case 3:
                    break;
                default:
                    cout << "Invalid Choice!\n";
            }
        } while(choice != 3);
    }
    // Function to check total, booked and available seats
    void checkSeats()
    {
        int id;
        cout << "Enter Route ID: ";
        cin >> id;
        int r = findRoute(id);
        if(r == -1)
        {
            cout << "Route Not Found!\n";
            return;
        }
        int total = buses[findBus(routes[r].busNo)].totalSeats;
        int booked = bookedSeats(routes[r].busNo);
        cout << "\nTotal Seats: " << total;
        cout << "\nBooked Seats: " << booked;
        cout << "\nAvailable Seats: " << total - booked << "\n";
    }
    // Function to print passenger ticket details
    void printTicket(int index)
    {
        cout << "\n========== BUS TICKET ==========\n";
        cout << "Ticket ID: " << bookings[index].ticketId;
        cout << "\nPassenger Name: " << bookings[index].passengerName;
        cout << "\nBus Number: " << bookings[index].busNo;
        cout << "\nRoute ID: " << bookings[index].routeId;
        cout << "\nSeat Number: " << bookings[index].seatNo;
        cout << "\nFare: Rs. " << bookings[index].fare;
        // Display booking status
        if(bookings[index].active)
            cout << "\nStatus: Confirmed";
        else
            cout << "\nStatus: Cancelled";
        cout << "\n================================\n";
    }
    // Function to book a seat and calculate fare
    void bookTicket()
    {
        if(bookingCount >= 50)
        {
            cout << "Booking Limit Reached!\n";
            return;
        }
        int id, seat;
        string name;
        // Input route ID for booking
        cout << "Enter Route ID: ";
        cin >> id;
        int r = findRoute(id);
        if(r == -1)
        {
            cout << "Route Not Found!\n";
            return;
        }
        int busIndex = findBus(routes[r].busNo);
        if(busIndex == -1)
        {
            cout << "Bus Not Found!\n";
            return;
        }
        // Check whether seats are available
        int total = buses[busIndex].totalSeats;
        if(bookedSeats(routes[r].busNo) >= total)
        {
            cout << "No Seats Available!\n";
            return;
        }
        // Input seat number from passenger
        cout << "Enter Seat Number (1-" << total << "): ";
        cin >> seat;
        // Validate seat number
        if(seat < 1 || seat > total)
        {
            cout << "Invalid Seat Number!\n";
            return;
        }
        // Check whether the selected seat is already booked
        for(int i = 0; i < bookingCount; i++)
        {
            if(bookings[i].busNo == routes[r].busNo &&
               bookings[i].seatNo == seat &&
               bookings[i].active)
            {
                cout << "Seat Already Booked!\n";
                return;
            }
        }
        // Input passenger name
        cout << "Enter Passenger Name: ";
        cin >> name;

        // Store booking details in the booking array
        bookings[bookingCount] =
        {
            nextTicketId,
            routes[r].busNo,
            routes[r].routeId,
            seat,
            name,
            routes[r].fare,
            true
        };
        // Calculate fare and print ticket
        cout << "\nFare Calculated Successfully!\n";
        printTicket(bookingCount);
        // Update booking counter and ticket ID
        bookingCount++;
        nextTicketId++;
    }
    // Function to search a ticket using ticket ID
    void searchTicket()
    {
        int id;
        cout << "Enter Ticket ID: ";
        cin >> id;
        // Search ticket in the booking array
        for(int i = 0; i < bookingCount; i++)
        {
            if(bookings[i].ticketId == id)
            {
                cout << "\nTicket Found!\n";
                printTicket(i);
                return;
            }
        }

        cout << "Ticket Not Found!\n";
    }
    // Function to cancel an active booking
    void cancelTicket()
    {
        int id;
        cout << "Enter Ticket ID: ";
        cin >> id;
        // Search for ticket and update its status
        for(int i = 0; i < bookingCount; i++)
        {
            if(bookings[i].ticketId == id && bookings[i].active)
            {
                bookings[i].active = false;
                cout << "Ticket Cancelled Successfully!\n";
                return;
            }
        }
        cout << "Active Ticket Not Found!\n";
    }
    // Function to display and control the main menu
    void menu()
    {
        int choice;
        do
        {
            cout << "\n====== BUS RESERVATION SYSTEM ======\n";
            cout << "1. Add Bus\n";
            cout << "2. View Bus Details\n";
            cout << "3. Manage Routes and Schedules\n";
            cout << "4. Check Seat Availability\n";
            cout << "5. Book Ticket\n";
            cout << "6. Search Ticket\n";
            cout << "7. Cancel Ticket\n";
            cout << "8. Exit\n";
            cout << "Enter Your Choice: ";
            cin >> choice;
            // Switch statement to execute selected menu option
            switch(choice)
            {
                case 1:
                    addBus();
                    break;
                case 2:
                    viewBus();
                    break;
                case 3:
                    manageRoutes();
                    break;
                case 4:
                    checkSeats();
                    break;
                case 5:
                    bookTicket();
                    break;
                case 6:
                    searchTicket();
                    break;
                case 7:
                    cancelTicket();
                    break;
                case 8:
                    cout << "Thank You!\n";
                    break;
                default:

                    cout << "Invalid Choice!\n";
            }
        } while(choice != 8);
    }
};
// Main function: login and start the reservation system
int main()
{
    string email, password;
    // Login system to authenticate the user
    cout << "====== LOGIN SYSTEM ======\n";
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;
    // Check login credentials
    if(email == "user@gmail.com" && password == "user123")
    {
        cout << "\nLogin Successful!\n";
        // Create object and call main menu
        bus b;
        b.menu();
    }
    else
    {
        cout << "\nInvalid Email or Password!\n";
    }
    return 0;
}