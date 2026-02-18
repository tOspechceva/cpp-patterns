#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>

// ==================== ИНТЕРФЕЙС ПРОДУКТА ====================

// Общий интерфейс для всех видов транспорта
class Transport {
public:
    virtual void deliver() = 0;
    virtual ~Transport() = default;
};

// ==================== КОНКРЕТНЫЕ ПРОДУКТЫ ====================

// Грузовик - перевозит грузы по земле
class Truck : public Transport {
public:
    void deliver() override {
        std::cout << "Грузовик доставляет груз по земле 🚛" << std::endl;
    }
};

// Судно - перевозит грузы по морю
class Ship : public Transport {
public:
    void deliver() override {
        std::cout << "Судно доставляет груз по морю 🚢" << std::endl;
    }
};

// ==================== СОЗДАТЕЛЬ (ФАБРИКА) ====================

// Абстрактный класс логистики с фабричным методом
class Logistics {
public:
    // Фабричный метод - создаёт транспорт
    virtual Transport* createTransport() = 0;
    
    // Основная бизнес-логика (использует фабричный метод)
    void planDelivery() {
        Transport* transport = createTransport();
        std::cout << "Планирование доставки..." << std::endl;
        transport->deliver();
        delete transport;
    }
    
    virtual ~Logistics() = default;
};

// ==================== КОНКРЕТНЫЕ СОЗДАТЕЛИ ====================

// Дорожная логистика - создаёт грузовики
class RoadLogistics : public Logistics {
public:
    Transport* createTransport() override {
        std::cout << "Создаём грузовик для наземной доставки" << std::endl;
        return new Truck();
    }
};

// Морская логистика - создаёт суда
class SeaLogistics : public Logistics {
public:
    Transport* createTransport() override {
        std::cout << "Создаём судно для морской доставки" << std::endl;
        return new Ship();
    }
};

// ==================== КЛИЕНТСКИЙ КОД ====================

// Функция создания логистики на основе типа доставки
Logistics* createLogistics(const std::string& deliveryType) {
    if (deliveryType == "road") {
        return new RoadLogistics();
    } else if (deliveryType == "sea") {
        return new SeaLogistics();
    }
    // По умолчанию - дорожная логистика
    return new RoadLogistics();
}

// ==================== MAIN ====================

int main() {
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    std::cout << "=== СИСТЕМА УПРАВЛЕНИЯ ГРУЗОПЕРЕВОЗКАМИ ===" << std::endl;
    std::cout << std::endl;
    
    // Пример 1: Дорожная доставка
    std::cout << "--- Заказ №1: Наземная доставка ---" << std::endl;
    Logistics* roadLogistics = createLogistics("road");
    roadLogistics->planDelivery();
    delete roadLogistics;
    std::cout << std::endl;
    
    // Пример 2: Морская доставка
    std::cout << "--- Заказ №2: Морская доставка ---" << std::endl;
    Logistics* seaLogistics = createLogistics("sea");
    seaLogistics->planDelivery();
    delete seaLogistics;
    std::cout << std::endl;
    
    // Пример 3: Прямое создание конкретных фабрик
    std::cout << "--- Заказ №3: Прямое создание фабрики ---" << std::endl;
    RoadLogistics* directRoad = new RoadLogistics();
    directRoad->planDelivery();
    delete directRoad;
    std::cout << std::endl;
    
    // Пример 4: Демонстрация расширяемости
    std::cout << "--- Добавление нового типа транспорта ---" << std::endl;
    std::cout << "Чтобы добавить авиадоставку, нужно:" << std::endl;
    std::cout << "1. Создать класс Airplane (наследник Transport)" << std::endl;
    std::cout << "2. Создать класс AirLogistics (наследник Logistics)" << std::endl;
    std::cout << "3. Переопределить createTransport() для создания Airplane" << std::endl;
    std::cout << "4. Клиентский код НЕ МЕНЯЕТСЯ!" << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== ВСЕ ЗАКАЗЫ ВЫПОЛНЕНЫ ===" << std::endl;
    
    return 0;
}