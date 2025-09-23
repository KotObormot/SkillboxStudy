#include "laguna.h"
#include "lagunaException.h"

size_t NUMBER_OF_SECTORS(9);
size_t NUMBER_OF_FISH(1);
size_t NUMBER_OF_BOOTS(3);

Laguna::Laguna() {
    for(size_t i(0); i < NUMBER_OF_SECTORS; ++i) {
        laguna.emplace_back(0);
    }

    std::srand(std::time(nullptr));
    //===== Releasing fish into the laguna. ======\n";
    for(size_t j(0); j < NUMBER_OF_FISH; ++j) {
        for(size_t i(0); i < laguna.size(); ++i) {
            size_t sector(std::rand() % NUMBER_OF_SECTORS);
            if(laguna.at(sector) != 0) {
                continue;
            } else {
                laguna.at(sector) = 1;
                break;
            }
        }
    }

    //======== Drowning boots in water. ===========\n";
    for(size_t boot(0); boot < NUMBER_OF_BOOTS; ++boot) {
        for(size_t i(0); i < laguna.size(); ++i) {
            size_t sector(std::rand() % NUMBER_OF_SECTORS);
            if(laguna.at(sector) != 0) {
                continue;
            } else {
                laguna.at(sector) = 2;
                break;
            }
        }
    }
    std::cout << "\n======== All is ready for fishing! ===========\n";
}

void Laguna::fishing() {
    /*size_t*/ int nAttempts(0);
    while(true) {
        std::cout << "Sector";
        size_t i(handlingInput());
        ++nAttempts;  // <-- AI

        int haul(0);

        try{
            haul = laguna.at(i);
            if(haul == 1) {
                throw FishException("Congratulations! The fish was caught.", nAttempts);
            } else if(haul == 2) {
                throw BootException{"Sorry, you caught the boot."};
            }
        }
//          catch(std::out_of_range e) {        — передача исключения по значению
//                                              Это может вызвать object slicing. Надо передавать по ссылке: AI
        catch(const std::out_of_range e) {
            std::cout /*<< "Error. (Code: " << e.what() << ") - "*/ << "Past the lagoon! Try again!\n";
        }
        catch(const FishException& ex) {
//            laguna.at(i) = 0;                     For the future
            std::cout << ex.what() << "\n";
            ex.getAttempts();            
            break;
        }
        catch(const BootException& ex) {
//            laguna.at(i) = 0;                     For the future
            std::cout << ex.what() << "\n";
            break;
        }

        std::cout << "Nothing caught. Let's keep fishing" << "\n";
//            ++nAttempts;
    }
}

void Laguna::print() {
    for(size_t i(0); i < laguna.size(); ++i) {
        std::string whatIsThere(laguna.at(i) == 1 ? "Fish" 
                            : (laguna.at(i) == 2 ? "Boot" : "")) ;
        std::cout << "Sector " << i << ":\t" << whatIsThere << "\n";
    }
}