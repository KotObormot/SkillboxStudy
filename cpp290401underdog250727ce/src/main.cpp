#include "common.h"
#include "loclib.h"
#include "talent.h"
#include "dog.h"

#define DEBUG true

int main() {
    std::cout << "Hello!\n";
    std::cout << "What is your dog's name?--> ";
    std::string name;
    getline(std::cin, name);
    Dog dog(name);

    Talent* talent;
    
    Barking* barking(new Barking);
    talent = barking;
    dog.setTalent(talent);
    Running* running(new Running);
    talent = running;
    dog.setTalent(talent);
    
    Swimming* swimming(new Swimming);
    Dancing* dancing(new Dancing);
    Counting* counting(new Counting);

    std::string talentTMP("");
    while(true) {
        std::cout << "Enter your pet's new talent or CLOSE to finish--> ";
        talentTMP = correctCommandInput();

        while(talentTMP != "swimming"
                && talentTMP != "dancing"
                && talentTMP != "counting"
                && talentTMP != "close") {        
            std::cout << "ERROR: There is no such talent. Try again--> ";
            talentTMP = correctCommandInput();        
        }

        if(talentTMP == "swimming") {
            talent = swimming;
        } else if(talentTMP == "dancing") {
            talent = dancing;
        } else if(talentTMP == "counting") {
            talent = counting;
        } else if(talentTMP == "close") {
            std::cout << "The list of talents is exhausted!" << "\n";
            break;
        }
        
        dog.setTalent(talent);
        std::cout << "Talent \"" << talent->getTalent() << "\" added.\n";
    }

    dog.show_talents();

    delete barking;
    delete swimming;
    delete dancing;
    delete counting;

    return 0;
}