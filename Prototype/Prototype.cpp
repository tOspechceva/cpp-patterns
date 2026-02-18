// ==================== ИНТЕРФЕЙС ПРОТОТИПА ====================

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <Windows.h>

// Базовый интерфейс для всех прототипов
class Prototype {
public:
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void showInfo() const = 0;
    virtual ~Prototype() = default;
};

// ==================== КОНКРЕТНЫЕ ПРОТОТИПЫ (ФИГУРЫ) ====================

// Круг
class Circle : public Prototype {
private:
    int radius;
    std::string color;
    int x, y; // координаты центра
    
public:
    Circle(int r = 0, const std::string& c = "white", int posX = 0, int posY = 0)
        : radius(r), color(c), x(posX), y(posY) {}
    
    // Копирующий конструктор (нужен для clone)
    Circle(const Circle& other) 
        : radius(other.radius), color(other.color), x(other.x), y(other.y) {}
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Circle>(*this);
    }
    
    void showInfo() const override {
        std::cout << "Круг: радиус=" << radius 
                  << ", цвет=" << color 
                  << ", позиция=(" << x << "," << y << ")" << std::endl;
    }
    
    // Геттеры и сеттеры
    void setRadius(int r) { radius = r; }
    void setColor(const std::string& c) { color = c; }
    void setPosition(int posX, int posY) { x = posX; y = posY; }
    int getRadius() const { return radius; }
};

// Прямоугольник
class Rectanglee : public Prototype {
private:
    int width, height;
    std::string color;
    int x, y; // координаты левого верхнего угла
    
public:
    Rectanglee(int w = 0, int h = 0, const std::string& c = "white", int posX = 0, int posY = 0)
        : width(w), height(h), color(c), x(posX), y(posY) {}
    
    Rectanglee(const Rectanglee& other)
        : width(other.width), height(other.height), color(other.color), x(other.x), y(other.y) {}
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<Rectanglee>(*this);
    }
    
    void showInfo() const override {
        std::cout << "Прямоугольник: " << width << "x" << height 
                  << ", цвет=" << color 
                  << ", позиция=(" << x << "," << y << ")" << std::endl;
    }
    
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setColor(const std::string& c) { color = c; }
    void setPosition(int posX, int posY) { x = posX; y = posY; }
};

// ==================== РЕЕСТР ПРОТОТИПОВ ====================

class PrototypeRegistry {
private:
    std::map<std::string, std::unique_ptr<Prototype>> prototypes;
    
public:
    // Регистрация прототипа
    void registerPrototype(const std::string& name, std::unique_ptr<Prototype> proto) {
        prototypes[name] = std::move(proto);
        std::cout << "Зарегистрирован прототип: " << name << std::endl;
    }
    
    // Создание копии прототипа
    std::unique_ptr<Prototype> createFromPrototype(const std::string& name) {
        auto it = prototypes.find(name);
        if (it != prototypes.end()) {
            std::cout << "Создаём копию из прототипа: " << name << std::endl;
            return it->second->clone();
        }
        std::cout << "Прототип не найден: " << name << std::endl;
        return nullptr;
    }
    
    // Показать все зарегистрированные прототипы
    void showAllPrototypes() const {
        std::cout << "\n=== ЗАРЕГИСТРИРОВАННЫЕ ПРОТОТИПЫ ===" << std::endl;
        for (const auto& pair : prototypes) {
            std::cout << "Имя: " << pair.first << " -> ";
            pair.second->showInfo();
        }
        std::cout << "=====================================\n" << std::endl;
    }
};

// ==================== КЛИЕНТСКИЙ КОД ====================

// Функция, работающая с любым прототипом (не знает конкретный класс)
void processShape(const std::unique_ptr<Prototype>& shape) {
    std::cout << "Обработка фигуры: ";
    shape->showInfo();
}

// Функция создания множества объектов из прототипа
void createMultipleShapes(PrototypeRegistry& registry, const std::string& protoName, int count) {
    std::cout << "\n=== Создаём " << count << " копий из прототипа '" << protoName << "' ===" << std::endl;
    
    for (int i = 1; i <= count; i++) {
        auto shape = registry.createFromPrototype(protoName);
        if (shape) {
            // Модифицируем копию (например, меняем позицию)
            if (auto circle = dynamic_cast<Circle*>(shape.get())) {
                circle->setPosition(i * 10, i * 10);
            } else if (auto rect = dynamic_cast<Rectanglee*>(shape.get())) {
                rect->setPosition(i * 15, i * 15);
            }
            shape->showInfo();
        }
    }
}

// ==================== MAIN ====================

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    // Создаём реестр прототипов
    PrototypeRegistry registry;
    
    // === ИНИЦИАЛИЗАЦИЯ: создаём и настраиваем прототипы ===
    std::cout << "--- Этап инициализации: создаём прототипы ---\n" << std::endl;
    
    // Прототип красного круга
    auto redCircle = std::make_unique<Circle>(50, "красный", 0, 0);
    registry.registerPrototype("red_circle", std::move(redCircle));
    
    // Прототип синего круга
    auto blueCircle = std::make_unique<Circle>(30, "синий", 0, 0);
    registry.registerPrototype("blue_circle", std::move(blueCircle));
    
    // Прототип зелёного прямоугольника
    auto greenRect = std::make_unique<Rectanglee>(100, 50, "зелёный", 0, 0);
    registry.registerPrototype("green_rectangle", std::move(greenRect));
    
    // Прототип большого квадрата
    auto bigSquare = std::make_unique<Rectanglee>(200, 200, "жёлтый", 0, 0);
    registry.registerPrototype("big_square", std::move(bigSquare));
    
    // Показываем все прототипы
    registry.showAllPrototypes();
    
    // === ИСПОЛЬЗОВАНИЕ: создаём объекты из прототипов ===
    std::cout << "--- Этап использования: клонируем прототипы ---\n" << std::endl;
    
    // Создаём несколько кругов из прототипа
    createMultipleShapes(registry, "red_circle", 3);
    
    // Создаём несколько прямоугольников из прототипа
    createMultipleShapes(registry, "green_rectangle", 2);
    
    // === ПРИМЕР: работа с объектами через общий интерфейс ===
    std::cout << "\n=== Работа через общий интерфейс Prototype ===" << std::endl;
    
    auto shape1 = registry.createFromPrototype("blue_circle");
    auto shape2 = registry.createFromPrototype("big_square");
    
    std::cout << "\nОбе фигуры обрабатываются одинаково:" << std::endl;
    processShape(shape1);
    processShape(shape2);
    
    // === ПРИМЕР: модификация клона без влияния на прототип ===
    std::cout << "\n=== Демонстрация независимости клонов ===" << std::endl;
    
    auto original = registry.createFromPrototype("red_circle");
    auto clone = original->clone();
    
    std::cout << "\nОригинал:" << std::endl;
    original->showInfo();
    
    std::cout << "\nКлон до изменений:" << std::endl;
    clone->showInfo();
    
    // Модифицируем клон
    if (auto circleClone = dynamic_cast<Circle*>(clone.get())) {
        circleClone->setRadius(100);
        circleClone->setColor("фиолетовый");
        circleClone->setPosition(500, 500);
    }
    
    std::cout << "\nКлон после изменений:" << std::endl;
    clone->showInfo();
    
    std::cout << "\nОригинал остался неизменным:" << std::endl;
    original->showInfo();
    
    
    return 0;
}