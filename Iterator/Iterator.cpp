/*
  ЛЕГЕНДА: Очередь в магазине — первый, второй, третий... Не знаешь весь список заранее.
  СУТЬ: Обход коллекции без знания её устройства.
  КОГДА: списки, деревья, любые коллекции.
*/

#include <iostream>
#include <vector>
using namespace std;

// Итератор — даёт доступ к элементам по одному
template<typename T>
class QueueIterator {
    vector<T>& items;
    int pos = 0;
public:
    QueueIterator(vector<T>& v) : items(v) {}
    bool hasNext() { return pos < (int)items.size(); }
    T next() { return items[pos++]; }
};

int main() {
    vector<string> queue = {"Первый", "Второй", "Третий"};
    QueueIterator<string> it(queue);

    while (it.hasNext())
        cout << it.next() << " ";
    cout << endl;
}
