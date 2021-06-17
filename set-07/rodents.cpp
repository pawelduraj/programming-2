#include <iostream>
#include <vector>

class Rodent {
public:
    virtual void printName() = 0;

    virtual void printMultilineName() = 0;

    virtual ~Rodent() = default;
};

class Mouse : public Rodent {
public:
    void printName() override {
        std::cout << "mouse" << std::endl;
    }

    void printMultilineName() override {
        std::cout << " _ __ ___   ___  _   _ ___  ___\n"
                     "| '_ ` _ \\ / _ \\| | | / __|/ _ \\\n"
                     "| | | | | | (_) | |_| \\__ \\  __/\n"
                     "|_| |_| |_|\\___/ \\__,_|___/\\___|\n\n";
    }

    ~Mouse() override {
        std::cout << "mouse destruction" << std::endl;
    }
};

class Gerbil : public Rodent {
public:
    void printName() override {
        std::cout << "gerbil" << std::endl;
    }

    void printMultilineName() override {
        std::cout << "                 _     _ _\n"
                     "                | |   (_) |\n"
                     "  __ _  ___ _ __| |__  _| |\n"
                     " / _` |/ _ \\ '__| '_ \\| | |\n"
                     "| (_| |  __/ |  | |_) | | |\n"
                     " \\__, |\\___|_|  |_.__/|_|_|\n"
                     "  __/ |\n"
                     " |___/\n\n";
    }

    ~Gerbil() override {
        std::cout << "gerbil destruction" << std::endl;
    }
};

class Hamster : public Rodent {
public:
    void printName() override {
        std::cout << "hamster" << std::endl;
    }

    void printMultilineName() override {
        std::cout << " _                         _\n"
                     "| |                       | |\n"
                     "| |__   __ _ _ __ ___  ___| |_ ___ _ __\n"
                     "| '_ \\ / _` | '_ ` _ \\/ __| __/ _ \\ '__|\n"
                     "| | | | (_| | | | | | \\__ \\ ||  __/ |\n"
                     "|_| |_|\\__,_|_| |_| |_|___/\\__\\___|_|\n\n";
    }

    ~Hamster() override {
        std::cout << "hamster destruction" << std::endl;
    }
};

class BlueHamster : public Hamster {
public:
    void printName() override {
        std::cout << "blue hamster" << std::endl;
    }

    void printMultilineName() override {
        std::cout << " _     _              _                         _\n"
                     "| |   | |            | |                       | |\n"
                     "| |__ | |_   _  ___  | |__   __ _ _ __ ___  ___| |_ ___ _ __\n"
                     "| '_ \\| | | | |/ _ \\ | '_ \\ / _` | '_ ` _ \\/ __| __/ _ \\ '__|\n"
                     "| |_) | | |_| |  __/ | | | | (_| | | | | | \\__ \\ ||  __/ |\n"
                     "|_.__/|_|\\__,_|\\___| |_| |_|\\__,_|_| |_| |_|___/\\__\\___|_|\n\n";
    }

    ~BlueHamster() override {
        std::cout << "blue hamster destruction" << std::endl;
    }
};

int main() {

    std::vector<Rodent *> rodents;
    for (int i = 0; i < 8; i++) {
        if (i % 4 == 0) rodents.push_back(new Mouse());
        else if (i % 4 == 1) rodents.push_back(new Gerbil());
        else if (i % 4 == 2) rodents.push_back(new Hamster());
        else rodents.push_back(new BlueHamster());
    }

    for (auto const& rodent : rodents)
        rodent->printName();

    for (auto const& rodent : rodents)
        rodent->printMultilineName();

    for (auto const& rodent : rodents)
        delete rodent;

    return 0;
}
