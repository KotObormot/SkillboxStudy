#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
//#include <stdexcept> //  для ExpectionOutOfRange
#include <limits.h>  // для CHAR_BIT
#include <limits> // для std::numeric_limits
	
//#define DEBUG8 true

struct Any_room {
    std::string roomName;
    double square;
};

struct Rooms {
    int numHstd;        // номер дома
    int numFlrs;     // номер этажа
    std::string roomName;   // название
    double areaLiving; // площадь жилой комнаты
    double areaNonLiving; // площадь нежилой комнаты
};  

struct Floors {         // этажи
    int numHstd;        // номер дома
    int numberFlrs;     // номер этажа
    double ceiling;     //высота потолка           
    size_t floorMask;     
    unsigned int totalRooms;     //кол-во комнат 
};

struct Homesteads {
    int numberHst;              // номер участка
    std::string owner;          // имя собственника
    int squareHstSqM;           // площадь участка, кв.м.
    size_t roomMask;            // МАСКА УЧАСТКА согласно Room_purpose
    double squareHsSqM;         // площадь дома по периметру, кв.м.
    double areaBathhouse;        // площадь бани, кв.м
    double areaGarage;;          // площадь гаража, кв.м
    double areaPool;            // площадь бассейна, кв.м
    double areaTenCort;         // площадь корта. кв.м        
};

enum class Room_purpose{
    START,

    BedroomBig = 1,         // 0    спальная большая
    BedroomSmall = 2,       // 1    спальная поменьше
    Kitchen = 4,            // 2    кухня
    Bathroom = 8,           // 3    ванная
    Children_room = 16,     // 4    детская
    Living_room = 32,       // 5    гостиная
    Utility_room = 64,      // 6    кладовая
    Outdoor_toilet = 128,   // 7    туалет во дворе :)
    Furnace_in_House = 256, // 8    печь в доме
    Bathhouse = 512,        // 9 баня
    Furnace_in_BthHs = 1024, // 10    печь в бане
    Garage = 2048,          // 11 гараж
    Pool = 4096,            // 12 бассейн 285 sq.m
    Tennis_court = 8192,    // 13 теннсный корт 260,7569 sq.m
    One_story_house = 16384, 
    Two_storey_house = 32768,
    Three_storey_house = 65536,
    Summer_house = 131072,

    END,
};

int handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        int x{0};
        std::cin >> x;
        // Проверяем на неудачное извлечение
        if (std::cin.fail()) { // предыдущее извлечение не удалось?        
            // да, давайте разберемся с ошибкой
            std::cin.clear(); // возвращаем нас в "нормальный" режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // и удаляем неверные входные данные
            std::cout << "Oops, that input is invalid.  Please try again: ";
        }   
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; // удаляем любые посторонние входные данные
            return x;
        }
    }   
}

unsigned int count_bits(size_t x) {    //Find the number of significant bits in a number
    unsigned int count = 0;
    for (unsigned int i = 0; i < sizeof(x) * CHAR_BIT; ++i)  {
        count += (x >> i) & 1;
    }
    return count;
}

std::string print_square_any_room(const double& square) {
    std::ostringstream print_square_any_room;
    if(square == 0) {
        print_square_any_room << "  ";    
    } else if(square == 1) {
        print_square_any_room << " +";
    } else {
        print_square_any_room << std::fixed << std::setprecision(1) << square << " sq.m.";
    }
    return print_square_any_room.str();
}

int number_of_storeys(const size_t& mask) {
    int number_of_storeys;
    (mask & static_cast<size_t>(Room_purpose::One_story_house)) ? number_of_storeys = 1
     : (mask & static_cast<size_t>(Room_purpose::Two_storey_house)) ? number_of_storeys = 2 
     : (mask & static_cast<size_t>(Room_purpose::Three_storey_house)) ? number_of_storeys = 3
     : (mask & static_cast<size_t>(Room_purpose::Summer_house)) ? number_of_storeys = 1
     : number_of_storeys = 0;

    return number_of_storeys; 
}

Any_room area_of_any_room_1(const Room_purpose& purpose) {
    Any_room any_room;
    switch (purpose) {
        case Room_purpose::BedroomBig:
            any_room.roomName = "Large bedroom";
            any_room.square = (((std::rand() % 100) + 200) *.1);
            return any_room;
        case Room_purpose::BedroomSmall:
            any_room.roomName = "Small bedroom";
            any_room.square = (((std::rand() % 30) + 70) *.1);
            return any_room;
        case Room_purpose::Kitchen:
            any_room.roomName = "Kitchen";
            any_room.square = (((std::rand() % 10) + 110) *.1);
            return any_room;
        case Room_purpose::Bathroom:
            any_room.roomName = "Bathroom";
            any_room.square = (((std::rand() % 5) + 99) *.1);
            return any_room;
        case Room_purpose::Children_room:
            any_room.roomName = "Children room";
            any_room.square = (((std::rand() % 9) + 100) *.1);
            return any_room;
        case Room_purpose::Living_room:
            any_room.roomName = "Living room";
            any_room.square = (((std::rand() % 50) + 351) *.1);
            return any_room;
        case Room_purpose::Utility_room:
            any_room.roomName = "Utility room";
            any_room.square = (((std::rand() % 50) + 50) *.1);
            return any_room;
        case Room_purpose::Outdoor_toilet:
            any_room.roomName = "Outdoor toilet";
            any_room.square = 1;
            return any_room;
        case Room_purpose::Furnace_in_House:
            any_room.roomName = "Furnace in house";
            any_room.square = 1;
            return any_room;
        case Room_purpose::Furnace_in_BthHs:
            any_room.roomName = "Furnace in bathhouse";
            any_room.square = 1;
            return any_room;
        case Room_purpose::Garage:
            any_room.roomName = "Garage";
            any_room.square = ((std::rand() % 25) + 375) * .1;
            return any_room;
        case Room_purpose::Bathhouse:
            any_room.roomName = "Bathhouse";
            any_room.square = ((std::rand() % 55) + 345) * .1;
            return any_room;
        case Room_purpose::Pool:
            any_room.roomName = "Pool";
            any_room.square = ((std::rand() % 55) + 2850) * .1;
            return any_room;
        case Room_purpose::Tennis_court:
            any_room.roomName = "Tennis court";
            any_room.square = ((std::rand() % 55) + 2607) * .1;
            return any_room;
        default:
            any_room.roomName = {};
            any_room.square = 0;
            return any_room;    
    }
}

void land_planning(std::vector<Homesteads>& homestead, const int& total) {
    Homesteads hmstd;
    for(int i = 0; i < total; ++i) {
        hmstd.numberHst = i + 1;
        hmstd.owner = {};        
        hmstd.roomMask = 0;
        hmstd.squareHsSqM = 0;
        hmstd.areaBathhouse = 0;
        hmstd.areaGarage = 0;
        hmstd.areaPool = 0;
        hmstd.areaTenCort = 0;
        for (int j = 0; j < ((std::rand() % 7) + 6); ++j) {
            char letter = (char)((std::rand() % 26) + 97);
            hmstd.owner.push_back(letter);
        }
        hmstd.squareHstSqM = (std::rand() % 15000) + 600;
        if(hmstd.squareHstSqM < 700) {   // участок <7 соток  
            hmstd.roomMask = static_cast<size_t>(Room_purpose::Summer_house)
                           | static_cast<size_t>(Room_purpose::Outdoor_toilet);
        } else {
            int randomNum = ((std::rand() % 3)) + 1; // кол-во этажей
            randomNum == 1 ? hmstd.roomMask |= static_cast<size_t>(Room_purpose::One_story_house)
                           : (randomNum == 2 ? hmstd.roomMask |= static_cast<size_t>(Room_purpose::Two_storey_house)
                           : hmstd.roomMask |= static_cast<size_t>(Room_purpose::Three_storey_house));            
        }
        if(((std::rand() % 2))) {
            hmstd.roomMask |= static_cast<size_t>(Room_purpose::Garage); // гараж
            hmstd.areaGarage = area_of_any_room_1(Room_purpose::Garage).square;
        }
        if(((std::rand() % 2))) {
            hmstd.roomMask |= static_cast<size_t>(Room_purpose::Bathhouse); // баня
            hmstd.areaBathhouse = area_of_any_room_1(Room_purpose::Bathhouse).square;
            if(((std::rand() % 2))) {
                hmstd.roomMask |= static_cast<size_t>(Room_purpose::Furnace_in_BthHs); // печь в бане
            }
        }
        if(((std::rand() % 2))) {
            hmstd.roomMask |= static_cast<size_t>(Room_purpose::Furnace_in_House); // печь в доме
        }
        if(hmstd.squareHstSqM > 10000) {
            if(((std::rand() % 2))) {
                hmstd.roomMask |= static_cast<size_t>(Room_purpose::Tennis_court); // теннисный корт
                hmstd.areaTenCort = area_of_any_room_1(Room_purpose::Tennis_court).square;
            }
            if(((std::rand() % 2))) {
                hmstd.roomMask |= static_cast<size_t>(Room_purpose::Pool); // бассейн
                hmstd.areaPool = area_of_any_room_1(Room_purpose::Pool).square;
            }
        }
        homestead.push_back({hmstd});
    }
}

bool finding_room(const Room_purpose& purpose, const size_t& mask) {
    bool isRoomFound;
    static_cast<size_t>(purpose) & mask ? isRoomFound = true : isRoomFound = false;
    return isRoomFound;
}

void house_planning(const std::vector<Homesteads>& homestead, std::vector<Floors>& floor) {    
    std::vector<std::vector<size_t>> floorMaskY {{76}, {76, 2}, {76, 2, 2}};    
    for(int i = 0; i < std::size(homestead); ++i) {
        int totalFloors = number_of_storeys(homestead[i].roomMask);
        Floors flr;
        for(int j = 0; j < totalFloors; ++j) {
            flr.numHstd = homestead[i].numberHst;
            flr.numberFlrs = j + 1;
            flr.ceiling = ((std::rand() % 6) + 26) * .1;
            if(finding_room(Room_purpose::Summer_house, homestead[i].roomMask)) {
                flr.floorMask = static_cast<size_t>(Room_purpose::BedroomSmall)
                              | static_cast<size_t>(Room_purpose::Kitchen)
                              | static_cast<size_t>(Room_purpose::Utility_room);
            } else {
                flr.floorMask = floorMaskY[number_of_storeys(homestead[i].roomMask) - 1][j];
                flr.floorMask |= (std::rand() % 2) * static_cast<size_t>(Room_purpose::BedroomBig) 
                               | (std::rand() % 2) * static_cast<size_t>(Room_purpose::BedroomSmall)
                               | (std::rand() % 2) * static_cast<size_t>(Room_purpose::Bathroom)
                               | (std::rand() % 2) * static_cast<size_t>(Room_purpose::Children_room)
                               | (std::rand() % 2) * static_cast<size_t>(Room_purpose::Living_room);
            }
            flr.totalRooms = count_bits(flr.floorMask);
            floor.push_back({flr});
        }
    }
}

void room_planning(std::vector<Homesteads>& homestead, const std::vector<Floors>& floor, std::vector<Rooms>& rooms) {    
    Rooms rms;
    int jPos = 0;
    int totalFloors = 0;
    for(int k = 0; k < homestead.size(); ++k) {     // homestead
        totalFloors += number_of_storeys(homestead[k].roomMask);    
        while(jPos < totalFloors) {
            for(int j = jPos; j < totalFloors; ++j) {   //floor
                for(size_t i = static_cast<size_t>(Room_purpose::START) + 1; i < static_cast<size_t>(Room_purpose::END); i = i << 1) {                
                    Room_purpose purpose_of_room = static_cast<Room_purpose>(static_cast<size_t>(i));
                    if(finding_room(purpose_of_room, floor[j].floorMask)) {
                        std::string roomName {};
                        rms.numHstd = homestead[k].numberHst;
                        rms.numFlrs = floor[j].numberFlrs;
                        rms.roomName = area_of_any_room_1(purpose_of_room).roomName;
                        if(static_cast<size_t>(purpose_of_room) & (static_cast<size_t>(Room_purpose::BedroomBig) | static_cast<size_t>(Room_purpose::BedroomSmall)
                                             | static_cast<size_t>(Room_purpose::Children_room) | static_cast<size_t>(Room_purpose::Living_room))) {
                            rms.areaLiving = area_of_any_room_1(purpose_of_room).square;
                            rms.areaNonLiving = 0;
                        } else {
                            rms.areaLiving = 0;
                            rms.areaNonLiving = area_of_any_room_1(purpose_of_room).square;
                        }
                        rooms.push_back({rms});
                    }            
                }                
            }
            jPos += number_of_storeys(homestead[k].roomMask);
        }
    }
    int sumFloors = 0;
    int jFloor = 0;
    int sumRooms {0};
    int kRoom {0};   
    for(int i = 0; i < std::size(homestead); ++i) {
        double areaHouseLiving {0};
        double areaHouseNonLiving {0};
        sumFloors += number_of_storeys(homestead[i].roomMask);
        while(jFloor < sumFloors) {
            for(int j = jFloor; j < sumFloors; ++j) {
                double areaFloorLiving {0};
                double areaFloorNonLiving {0};
                sumRooms += floor[j].totalRooms;
                while(kRoom < sumRooms) { 
                    for(int k = kRoom; k < sumRooms; ++k) {
                        areaFloorLiving += rooms[k].areaLiving;
                        areaFloorNonLiving += rooms[k].areaNonLiving;
                    }
                    kRoom += floor[j].totalRooms;
                }
                areaHouseLiving += areaFloorLiving;
                areaHouseNonLiving += areaFloorNonLiving;
                if(floor[j].numberFlrs == 1) {
                    homestead[i].squareHsSqM = areaFloorLiving + areaFloorNonLiving;
                }
            }
            jFloor += number_of_storeys(homestead[i].roomMask);
        }        
    }    
}

void print_village(std::vector<Homesteads>& homestead, std::vector<Floors>& floor) {
    std::cout << "===============PARAMETERS OF HOMESTEADS OF THE VILLAGE===================\n";
    std::cout << std::setw(3) << "No" << std::setw(14) << "OWNER" << std::setw(9) << "AREA"
              << std::setw(20) << "AofH*" << std::setw(7) << "Floors"
              << std::setw(10) << "Bathhouse" << std::setw(3) << "+Furnace" << std::setw(8) << "Garage"
              << std::setw(25) << "Furnace in the house"
              << std::setw(5) << "Pool"
              << std::setw(21) << "Tennis court"
              << std::setw(15) << "Outdoor toilet"
              << "\n";    
    for(int i = 0; i < std::size(homestead); ++i) {        
        std::cout << std::setw(3) << homestead[i].numberHst << ")" 
                  << std::setw(13) << homestead[i].owner << ": "
                  << std::setprecision(2) << ((double)(homestead[i].squareHstSqM)) / 10000 << " ha"
                  << std::setw(20) << print_square_any_room(homestead[i].squareHsSqM)
                  << std::setw(5) << number_of_storeys(homestead[i].roomMask)
                  << std::setw(14)
                  << print_square_any_room(homestead[i].areaBathhouse)
                  << print_square_any_room(area_of_any_room_1(Room_purpose::Furnace_in_BthHs).square * finding_room(Room_purpose::Furnace_in_BthHs, homestead[i].roomMask))
                  << std::setw(16)
                  << print_square_any_room(homestead[i].areaGarage)
                  << std::setw(7)
                  << print_square_any_room(area_of_any_room_1(Room_purpose::Furnace_in_House).square * finding_room(Room_purpose::Furnace_in_House, homestead[i].roomMask))
                  << std::setw(26)
                  << print_square_any_room(homestead[i].areaPool)
                  << std::setw(14)
                  << print_square_any_room(homestead[i].areaTenCort)
                  << std::setw(10)
                  << print_square_any_room(area_of_any_room_1(Room_purpose::Outdoor_toilet).square * finding_room(Room_purpose::Outdoor_toilet, homestead[i].roomMask))
                  << "\n";
    }
    std::cout << "\n--------------------------------------------------\n"
              << "*Note: AofH is occupied area of ​​the house along the perimeter\n";
}

void print_house(const std::vector<Homesteads>& homestead, const std::vector<Floors>& floor, const std::vector<Rooms>& rooms, const int number) {
    int sumFloors = 0;
    int jFloor = 0;
    int sumRooms {0};
    int kRoom {0};   
    for(int i = 0; i < std::size(homestead); ++i) {
        double areaHouseLiving {0};
        double areaHouseNonLiving {0};
        if(i == number - 1) {
            std::cout << std::setw(36) << "Homestead plan #" << number << "\n"
                      << std::setw(7) << "Owner: " << homestead[i].owner 
                      << std::setw(7) << "Area " << std::setprecision(2) << ((double)(homestead[i].squareHstSqM) / 10000) << " ha.\n"
                      << "============================================================\n"
                      << std::setw(8) << "*** House\n";            
            if(finding_room(Room_purpose::Furnace_in_House, homestead[i].roomMask)) {
                std::cout << std::setw(19) << area_of_any_room_1(Room_purpose::Furnace_in_House).roomName << "\n";
            }
        }
        sumFloors += number_of_storeys(homestead[i].roomMask);
        while(jFloor < sumFloors) {
            for(int j = jFloor; j < sumFloors; ++j) {
                double areaFloorLiving {0};
                double areaFloorNonLiving {0};
                sumRooms += floor[j].totalRooms;
                if(i == number - 1) {
                    std::cout  
                            << std::setw(9)  << floor[j].numberFlrs << ".floor: "
                            << std::setw(3) << floor[j].totalRooms << " rooms, "
                            << std::setw(5) << "Ceiling = " << std::setprecision(1) << floor[j].ceiling << " m"
                            << "\n";
                }
                while(kRoom < sumRooms) { 
                    for(int k = kRoom; k < sumRooms; ++k) {
                        areaFloorLiving += rooms[k].areaLiving;
                        areaFloorNonLiving += rooms[k].areaNonLiving;
                        if(i == number - 1) {
                            std::cout << std::setw(30) << rooms[k].roomName
                                    << " " << print_square_any_room(rooms[k].areaLiving + rooms[k].areaNonLiving) << "\n";
                        }
                    }
                    kRoom += floor[j].totalRooms;                    
                    if(i == number - 1) {
                        std::cout << std::setw(50) << "--------------------\n"
                                  << std::setw(50) << "Living floor area " << print_square_any_room(areaFloorLiving) << "\n"
                                  << std::setw(50) << "Non-residential area " << print_square_any_room(areaFloorNonLiving) << "\n"
                                  << std::setw(50) << "Total floor area " << print_square_any_room(areaFloorLiving + areaFloorNonLiving)
                                  << "\n";                                  
                    }
                }
                areaHouseLiving += areaFloorLiving;
                areaHouseNonLiving += areaFloorNonLiving;
            }
            jFloor += number_of_storeys(homestead[i].roomMask);
        }
        if(i == number - 1) {
            std::cout << "*************************************\n"
                      << std::setw(42) << "Living area of ​​the house " << print_square_any_room(areaHouseLiving) << "\n"
                      << std::setw(42) << "Non-residential area of ​​the house " << print_square_any_room(areaHouseNonLiving) << "\n"
                      << std::setw(42) << "Total area of ​​the house " << print_square_any_room(areaHouseLiving + areaHouseNonLiving) << "\n"
                      << std::setw(36) << "House perimeter area " << print_square_any_room(homestead[i].squareHsSqM) << "\n"
                      << "============================================================\n";
            if(finding_room(Room_purpose::Bathhouse, homestead[i].roomMask)) {
                std::cout << "*** " << area_of_any_room_1(Room_purpose::Bathhouse).roomName << " "
                          << print_square_any_room(homestead[i].areaBathhouse);
                if(finding_room(Room_purpose::Furnace_in_BthHs, homestead[i].roomMask)) {
                    std::cout << " and " << area_of_any_room_1(Room_purpose::Furnace_in_BthHs).roomName;
                }
                std::cout << "\n";
            }
            if(finding_room(Room_purpose::Outdoor_toilet, homestead[i].roomMask)) {
                std::cout << "*** " << area_of_any_room_1(Room_purpose::Outdoor_toilet).roomName << "\n";
            }
            if(finding_room(Room_purpose::Garage, homestead[i].roomMask)) {
                std::cout << "*** " << area_of_any_room_1(Room_purpose::Garage).roomName << " "
                          << print_square_any_room(homestead[i].areaGarage) << "\n";
            }
            if(finding_room(Room_purpose::Pool, homestead[i].roomMask)) {
                std::cout << "*** " << area_of_any_room_1(Room_purpose::Pool).roomName << " "
                          << print_square_any_room(homestead[i].areaPool) << "\n";
            }
            if(finding_room(Room_purpose::Tennis_court, homestead[i].roomMask)) {
                std::cout << "*** " << area_of_any_room_1(Room_purpose::Tennis_court).roomName << " "
                          << print_square_any_room(homestead[i].areaTenCort) << "\n";
            }

        }
    }    
}

int main() {
    std::cout << "Hello\n";
    std::srand(std::time(nullptr));
    std::cout.setf(std::ios::fixed);
    int totalHmstds {0};
    std::cout << "The distribution of plots is done by artificial intelligence ChatGPT based on random numbers )))\n"
              << "Enter the total number of plots";
    totalHmstds = handling_invalid_input();
    std::vector<Homesteads> homestead;
    land_planning(homestead, totalHmstds);

    std::vector<Floors> floor;
    house_planning(homestead, floor);

    std::vector<Rooms> rooms;
    room_planning(homestead, floor, rooms);

    char choice {};
    while(choice != 'q') {
        std::cout << "Enter the operating mode please:\n";
        std::cout << "< Display a plan of the entire village / h Show a detailed plan of any homestead / q End work ";        
        std::cin.clear();        
        std::cin >> choice;
        if(choice == '<') {
            print_village(homestead, floor);
        } else if (choice == 'h') {
            std::cout << "Enter the plot number";
            int homesteadNumber = handling_invalid_input();
            print_house(homestead, floor, rooms, homesteadNumber);
        }
    }
    return 0;
}