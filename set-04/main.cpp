#include <iostream>

using namespace std;

struct ComplexNumber {

    double re;
    double im;

    ComplexNumber(double re = 0, double im = 0) : re(re), im(im) {}

    ComplexNumber &operator=(const ComplexNumber &x) = default;
};

/*
 * The following operations are defined for complex numbers:
 * x + y, x += y    addition
 * x - y, x -= y    subtraction
 * x * y, x *= y    multiplication
 * x / y, x /= y    division
 * ==, !=           comparison
 * -x               negation
 * !x               conjugation
 * ++x              post-incrementation of the real part by 1
 * --x              post-decrementation of the real part by 1
 * x++              post-incrementation of the imaginary part by 1
 * x--              post-decrementation of the imaginary part by 1
 * x = y            assignment
 * */

ComplexNumber operator+(const ComplexNumber &x, const ComplexNumber &y) {
    return ComplexNumber(x.re + y.re, x.im + y.im);
}

ComplexNumber operator+=(ComplexNumber &x, const ComplexNumber &y) {
    x.re += y.re;
    x.im += y.im;
    return ComplexNumber(x.re, x.im);
}

ComplexNumber operator-(const ComplexNumber &x, const ComplexNumber &y) {
    return ComplexNumber(x.re - y.re, x.im - y.im);
}

ComplexNumber operator-=(ComplexNumber &x, const ComplexNumber &y) {
    x.re -= y.re;
    x.im -= y.im;
    return ComplexNumber(x.re, x.im);
}

ComplexNumber operator*(const ComplexNumber &x, const ComplexNumber &y) {
    return ComplexNumber(x.re * y.re - x.im * y.im, x.im * y.re + x.re * y.im);
}

ComplexNumber operator*=(ComplexNumber &x, const ComplexNumber &y) {
    double newRe = x.re * y.re - x.im * y.im;
    double newIm = x.im * y.re + x.re * y.im;
    return ComplexNumber(x.re = newRe, x.im = newIm);
}

ComplexNumber operator/(const ComplexNumber &x, const ComplexNumber &y) {
    return ComplexNumber((x.re * y.re + x.im * y.im) / (y.re * y.re + y.im * y.im),
                         (x.im * y.re - x.re * y.im) / (y.re * y.re + y.im * y.im));
}

ComplexNumber operator/=(ComplexNumber &x, const ComplexNumber &y) {
    double newRe = (x.re * y.re + x.im * y.im) / (y.re * y.re + y.im * y.im);
    double newIm = (x.im * y.re - x.re * y.im) / (y.re * y.re + y.im * y.im);
    return ComplexNumber(x.re = newRe, x.im = newIm);
}

ComplexNumber operator-(const ComplexNumber &x) {
    return ComplexNumber(-x.re, -x.im);
}

ComplexNumber operator!(const ComplexNumber &x) {
    return ComplexNumber(x.re, -x.im);
}

bool operator==(const ComplexNumber &x, const ComplexNumber &y) {
    return x.re == y.re and x.im == y.im;
}

bool operator!=(const ComplexNumber &x, const ComplexNumber &y) {
    return x.re != y.re or x.im != y.im;
}

ComplexNumber operator++(ComplexNumber &x) {
    return ComplexNumber(x.re++, x.im);
}

ComplexNumber operator--(ComplexNumber &x) {
    return ComplexNumber(x.re--, x.im);
}

ComplexNumber operator++(ComplexNumber &x, int) {
    return ComplexNumber(x.re, x.im++);
}

ComplexNumber operator--(ComplexNumber &x, int) {
    return ComplexNumber(x.re, x.im--);
}

ostream &operator<<(ostream &out, const ComplexNumber &x) {
    return out << "(" << x.re << ", " << x.im << ")";
}

istream &operator>>(istream &in, ComplexNumber &x) {
    return in >> x.re >> x.im;
}

int main() {

    ComplexNumber x, y, z;
    cout << boolalpha; // display bool as true/false instead of 1/0

    // TEST 1
    cout << "\nTEST 1\n";
    x = ComplexNumber(1, 2);
    y = ComplexNumber(3, 4);
    cout << "x = " << x << "\ny = " << y << '\n';
    cout << "x + y  // " << x + y << '\n';
    cout << "x - y  // " << x - y << '\n';
    cout << "x * y  // " << x * y << '\n';
    cout << "x / y  // " << x / y << '\n';
    cout << "-x     // " << -x << '\n';
    cout << "-(-x)  // " << -(-x) << '\n';
    cout << "!x     // " << !x << '\n';
    cout << "!!x    // " << !!x << '\n';

    // TEST 2
    cout << "\nTEST 2\n";
    x = ComplexNumber(1, 2);
    y = ComplexNumber(3, 4);
    cout << "x = " << x << "\ny = " << y << '\n';
    cout << "x += y // " << (x += y) << '\n';
    cout << "x -= y // " << (x -= y) << '\n';
    cout << "x *= y // " << (x *= y) << '\n';
    cout << "x /= y // " << (x /= y) << '\n';

    // TEST 3
    cout << "\nTEST 3\n";
    x = ComplexNumber(1, 2);
    y = ComplexNumber(3, 4);
    cout << "x = " << x << "\ny = " << y << '\n';
    cout << "x == y // " << (x == y) << '\n';
    cout << "x != y // " << (x != y) << '\n';
    cout << "x = y  // " << (x = y) << '\n';
    cout << "x == y // " << (x == y) << '\n';
    cout << "x != y // " << (x != y) << '\n';

    // TEST 4
    cout << "\nTEST 4\n";
    z = ComplexNumber(1, 2);
    cout << "z = " << z << '\n';
    cout << "++z    // " << ++z << '\n';
    cout << "z      // " << z << '\n';
    cout << "--z    // " << --z << '\n';
    cout << "z      // " << z << '\n';
    cout << "z++    // " << z++ << '\n';
    cout << "z      // " << z << '\n';
    cout << "z--    // " << z-- << '\n';
    cout << "z      // " << z << '\n';

    return 0;
}
