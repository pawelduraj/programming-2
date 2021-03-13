#include <iostream>

using namespace std;

struct Element {

    Element *prev, *next;
    string name;

    Element() {
        this->name = "";
        this->prev = nullptr;
        this->next = nullptr;
    }

    Element(string name) {
        this->name = name;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

// Simple doubly linked list implementation.
struct List {

private:
    Element *head, *tail;
    int size;

public:
    List() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    ~List() {
        clear();
    }

    // Adds an element to the end of the list.
    void add(Element *e) {
        if (size == 0) {
            head = e;
            tail = e;
            e->next = nullptr;
            e->prev = nullptr;
        } else {
            tail->next = e;
            e->next = nullptr;
            e->prev = tail;
            tail = e;
        }
        size++;
    }

    // Creates a new element with the specified name and adds it to the end of the list.
    void add(const string &name) {
        auto *element = new Element(name);
        add(element);
    }

    // Checks if an element with the specified name is in the list.
    bool contain(const string &name) {
        Element *element = head;
        while (element != nullptr) {
            if (element->name == name)
                return true;
            element = element->next;
        }
        return false;
    }

    // Removes the first element with the specified name from the list.
    void remove(const string &name) {
        Element *element = head;
        while (element != nullptr) {
            if (element->name == name) {
                if (element->prev != nullptr and element->next != nullptr) {
                    element->next->prev = element->prev;
                    element->prev->next = element->next;
                } else if (element->prev == nullptr and element->next != nullptr) {
                    head = element->next;
                    element->next->prev = nullptr;
                } else if (element->prev != nullptr and element->next == nullptr) {
                    tail = element->prev;
                    element->prev->next = nullptr;
                } else {
                    head = nullptr;
                    tail = nullptr;
                }
                delete element;
                size--;
                break;
            }
            element = element->next;
        }
    }

    // Removes all elements with the specified name from the list.
    void removeAll(const string &name) {
        Element *element = head;
        int deletedElements = 0;
        while (element != nullptr) {
            if (element->name == name) {
                if (element->prev != nullptr and element->next != nullptr) {
                    element->prev->next = element->next;
                    element->next->prev = element->prev;
                    Element *delElement = element;
                    element = element->next;
                    delete delElement;
                    deletedElements++;
                } else if (element->prev == nullptr and element->next != nullptr) {
                    head = element->next;
                    element->next->prev = nullptr;
                    delete element;
                    deletedElements++;
                    element = head;
                } else if (element->prev != nullptr and element->next == nullptr) {
                    tail = element->prev;
                    element->prev->next = nullptr;
                    delete element;
                    deletedElements++;
                    element = nullptr;
                } else {
                    head = nullptr;
                    tail = nullptr;
                    delete element;
                    deletedElements++;
                    element = nullptr;
                }
            } else {
                element = element->next;
            }
        }
        size -= deletedElements;
    }

    // Returns the number of elements in the list.
    int length() {
        return size;
    }

    // Checks if the list is empty.
    bool isEmpty() {
        return size == 0;
    }

    // Removes all elements from the list.
    void clear() {
        Element *element = head;
        while (element != nullptr) {
            Element *delElement = element;
            element = element->next;
            delete delElement;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Returns zero-based index of the first element with the specified name from the list.
    // Returns -1 if the list doesn't contain an element with the specified name.
    int indexOf(const string &name) {
        Element *element = head;
        for (int i = 0; i < size; i++) {
            if (element->name == name)
                return i;
            element = element->next;
        }
        return -1;
    }

    // Adds an element to the list at the specified position only if the given index
    // is greater than or equal to 0 and less then or equal to the list size.
    void add(Element *e, int index) {
        if (index == 0) {
            e->next = head;
            e->prev = nullptr;
            head = e;
            size++;
            if (size == 1) tail = e;
        } else if (index >= 0 and index < size) {
            Element *element = head;
            for (int i = 0; i < index - 1; ++i)
                element = element->next;
            e->next = element->next;
            e->prev = element;
            e->next->prev = e;
            e->prev->next = e;
            size++;
        } else if (index == size) {
            tail->next = e;
            e->next = nullptr;
            e->prev = tail;
            tail = e;
            size++;
        }
    }

    // Creates a new element with the specified name and adds it to the list at the specified position
    // only if the given index is greater than or equal to 0 and less then or equal to the list size.
    void add(const string &name, int index) {
        if (index >= 0 and index <= size) {
            auto *element = new Element(name);
            add(element, index);
        }
    }

    // Removes all repetitions from the list.
    void removeRep() {
        Element *element1 = head;
        Element *element2;
        int deletedElements = 0;
        while (element1 != nullptr) {
            element2 = element1->next;
            while (element2 != nullptr) {
                if (element1->name == element2->name) {
                    Element *delElement = element2;
                    if (element2->next != nullptr) {
                        element2->prev->next = element2->next;
                        element2->next->prev = element2->prev;
                    } else {
                        element2->prev->next = nullptr;
                        tail = element2->prev;
                    }
                    element2 = element2->next;
                    delete delElement;
                    deletedElements++;
                } else {
                    element2 = element2->next;
                }
            }
            element1 = element1->next;
        }
        size -= deletedElements;
    }

    // Reverses the list.
    void reverse() {
        Element *element = head;
        Element *prevElement = nullptr;
        Element *newElement = nullptr;
        tail = head;
        while (element != nullptr) {
            prevElement = element;
            element = element->next;
            prevElement->next = newElement;
            prevElement->prev = element;
            newElement = prevElement;
        }
        head = prevElement;
    }

    // Returns a list-sized array filled with list elements.
    Element *toArray() {
        auto *array = new Element[size];
        Element *element = head;
        for (int i = 0; i < size; i++) {
            array[i] = *element;
            element = element->next;
        }
        return array;
    }

    // Prints names of list elements separated by space.
    void print() {
        Element *element = head;
        for (int i = 0; i < size; i++) {
            cout << element->name << ' ';
            element = element->next;
        }
        cout << '\n';
    }
};


// The TestList struct operates on a singly linked list. It has the same functions as the List structure.
// Functions return nothing, but print all operations and results to the console.
struct TestList {

    List list;

    ~TestList() {
        list.clear();
    }

    void add(Element *e) {
        cout << "add(new Element(\"" << e->name << "\"));\n";
        list.add(e);
    }

    void add(const string &name) {
        cout << "add(\"" << name << "\");\n";
        list.add(name);
    }

    void contain(const string &name) {
        cout << "contain(\"" << name << "\"); // " << list.contain(name) << '\n';
    }

    void remove(const string &name) {
        cout << "remove(\"" << name << "\");\n";
        list.remove(name);
    }

    void removeAll(const string &name) {
        cout << "removeAll(\"" << name << "\");\n";
        list.removeAll(name);
    }

    void length() {
        cout << "length(); // " << list.length() << '\n';
    }

    void isEmpty() {
        cout << "isEmpty(); // " << list.isEmpty() << '\n';
    }

    void clear() {
        cout << "clear();\n";
        list.clear();
    }

    void indexOf(const string &name) {
        cout << "indexOf(\"" << name << "\"); // " << list.indexOf(name) << '\n';
    }

    void add(Element *e, int index) {
        cout << "add(new Element(\"" << e->name << "\"), " << index << ");\n";
        list.add(e, index);
    }

    void add(const string &name, int index) {
        cout << "add(\"" << name << "\", " << index << ");\n";
        list.add(name, index);
    }

    void removeRep() {
        cout << "removeRep();\n";
        list.removeRep();
    }

    void reverse() {
        cout << "reverse();\n";
        list.reverse();
    }

    void toArray() {
        cout << "toArray(); // ";
        Element *array = list.toArray();
        for (int i = 0; i < list.length(); i++)
            cout << array[i].name << ' ';
        delete[] array;
        cout << '\n';
    }

    void print() {
        cout << "list: ";
        list.print();
    }
};

int main() {

    TestList list;
    cout << boolalpha; // display bool as true/false instead of 1/0

    // TEST 1
    cout << "\nTEST 1\n";
    list.print();
    list.length();
    list.isEmpty();
    list.contain("Alpha");
    list.remove("Alpha");
    list.removeAll("Beta");
    list.print();
    list.indexOf("Gamma");
    list.removeRep();
    list.reverse();
    list.print();
    list.clear();

    // TEST 2
    cout << "\nTEST 2\n";
    list.add(new Element("Alpha"));
    list.isEmpty();
    list.length();
    list.contain("Alpha");
    list.indexOf("Alpha");
    list.reverse();
    list.clear();
    list.isEmpty();
    list.contain("Alpha");
    list.indexOf("Alpha");

    // TEST 3
    cout << "\nTEST 3\n";
    list.add("Beta");
    list.add("Delta");
    list.print();
    list.length();
    list.add("Alpha", 0);
    list.print();
    list.add("Gamma", 2);
    list.print();
    list.length();
    list.add("Tau", -5);
    list.add("Omicron", 7);
    list.add("Epsilon", 4);
    list.print();
    list.reverse();
    list.print();

    // TEST 4
    cout << "\nTEST 4\n";
    list.clear();
    list.add("Alpha");
    list.add("Beta");
    list.add("Alpha");
    list.add("Beta");
    list.add("Alpha");
    list.add("Beta");
    list.add("Alpha");
    list.print();
    list.toArray();
    list.reverse();
    list.print();
    list.contain("Alpha");
    list.contain("Beta");
    list.contain("Gamma");
    list.contain("alpha");
    list.remove("Alpha");
    list.print();
    list.removeRep();
    list.print();
    list.add("Beta");
    list.add("Alpha");
    list.print();
    list.removeAll("Alpha");
    list.print();
    list.removeAll("Beta");
    list.print();
    list.length();

    return 0;
}