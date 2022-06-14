#include <iostream>
#include <string>

using namespace std;

struct Ticket {
    string fullName;
    int type;
    union
    {
        struct { int wagon; } Train;
        struct { int ranking; } Airplane;
    };
    int row;
    string telephoneNumber;
};

Ticket createTicket(int type) {
    Ticket ticket;

    cout << "Enter full name: ";
    while (ticket.fullName == "") {
        getline(cin, ticket.fullName);
    }

    ticket.type = type;
    if (type == 1) {
        cout << "Enter number of wagon: ";
        cin >> ticket.Train.wagon;
    } else {
        cout << "Enter number of row position: ";
        cin >> ticket.Airplane.ranking;
    }

    cout << "Enter number of row: ";
    cin >> ticket.row;
    cout << "Phone number: ";
    while (ticket.telephoneNumber == "") {
        getline(cin, ticket.telephoneNumber);
    }
    return ticket;
}

void printTicket(Ticket ticket) {
    cout << "Name: " << ticket.fullName << "\n";
    if (ticket.type == 1) {
        cout << "Type: Train\n";
        cout << "Wagon: " << ticket.Train.wagon <<", " ;
    }
    else {
        cout << "Type: Airplane\n";
        cout << "Position: " << ticket.Airplane.ranking <<", ";
    }
    cout << ticket.row << "\n";
    cout << "Telephone number: " << ticket.telephoneNumber << "\n";
}

int main()
{
    Ticket dataBase[10], ticket = {"", 0, {0}, 0, "" };

    int i, j;
    for (i = 0; i < sizeof(dataBase) / sizeof(ticket); i++) {
        dataBase[i] = ticket;
    }

    while (true) {
        cout << "    Menu:\n"
            << "1. Data input.\n"
            << "2. Output of information about the ticket.\n"
            << "3. Output of all information.\n"
            << "4. Delete information about ticket.\n"
            << "5. Delete of all information.\n"
            << "6. Finish the job.\n"
            << ">";
        cin >> i;

        switch (i) {
        case 1:
            cout << "Number of ticket: "; cin >> i;
            cout << "Type (1 - Train, 2 - Airplane): "; cin >> j;
            dataBase[i - 1] = createTicket(j);
            break;
        case 2:
            cout << "Number of ticket: "; cin >> i;
            printTicket(dataBase[i - 1]);
            break;
        case 3:
            for (i = 0; i < sizeof(dataBase) / sizeof(ticket); i++) {
                if (dataBase[i].type != 0) {
                    cout << "Ticket #" << i + 1 << ':' << "\n";
                    printTicket(dataBase[i]);
                }
            }
            break;
        case 4:
            cout << "Number of ticket: "; cin >> i;
            dataBase[i - 1] = ticket;
            break;
        case 5:
            for (i = 0; i < sizeof(dataBase) / sizeof(ticket); i++) {
                dataBase[i] = ticket;
            }
            break;
        case 6:
            return 0;
        default: cout << "Repeat input!\n";
        }
    }
}