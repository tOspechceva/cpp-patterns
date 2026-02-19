/*
  ЛЕГЕНДА: Черновик — «Сохранить» = снимок, «Восстановить» = откат.
  СУТЬ: Сохраняет состояние объекта, чтобы потом восстановить.
  КОГДА: Undo, черновики, checkpoints.
*/

#include <iostream>
using namespace std;

// Снимок — хранит состояние (только Draft знает что внутри)
class DraftSnapshot {
    string content;
    friend class Draft;  // Только Draft может читать/писать
public:
    DraftSnapshot() {}
};

class Draft {
    string content = "";
public:
    DraftSnapshot save() {
        DraftSnapshot m;
        m.content = content;  // Сохраняем копию
        return m;
    }
    void load(const DraftSnapshot& m) {
        content = m.content;  // Восстанавливаем
    }
    void write(const string& s) { content += s; }
    void show() { cout << "Текст: " << content << endl; }
};

int main() {
    Draft d;
    d.write("Привет");
    d.show();
    auto snap = d.save();   // Снимок
    d.write(" мир");        // Меняем
    d.show();
    d.load(snap);           // Откат
    d.show();
}
