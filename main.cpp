#include <iostream>
#include "inc/executor.h"

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
            std::cout << "Error: an error has occured!\n";
        }
    }
    return 0;
}
