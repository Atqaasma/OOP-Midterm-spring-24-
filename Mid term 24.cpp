#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Customer {
  string name;
public:
    Customer(string name):name(name) {}
    void display(){
        cout << "Customer Name: " << name << "\n";
    }
};

class Reservation {
private:
    Customer* customer; 
    string timeSlot;
public:
    Reservation(Customer* customer, string time) : customer(customer), timeSlot(time) {}
    void display() {
        customer->display();
        cout << "Time Slot: " << timeSlot << "\n";
    }
    string getTimeSlot() {
        return timeSlot;
    }
};

class Restaurant {
private:
    vector<string> availableTimeSlots;
    vector<Reservation*> reservations; 
public:
    Restaurant() {
        availableTimeSlots = {"10:00-11:00", "11:00-12:00", "12:00-13:00","13:00-14:00", "14:00-15:00", "15:00-16:00", "16:00-17:00","17:00-18:00", "18:00-19:00","19:00-20:00", "20:00-21:00", "21:00-22:00", "22:00-23:00"};
    }
    ~Restaurant() {
        
        for(auto* reservation : reservations) {
            delete reservation;
        }
    }
    
    bool makeReservation(Customer* customer,  string time) {
        for (auto it = availableTimeSlots.begin(); it != availableTimeSlots.end(); ++it) {
            if (*it == time) {
                reservations.push_back(new Reservation(customer, time));
                availableTimeSlots.erase(it);
                return true;
            }
        }
        return false;
    }
    bool cancelReservation(string time) {
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if ((*it)->getTimeSlot() == time) {
                availableTimeSlots.push_back(time);
                delete *it; 
                reservations.erase(it);
                return true;
            }
        }
        return false;
    }
    void showReservations() {
        cout << "Reservations:\n";
        for (const auto& reservation : reservations) {
            reservation->display();
        }
    }
    int getTotalReservations() {
        return reservations.size();
    }
    void showAvailableTimeSlots() {
        cout << "Available time slots are:\n";
        for (const auto& time : availableTimeSlots) {
            cout << time << "\n";
        }
    }
};

int main() {
    Restaurant myRestaurant;
    myRestaurant.showAvailableTimeSlots();

    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    Customer customer(name);

    string time;
    cout << "Enter time slot you want to reserve: ";
    cin >> time;

    try {
        if (myRestaurant.makeReservation(&customer, time)) {
            cout << "Reservation done successfully!\n";
        } else {
            throw runtime_error("Sorry, that time slot is not available.\n");
        }
    } catch (const exception& e) {
        cerr << e.what();
        return 1;
    }

    myRestaurant.showAvailableTimeSlots();
    myRestaurant.showReservations();

    cout << "Total reservations: " << myRestaurant.getTotalReservations() << "\n";
    //For canceling the reservations
    cout << "Enter a time slot to cancel the reservation: ";
    cin >> time;
    if (myRestaurant.cancelReservation(time)) {
        cout << "Reservation cancelled successfully!\n";
    } else {
        cout << "No reservation found for the given time slot.\n";
    }

    myRestaurant.showAvailableTimeSlots();
    myRestaurant.showReservations();

    cout << "Total reservations: " << myRestaurant.getTotalReservations() << "\n";

    return 0;
}

