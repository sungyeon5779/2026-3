#include <iostream>
using namespace std;

#define MAX_DEGREE 100

class Polynomial {
private:
int degree;
float coef[MAX_DEGREE];

public:
Polynomial() {
degree = 0;
for (int i = 0; i < MAX_DEGREE; i++) {
coef[i] = 0;
}
}

void read() {
cout << "다항식의 최고 차수를 입력하시오: ";
cin >> degree;

cout << "각 항의 계수를 입력하시오 (총 " << degree + 1 << "개): ";
for (int i = 0; i <= degree; i++) {
cin >> coef[i];
}
}

void display(const char* msg) {
cout << msg;
for (int i = 0; i < degree; i++) {
cout << coef[i] << "x^" << degree - i << " + ";
}
cout << coef[degree] << endl;
}

void add(Polynomial a, Polynomial b) {
if (a.degree > b.degree) {
*this = a;
for (int i = 0; i <= b.degree; i++) {
coef[i + (degree - b.degree)] += b.coef[i];
}
}
else {
*this = b;
for (int i = 0; i <= a.degree; i++) {
coef[i + (degree - a.degree)] += a.coef[i];
}
}
}
};

int main() {
Polynomial A, B, C;

A.read();
B.read();

C.add(A, B);

A.display("A = ");
B.display("B = ");
C.display("A + B = ");

return 0;
}
