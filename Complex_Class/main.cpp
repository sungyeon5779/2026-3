#include <iostream>
#include <cstdio>
using namespace std;

class Complex {
private:
double real;
double imag;

public:
void set(double r, double i) {
real = r;
imag = i;
}

void read(const char* msg) {
cout << msg;
cin >> real >> imag;
}

void print(const char* msg) {
printf("%s %.2f + %.2fi\n", msg, real, imag);
}

void add(Complex a, Complex b) {
real = a.real + b.real;
imag = a.imag + b.imag;
}
};

int main() {
Complex A, B, C;

A.read("A = ");
B.read("B = ");

C.add(A, B);

A.print("A = ");
B.print("B = ");
C.print("A + B = ");

return 0;
}
