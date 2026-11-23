#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Time
{
    short h, m, s;
};

class Train
{
private:
    int number;
    Time departureTime;
    string destination;

public:
    Train()
    {
        number = 0;
        departureTime = { 0, 0, 0 };
        destination = "";
    }

    Train(int number, Time time, string destination)
    {
        this->number = number;
        departureTime = time;
        this->destination = destination;
    }

    int getNumber() const
    {
        return number;
    }

    Time getTime() const
    {
        return departureTime;
    }

    string getDestination() const
    {
        return destination;
    }

    void setTime(Time time)
    {
        departureTime = time;
    }

    bool operator<(const Train& other) const
    {
        if (departureTime.h != other.departureTime.h)
            return departureTime.h < other.departureTime.h;

        if (departureTime.m != other.departureTime.m)
            return departureTime.m < other.departureTime.m;

        return departureTime.s < other.departureTime.s;
    }

    friend ostream& operator<<(ostream& out, const Train& train)
    {
        out << train.number << " "
            << train.departureTime.h << " "
            << train.departureTime.m << " "
            << train.departureTime.s << " "
            << train.destination;

        return out;
    }

    friend istream& operator>>(istream& in, Train& train)
    {
        in >> train.number
            >> train.departureTime.h
            >> train.departureTime.m
            >> train.departureTime.s
            >> ws;

        getline(in, train.destination);

        return in;
    }

    void Show() const
    {
        cout << left << setw(12) << number
            << setw(15)
            << setfill('0')
            << departureTime.h << ":"
            << setw(2) << departureTime.m << ":"
            << setw(2) << departureTime.s
            << setfill(' ')
            << "  " << destination << endl;
    }
};

class Railway
{
private:
    vector<Train> trains;

public:
    void AddTrain()
    {
        int number;
        Time time;
        string destination;

        cout << "Enter train number: ";
        cin >> number;

        if (FindTrain(number) != nullptr)
        {
            cout << "Train already exists!" << endl;
            return;
        }

        cout << "Enter departure time (HH MM SS): ";
        cin >> time.h >> time.m >> time.s;

        if (time.h < 0 || time.h > 23 ||
            time.m < 0 || time.m > 59 ||
            time.s < 0 || time.s > 59)
        {
            cout << "Invalid time!" << endl;
            return;
        }

        cout << "Enter destination station: ";
        cin >> ws;
        getline(cin, destination);

        if (destination.empty())
        {
            cout << "Destination cannot be empty!" << endl;
            return;
        }

        trains.push_back(Train(number, time, destination));

        cout << "Train added successfully!" << endl;
    }

    Train* FindTrain(int number)
    {
        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                return &trains[i];
            }
        }

        return nullptr;
    }

    void ShowAll() const
    {
        if (trains.empty())
        {
            cout << "No trains!" << endl;
            return;
        }

        cout << "\n========== ALL TRAINS ==========\n";
        cout << "Number      Time           Destination\n";

        for (const Train& train : trains)
        {
            train.Show();
        }
    }

    void ShowTrain()
    {
        int number;

        cout << "Enter train number: ";
        cin >> number;

        Train* train = FindTrain(number);

        if (train == nullptr)
        {
            cout << "Train not found!" << endl;
            return;
        }

        cout << "\nTrain information:\n";
        train->Show();
    }

    void EditTime()
    {
        int number;
        Time time;

        cout << "Enter train number: ";
        cin >> number;

        Train* train = FindTrain(number);

        if (train == nullptr)
        {
            cout << "Train not found!" << endl;
            return;
        }

        cout << "Enter new time (HH MM SS): ";
        cin >> time.h >> time.m >> time.s;

        if (time.h < 0 || time.h > 23 ||
            time.m < 0 || time.m > 59 ||
            time.s < 0 || time.s > 59)
        {
            cout << "Invalid time!" << endl;
            return;
        }

        train->setTime(time);

        cout << "Time updated successfully!" << endl;
    }

    void SortTrains()
    {
        sort(trains.begin(), trains.end());

        cout << "Trains sorted successfully!" << endl;
    }

    void ShowByDestination()
    {
        string destination;
        bool found = false;

        cout << "Enter destination station: ";
        cin >> ws;
        getline(cin, destination);

        cout << "\nTrains to " << destination << ":\n";

        for (const Train& train : trains)
        {
            if (train.getDestination() == destination)
            {
                train.Show();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No trains to this destination!" << endl;
        }
    }

    void SaveToFile()
    {
        ofstream file("trains.txt");

        if (!file.is_open())
        {
            cout << "Cannot open file!" << endl;
            return;
        }

        for (const Train& train : trains)
        {
            file << train << endl;
        }

        file.close();

        cout << "Data saved successfully!" << endl;
    }

    void LoadFromFile()
    {
        ifstream file("trains.txt");

        if (!file.is_open())
        {
            cout << "Cannot open file!" << endl;
            return;
        }

        vector<Train> loaded;
        Train train;

        while (file >> train)
        {
            loaded.push_back(train);
        }

        trains = loaded;

        file.close();

        cout << "Data loaded successfully!" << endl;
    }
};

int main()
{
    Railway railway;
    int choice;

    do
    {
        cout << "\n===== RAILWAY STATION SYSTEM =====\n";
        cout << "1. Add train\n";
        cout << "2. Show all trains\n";
        cout << "3. Find train by number\n";
        cout << "4. Edit departure time\n";
        cout << "5. Sort trains by departure time\n";
        cout << "6. Show trains by destination\n";
        cout << "7. Save trains to file\n";
        cout << "8. Load trains from file\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            railway.AddTrain();
            break;

        case 2:
            railway.ShowAll();
            break;

        case 3:
            railway.ShowTrain();
            break;

        case 4:
            railway.EditTime();
            break;

        case 5:
            railway.SortTrains();
            break;

        case 6:
            railway.ShowByDestination();
            break;

        case 7:
            railway.SaveToFile();
            break;

        case 8:
            railway.LoadFromFile();
            break;

        case 0:
            cout << "Program finished!" << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}
