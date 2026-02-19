/*
  ЛЕГЕНДА: Оплата — покупка одна. Картой или наличными. Меняешь способ — результат тот же.
  СУТЬ: Разные алгоритмы под одним интерфейсом.
  КОГДА: сортировка, оплата, сжатие — несколько способов.
*/

#include <iostream>
using namespace std;

// Стратегия — способ оплаты
class Payment {
public:
    virtual void pay(int sum) = 0;
    virtual ~Payment() = default;
};

// Картой
class CardPayment : public Payment {
    void pay(int s) override { cout << "Оплата картой: " << s << endl; }
};
// Наличными
class CashPayment : public Payment {
    void pay(int s) override { cout << "Оплата наличными: " << s << endl; }
};

// Касса — может менять способ
class Checkout {
    Payment* method;
public:
    void setMethod(Payment* p) { method = p; }
    void checkout(int sum) { method->pay(sum); }
};

int main() {
    Checkout ch;
    ch.setMethod(new CardPayment());
    ch.checkout(100);
    ch.setMethod(new CashPayment());
    ch.checkout(100);
}
