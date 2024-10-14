#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Date {
    int day, month, year;

    Date(const string& s) {
        sscanf(s.c_str(), "%d/%d/%d", &day, &month, &year);
    }

    bool operator>(const Date& other) const {
        if (year != other.year) return year > other.year;
        if (month != other.month) return month > other.month;
        return day > other.day;
    }
    
    bool operator==(const Date& other) const {
        if (year == other.year && month == other.month && day > other.day) return true;
        else return false;
    }
};

struct Game {
    Date date;
    int localGoals, visitGoals;

    Game(const string& dateStr, int localGoals, int visitGoals)
        : date(dateStr), localGoals(localGoals), visitGoals(visitGoals) {}

    int totalGoals() const {
        return localGoals + visitGoals;
    }

    bool operator>(const Game& other) const {
        if (totalGoals() != other.totalGoals())
            return totalGoals() > other.totalGoals();
        return date > other.date;
    }
    
    // Definimos el operador < para la comparación.
    bool operator<(const Game& other) const {
        return !(*this > other) && !(*this == other);
    }

    bool operator==(const Game& other) const {
        return (localGoals == other.localGoals && visitGoals == other.visitGoals && date == other.date);
    }
};

template <class T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <class T>
class TopList {
    int top;
    Node<T>* root;
    int size;

public:
    TopList(int top) : top(top), root(nullptr), size(0) {}

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!root) {
            root = newNode;
        }
        else if (!root.next) {
            root.next = newNode;
        } else {
            Node<T>* current = root;
            Node<T>* previous = nullptr;

            while (newNode->value > current->value) {
                if (current->next) {
                    Node<T>* tmp = current;
                    current = current->next;
                    previous = tmp;
                } else {
                    
                }
            }
        }

        size++;
        if (size > top) {
            Node<T>* toDelete = root;
            root = root->next;
            delete toDelete;
            size--;
        }
    }

    void print() const {
        Node<T>* current = root;
        while (current) {
            cout << current->data.date.day << "/"
                 << current->data.date.month << "/"
                 << current->data.date.year << " "
                 << current->data.localGoals << "-"
                 << current->data.visitGoals << " total: "
                 << current->data.totalGoals() << endl;
            current = current->next;
        }
    }
};

int main() {
    TopList<Game> top5(5);
    top5.push({"22/4/2005", 2, 3});
    top5.push({"21/4/2005", 5, 3});
    top5.push({"22/4/2005", 5, 3});
    top5.push({"23/4/2005", 5, 3});
    top5.push({"21/4/2005", 5, 4});
    top5.push({"20/4/2005", 7, 3});
    top5.push({"23/4/2005", 5, 4});

    top5.print();

    return 0;
}
