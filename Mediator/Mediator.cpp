/*
  ЛЕГЕНДА: Биржа — все заявки через площадку, а не друг другу напрямую.
  СУТЬ: Центральный посредник — все общаются через него.
  КОГДА: много объектов связаны, без посредника путаница.
*/

#include <iostream>
#include <vector>
using namespace std;

class Trader;

// Посредник — знает всех, рассылает сообщения
class Exchange {
    vector<Trader*> traders;
public:
    void add(Trader* t);
    void broadcast(Trader* from, const string& order);
};

// Участник — общается только через посредника
class Trader {
    string name;
    Exchange* ex;
public:
    Trader(const string& n, Exchange* e) : name(n), ex(e) {}
    void place(const string& order) {
        ex->broadcast(this, order);  // Не пишет каждому — через биржу
    }
    string getName() { return name; }
    virtual void receive(const string& from, const string& msg) {
        cout << name << " получил от " << from << ": " << msg << endl;
    }
};

void Exchange::add(Trader* t) { traders.push_back(t); }
void Exchange::broadcast(Trader* from, const string& msg) {
    for (auto t : traders)
        if (t != from)
            t->receive(from->getName(), msg);
}

int main() {
    Exchange ex;
    Trader a("Алиса", &ex), b("Борис", &ex);
    ex.add(&a);
    ex.add(&b);
    a.place("Куплю 100");
}
