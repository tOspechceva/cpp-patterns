/*
  ЛЕГЕНДА: Погода — изменилась температура → рассылка всем подписчикам.
  СУТЬ: При изменении одного объекта все подписчики уведомляются.
  КОГДА: события, подписки, реактивные данные.
*/

#include <iostream>
#include <vector>
using namespace std;

// Подписчик — получает уведомления
class Subscriber {
public:
    virtual void update(const string& data) = 0;
    virtual ~Subscriber() = default;
};

// Источник — рассылает всем при изменении
class WeatherService {
    vector<Subscriber*> subs;
public:
    void subscribe(Subscriber* s) { subs.push_back(s); }
    void notify(const string& data) {
        for (auto s : subs)
            s->update(data);  // Уведомляем каждого
    }
};

// Виджет — конкретный подписчик
class Widget : public Subscriber {
    string name;
public:
    Widget(const string& n) : name(n) {}
    void update(const string& data) override {
        cout << name << ": " << data << endl;
    }
};

int main() {
    WeatherService ws;
    Widget w1("Домашний"), w2("Рабочий");
    ws.subscribe(&w1);
    ws.subscribe(&w2);
    ws.notify("+18°C, ясно");  // Оба получат
}
