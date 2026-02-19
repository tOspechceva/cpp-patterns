/*
  ЛЕГЕНДА: Дверь — закрыта: «закрыто». Открыта: «проходи». Состояние решает, что делать.
  СУТЬ: Поведение зависит от внутреннего состояния.
  КОГДА: лифт, автомат, заказ — разные действия в разных состояниях.
*/

#include <iostream>
using namespace std;

class Door;

// Состояние — знает что делать
class DoorState {
public:
    virtual void open(Door* d) = 0;
    virtual void close(Door* d) = 0;
};

// Дверь — хранит текущее состояние
class Door {
    DoorState* state;
public:
    void setState(DoorState* s) { state = s; }
    void open()  { state->open(this); }
    void close() { state->close(this); }
};

// Закрыта
class Closed : public DoorState {
public:
    void open(Door* d) override;
    void close(Door*) override { cout << "Уже закрыта\n"; }
};

// Открыта
class Opened : public DoorState {
public:
    void open(Door*) override { cout << "Уже открыта\n"; }
    void close(Door* d) override {
        cout << "Закрываю\n";
        d->setState(new Closed());
    }
};

void Closed::open(Door* d) {
    cout << "Открываю — проходи\n";
    d->setState(new Opened());
}

int main() {
    Door door;
    door.setState(new Closed());
    door.open();
    door.close();
}
