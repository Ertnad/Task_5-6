#include <iostream>
#include <string>

using namespace std;

struct Ticket {
    Ticket* Next; // Указатель на следующую структуру в списке
    string fullName;
    int type;
    union {
        struct { int wagon; } Train;
        struct { int ranking; } Airplane;
    };
    int row;
    string telephoneNumber;
};

Ticket* dataBase = NULL; // Указатель начала списка

Ticket createTicket(int type) {
    Ticket ticket;

    cout << "Enter full name: ";
    while (ticket.fullName.empty()) {
        getline(cin, ticket.fullName);
    }

    ticket.type = type;
    if (type == 1) {
        cout << "Enter number of wagon: ";
        cin >> ticket.Train.wagon;
    }
    else {
        cout << "Enter number of row position: ";
        cin >> ticket.Airplane.ranking;
    }

    cout << "Enter number of row: ";
    cin >> ticket.row;
    cout << "Phone number: ";
    while (ticket.telephoneNumber.empty()) {
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

// Поиск в списке билетов с заданным порядковым номером num в списке (нумеруем, начиная с 0)
Ticket* findTicket(int num) {
    Ticket* p = dataBase;
    while (p != NULL && --num) p = p->Next; // продвигаем указатель вдоль списка
    return p; // Возвращаем указатель на найденный элемент или NULL, если элемент не найден, добавить нового абонента в список за номером num
}

void addTicket(int num, int brand) {
    Ticket* q = new Ticket; // Создали новую структуру
    *q = createTicket(brand); // Заполнили ее информацией
    if (dataBase == NULL) num = 0; // Если список пустой - добавим в начало
    if (num) {
        Ticket* p = dataBase; // Ищем указатель на предыдущую структуру
        while (p->Next != NULL && -num)
        p = p->Next;
        q->Next = p->Next;
        p->Next = q; // Вставляем новую структуру после *p
    }
    else {
        q->Next = dataBase; // Добавим в начало списка
        dataBase = q;
    }
}

void deleteTicket(int num) {
    Ticket* q;
    if (dataBase == NULL) return;
    if (num) {
        Ticket* p = dataBase; // Ищем указатель на предыдущую структуру.
        while (p->Next != NULL && -num) p = p->Next;
        if ((q = p->Next) != NULL) {
            p->Next = q->Next;
            delete q;
        }
    }
    else { // Удаляем начальный элемент
        q = dataBase;
        dataBase = q->Next;
        delete q;
    }
}

int main() {
    Ticket* p;
    int i, j;
    while (true) {
        cout << " Menu:\n"
                << "1. Data input.\n"
                << "2. Output of information about the ticket.\n"
                << "3. Output of all information.\n"
                << "4. Delete information about ticket.\n"
                << "5. Finish the job.\n"
                << ">";
        cin >> i;
        switch (i) {
            case 1:
                cout << "Type (1 - Train, 2 - Airplane): "; cin >> j;
                addTicket(i, j);
                break;
            case 2:
                cout << "Ticket #: "; cin >> i;
                if ((p = findTicket(i)) != NULL)
                    printTicket(*p);
                else cout << "Ticket is not found!" << endl;
                break;
            case 3:
                p = dataBase;
                i = 0;
                while (p != NULL) {
                    cout << "Ticket #" << i + 1 << ':' << "\n";
                    printTicket(*p);
                    p = p->Next;
                }
                break;
            case 4:
                cout << "Ticket #: ";
                cin >> i;
                deleteTicket(i);
                break;
            case 5:
                while (dataBase != NULL) {
                    p = dataBase;
                    dataBase = p->Next;
                    delete p;
                }
                return 0;
            default: cout << "Repeat input!\n";
        }
    }
}