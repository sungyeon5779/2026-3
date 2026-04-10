#include <iostream>
#include <cstring>
using namespace std;

class Car {
protected:
int speed;
char name[40];

public:
int gear;

Car() {
speed = 0;
gear = 0;
strcpy(name, "NoName");
}

Car(int s, const char* n, int g) {
speed = s;
gear = g;
strcpy(name, n);
}

void changeGear(int g = 4) {
gear = g;
}

void speedUp() {
speed += 5;
}

void display() {
cout << "[" << name << "] : 기어=" << gear << "단 속도=" << speed << "kmph" << endl;
}
};

class SportsCar : public Car {
public:
bool bTurbo;

SportsCar() : Car() {
bTurbo = false;
}

SportsCar(int s, const char* n, int g, bool t) : Car(s, n, g) {
bTurbo = t;
}

void setTurbo(bool t) {
bTurbo = t;
}

void speedUp() {
if (bTurbo)
speed += 20;
else
Car::speedUp();
}
};

int main() {
Car c1(50, "Avante", 3);
SportsCar c2(50, "Ferrari", 3, false);

c1.display();
c1.changeGear(4);
c1.speedUp();
c1.display();

c2.display();
c2.setTurbo(true);
c2.speedUp();
c2.display();

return 0;
}
