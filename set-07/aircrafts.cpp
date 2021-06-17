#include <iostream>
#include <vector>

class Aircraft {
private:
    std::string name;
    bool isInTheAir;
    int currentFuel, maxFuel;

public:
    Aircraft(const std::string &name, int currentFuel, int maxFuel) {
        this->name = name;
        this->isInTheAir = false;
        this->currentFuel = currentFuel;
        this->maxFuel = maxFuel;
    }

    std::string getName() {
        return name;
    }

    int getCurrentFuel() const {
        return currentFuel;
    }

    int getMaxFuel() const {
        return maxFuel;
    }

    bool isAtTheAirport() const {
        return !isInTheAir;
    }

    void setCurrentFuel(int fuel) {
        currentFuel = fuel;
        if (currentFuel < 0) currentFuel = 0;
        if (currentFuel > maxFuel) currentFuel = maxFuel;
    }

    void takeoff() {
        isInTheAir = true;
    }

    void land() {
        isInTheAir = false;
    }

    virtual bool shouldLand() = 0;

    virtual void fly() = 0;

    virtual void refuel() = 0;

    virtual std::string getFullName() = 0;

    virtual ~Aircraft() = default;
};

class Fighter : public Aircraft {
public:
    explicit Fighter(const std::string &name, int currentFuel, int maxFuel) : Aircraft(name, currentFuel, maxFuel) {}

    bool shouldLand() override {
        return getCurrentFuel() < 3;
    }

    void fly() override {
        setCurrentFuel(getCurrentFuel() - 2);
    }

    void refuel() override {
        setCurrentFuel(getCurrentFuel() + 4);
    }

    std::string getFullName() override {
        return "Fighter " + getName();
    }

    ~Fighter() override {
        std::cout << "fighter destruction" << std::endl;
    }
};

class Bomber : public Aircraft {
public:
    explicit Bomber(const std::string &name, int currentFuel, int maxFuel) : Aircraft(name, currentFuel, maxFuel) {}

    bool shouldLand() override {
        return getCurrentFuel() < 5;
    }

    void fly() override {
        setCurrentFuel(getCurrentFuel() - 4);
    }

    void refuel() override {
        setCurrentFuel(getCurrentFuel() + 2);
    }

    std::string getFullName() override {
        return "Bomber " + getName();
    }

    ~Bomber() override {
        std::cout << "bomber destruction" << std::endl;
    }
};

class Tower {
private:
    std::vector<Aircraft *> aircrafts;

public:
    void run(int rounds) {
        for (int i = 0; i < rounds; i++) {
            for (auto const &aircraft : aircrafts) {
                if (!aircraft->isAtTheAirport() && aircraft->shouldLand()) {
                    aircraft->land();
                    std::cout << aircraft->getFullName() << " has landed";
                } else if (aircraft->isAtTheAirport() && aircraft->getCurrentFuel() == aircraft->getMaxFuel()) {
                    aircraft->takeoff();
                    std::cout << aircraft->getFullName() << " has taken off";
                } else {
                    std::cout << aircraft->getFullName() << " ";
                    std::cout << (aircraft->isAtTheAirport() ? "is at the airport" : "is in the air");
                }
                std::cout << ". Fuel " << aircraft->getCurrentFuel() << "/" << aircraft->getMaxFuel() << std::endl;
            }
            for (auto const &aircraft : aircrafts) {
                if (aircraft->isAtTheAirport()) aircraft->refuel();
                else aircraft->fly();
            }
        }
    }

    void add(Aircraft *aircraft) {
        aircrafts.push_back(aircraft);
    }

    ~Tower() {
        for (auto const& aircraft : aircrafts)
            delete aircraft;
    }
};

int main() {

    std::vector<Aircraft *> aircrafts;
    aircrafts.push_back(new Fighter("F-16", 10, 10));
    aircrafts.push_back(new Bomber("B-16", 30, 30));
    aircrafts.push_back(new Fighter("MiG-17", 12, 12));

    auto tower = new Tower();
    for (auto const &aircraft : aircrafts)
        tower->add(aircraft);

    tower->run(15);
    delete tower;

    return 0;
}
