#include <iostream>
#include "executor.h"

int main() {
    while (!Executor::instance()->isExit())
    {
        try {
            Executor::instance()->execute();
        }
        catch (std::exception &e) {
            std::cout << e.what() << "\n";
        }
        catch(...){
            std::cout << "Error: an error has occurred!\n";
        }
    }
    return 0;
}
