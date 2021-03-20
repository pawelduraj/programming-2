#include <iostream>

using namespace std;

// Simple implementation of the set which can only contain integers from range [1, 16].
struct Set {

    unsigned short int set;

    Set() {
        this->set = 0;
    }

    Set(unsigned short int set) {
        this->set = set;
    }

    // Checks if the specified number is in the set.
    bool contain(int n) {
        if (n < 1 or n > 16) return false;
        return (set >> (16 - n)) % 2 == 1;
    }

    // Adds the specified number to the set.
    void add(int n) {
        if (n >= 1 and n <= 16) set = set | (((unsigned short int) 1) << (16 - n));
    }

    // Removes the specified number from the set.
    void remove(int n) {
        if (n >= 1 and n <= 16) set = set & ~(((unsigned short int) 1) << (16 - n));
    }

    // Returns the cardinality of the set.
    int cardinality() {
        int cardinality = 0;
        for (int i = 1; i <= 16; i++)
            if ((set >> (16 - i)) % 2 == 1)
                cardinality++;
        return cardinality;
    }
};

/*
 * For any sets A, B the following operations are defined
 * A + B    union
 * A * B    intersection
 * A - B    difference
 * A % B    symmetric difference
 * - A      absolute complement
 */

Set operator+(const Set &A, const Set &B) {
    return Set(A.set | B.set);
}

void operator+=(Set &A, const Set &B) {
    A.set = A.set | B.set;
}

Set operator*(const Set &A, const Set &B) {
    return Set(A.set & B.set);
}

void operator*=(Set &A, const Set &B) {
    A.set = A.set & B.set;
}

Set operator-(const Set &A, const Set &B) {
    return Set(A.set & (~B.set));
}

void operator-=(Set &A, const Set &B) {
    A.set = A.set & (~B.set);
}

Set operator%(const Set &A, const Set &B) {
    return Set(A.set ^ B.set);
}

void operator%=(Set &A, const Set &B) {
    A.set = A.set ^ B.set;
}

Set operator-(const Set &A) {
    return Set(~A.set & 0b1111111111111111);
}

ostream &operator<<(ostream &out, const Set &A) {
    bool firstElementPrinted = false;
    out << "{";
    for (int i = 1; i <= 16; i++) {
        if ((A.set >> (16 - i)) % 2 == 1) {
            if (!firstElementPrinted) {
                out << i;
                firstElementPrinted = true;
            } else out << ", " << i;
        }
    }
    out << "}";
    return out;
}

int main() {

    cout << boolalpha; // display bool as true/false instead of 1/0

    // TEST 1
    cout << "\nTEST 1\n";
    Set a = Set(0b1001100110011001);
    Set b = Set(0b0110110010101011);
    cout << "A = " << a << '\n';
    cout << "B = " << b << '\n';
    cout << "|A| = " << a.cardinality() << '\n';
    cout << "|B| = " << b.cardinality() << '\n';
    cout << "A + B = " << a + b << '\n';
    cout << "A * B = " << a * b << '\n';
    cout << "A - B = " << a - b << '\n';
    cout << "B - A = " << b - a << '\n';
    cout << "A % B = " << a % b << '\n';
    cout << "- A = " << -a << '\n';
    cout << "- B = " << -b << '\n';

    // TEST 2
    cout << "\nTEST 2\n";
    Set c;
    cout << "C = " << c << '\n';
    cout << "|C| = " << c.cardinality() << '\n';
    c.add(3);
    c.add(1);
    c.add(4);
    c.add(20);
    cout << "add(3);\nadd(1);\nadd(4);\nadd(20);\n";
    cout << "C = " << c << '\n';
    cout << "|C| = " << c.cardinality() << '\n';
    cout << "contain(1); // " << c.contain(1) << '\n';
    cout << "contain(2); // " << c.contain(2) << '\n';
    cout << "contain(3); // " << c.contain(3) << '\n';
    cout << "contain(20); // " << c.contain(20) << '\n';
    c.remove(1);
    c.remove(2);
    c.remove(805);
    cout << "remove(1);\nremove(2);\nremove(805);\n";
    cout << "C = " << c << '\n';
    cout << "|C| = " << c.cardinality() << '\n';

    return 0;
}