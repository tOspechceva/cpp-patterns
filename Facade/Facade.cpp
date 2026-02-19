/*
  ЛЕГЕНДА: Лифт — нажал этаж. Внутри мотор, трос, двери. Одна кнопка, всё скрыто.
  СУТЬ: Простой интерфейс к сложной подсистеме.
  КОГДА: много классов, нужен один простой способ.
*/
#include <Windows.h>
#include <iostream>
using namespace std;

// --- Сложная подсистема (много деталей) ---
class Motor  { public: void run()   { cout << "Мотор\n"; } };
class Cable  { public: void move()  { cout << "Трос\n"; } };
class Doors  { public: void open()  { cout << "Двери\n"; } };

// --- Фасад — одна кнопка, внутри всё вызывает ---
class Elevator {
    Motor m;
    Cable c;
    Doors d;
public:
    void goToFloor(int f) {
        cout << "Этаж " << f << ": ";
        m.run();
        c.move();
        d.open();
    }
};

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    Elevator el;
    el.goToFloor(5);  // Пользователь — один вызов
}
