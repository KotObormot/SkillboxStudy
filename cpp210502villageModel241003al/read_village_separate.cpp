#include <fstream>
#include <iostream>
#include <vector>
#include <string>
//#include <ctime>
//#include <sstream>
#include <iomanip>
//#include <limits.h>  // для CHAR_BIT
#include <limits> // для std::numeric_limits
//#include <cstdlib>
#define DEBUG1 false
#define DEBUG2 true // bool isFurnace
#define DEBUG3 false // bit isFurnace
#define DEBUG4 true //печать промежуточных переменных
#define DEBUG5 true // with Serialization
#define DEBUG6 false // without Serialization
#define DEBUG7 true // char name
#define DEBUG8 false // string name
#define DEBUG9 true
#define DEBUG10 false
#define DEBUG12 true // write to separate files in reverse order
#define DEBUG13 false // write to a single file in direct order
#define DEBUG14 false // reading from file village

std::string ordinal_number(const int number) {
    std::string ordinal_number {};
    switch (number) {
        case 1:
            ordinal_number = " 1st ";
            return ordinal_number;
        case 2:
            ordinal_number = " 2nd ";
            return ordinal_number;
        case 3:
            ordinal_number = " 3rd ";
            return ordinal_number;
        default:
            ordinal_number = " " + std::to_string(number) + "st ";
            return ordinal_number;
    }
}

enum class Room{
    START,

    Hallway = 1,             // 0    прихожая
    Bedroom = 2,            // 1    спальная 
    Kitchen = 4,            // 2    кухня
    Bathroom = 8,           // 3    ванная
    Children_room = 16,     // 4    детская
    Living_room = 32,       // 5    гостиная
    Utility_room = 64,      // 6    кладовая / гардеробная

    END,
};

std::string room_name(const Room& rms) {
    std::string roomName {};
    switch (rms) {
        case Room::Bathroom:
            roomName = "Bathroom";
            return roomName;
        case Room::Bedroom:
            roomName = "Bedroom";
            return roomName;
        case Room::Children_room:
            roomName = "Children room";
            return roomName;
        case Room::Hallway:
            roomName = "Hallway";
            return roomName;
        case Room::Kitchen:
            roomName = "Kitchen";
            return roomName;
        case Room::Living_room:
            roomName = "Living room";
            return roomName;
        case Room::Utility_room:
            roomName = "Utility room";
            return roomName;
        default:
            return roomName;
    }
}

enum class Buildings{
    START, 
    
    Garage = 1,          // 0   гараж
    Pool = 2,            // 1 бассейн 285 sq.m
    Tennis_court = 4,    // 2 теннсный корт 260,7569 sq.m
    Pigsty = 8,           // 3 
    Chicken_coop = 16,      // 4
    
    END,
};

std::string building_name(const Buildings& bldngs) {
    std::string buildingName {};
    switch (bldngs) {
        case Buildings::Garage:
            buildingName = "Garage";
            return buildingName;
        case Buildings::Pool:
            buildingName = "Pool";
            return buildingName;
        case Buildings::Tennis_court:
            buildingName = "Tennis court";
            return buildingName;
        case Buildings::Pigsty:
            buildingName = "Pigsty";
            return buildingName;
        case Buildings::Chicken_coop:
            buildingName = "Chicken coop";
            return buildingName;
        default:
            return buildingName;
    }
}

struct Rooms { // структура "Комнаты"
    size_t roomType;
    double areaLiving; // площадь жилой комнаты
    double areaNonLiving; // площадь нежилой комнаты    
};

struct Floors { // структура "Этажи дома"
    double ceiling;     //высота потолка
    double floorArea;
    int totalRooms;
    std::vector<Rooms> rooms;  // вектор объектов для структуры Rooms
    void read_rooms(const std::string& fileLocation);
};

struct Building { // струткрура Строения
    size_t buildingType;   // тип строения согласно enum Buildings
    double buildingArea;   // площадь строения. кв.м.
};

struct House {
    int number_of_storeys;
    double areaHouseAlongThePerimeter;
    bool isFurnace;
    std::vector<Floors> flor;
    void read_floors(const std::string& fileLocation);
};

struct Bathhouse {
    double area;
    bool isFurnace;
};

struct Homesteads { // структура "Участки"    
    char owner[10];          // имя собственника    
    int numberHst {0};              // номер участка
    double squareHstSqM {0};         // площадь участка, га.
    House house;
    std::vector<Building> building;
    Bathhouse bathhouse; 
    void read_house(const std::string& fileLocation);
    void read_building(const std::string& fileLocation);
    void read_bathhouse(const std::string& fileLocation);
};

struct Village {
    char villageName[10];
    int totalNumHmstd;
    std::vector<Homesteads> homestead;
    void read_homestead(const std::string& fileLocation);
};

void Floors::read_rooms(const std::string& fileLocation) {
    std::ifstream rm(fileLocation + "room.bin", std::ios::in | std::ios::binary);
    if(!rm.is_open()) {
        std::cerr << "The room is missing. Please plan. ";
        return;
    } else {
        int rooms_size;
        rm.read((char*)& rooms_size, sizeof(rooms_size));
        Rooms rms {0, 0, 0};
        /*while(!rm.eof())*/
        for(int i = 0; i < rooms_size; ++i) {
            rm.read((char*)& rms.roomType, sizeof(rms.roomType));
            rm.read((char*)& rms.areaLiving, sizeof(rms.areaLiving));
            rm.read((char*)& rms.areaNonLiving, sizeof(rms.areaNonLiving));
            rooms.push_back({rms});
        }
        //rooms.resize(rooms.size() - 1);
        rm.close();
    }
}

void House::read_floors(const std::string& fileLocation) {        
    std::ifstream flr(fileLocation + "floor.bin", std::ios::in | std::ios::binary);
    if(!flr.is_open()) {
        std::cerr << "The floor is missing. Please plan. ";
        //write_village(village, fileLocation);
        return;
    } else {
        int flor_size;
        flr.read((char*)& flor_size, sizeof(flor_size));
        Floors flrs {0, 0};
        /*while(!flr.eof())*/
        for(int i = 0; i < flor_size; ++i) {
            flr.read((char*)& flrs.ceiling, sizeof(flrs.ceiling));
            flr.read((char*)& flrs.floorArea, sizeof(flrs.floorArea));
            flr.read((char*)& flrs.totalRooms, sizeof(flrs.totalRooms));
            flor.push_back({flrs});
        }
        flr.close();
        //flor.resize(flor.size() - 1);

        #if DEBUG4
        for(int i = 0; i < size(flor); ++i) {
            std::cout << ordinal_number(i + 1)
                        << " floor: ceiling = " << flor[i].ceiling
                        << ", area = " << flor[i].floorArea 
                        << ", total number of rooms = " << flor[i].totalRooms
                        << "\n";
        }
        #endif        
    }
}

void Homesteads::read_house(const std::string& fileLocation) {
    std::cout << "# " << numberHst << ": \n";        
    std::ifstream hs(fileLocation + "house.bin", std::ios::in | std::ios::binary);
    if(!hs.is_open()) {
        std::cerr << "The house is missing. Please plan. ";
        //write_village(village, fileLocation);
        return;
    } else {
        hs.read((char*)& house, sizeof(house));
    }
    hs.close();
    house.read_floors(fileLocation);
}

void Homesteads::read_building(const std::string& fileLocation) {
    std::ifstream bldng(fileLocation + "building.bin", std::ios::in | std::ios::binary);
    if(!bldng.is_open()) {
        std::cerr << "The buildings is missing. Please plan. ";
        //write_village(village, fileLocation);
        return;
    } else {
        #if DEBUG4
        std::cout << "# " << numberHst << ": \n";
        #endif
        int build_size;
        bldng.read((char*)& build_size, sizeof(build_size));
        Building bldngs {0, 0};
        /*while(!bldng.eof())*/
        for(int i = 0; i < build_size; ++i) {
            bldng.read((char*)& bldngs.buildingType, sizeof(bldngs.buildingType));
            bldng.read((char*)& bldngs.buildingArea, sizeof(bldngs.buildingArea));
            building.push_back({bldngs});
        }
        bldng.close();
        //building.resize(size(building) - 1);                     
    }
}

void Homesteads::read_bathhouse(const std::string& fileLocation) {
    std::cout << "# " << numberHst << "\n";
    std::ifstream bthhs(fileLocation + "bathhouse.bin", std::ios::in | std::ios::binary);
    if(!bthhs.is_open()) {
        std::cerr << "The bathhouse is missing. Please plan. ";
        return;
    } else {
        bthhs.read((char*)& bathhouse, sizeof(bathhouse));            
    }
    bthhs.close();
}

void Village::read_homestead(const std::string& fileLocation) {        
    std::ifstream hmstd(fileLocation + "homestead.bin", std::ios::in | std::ios::binary );
    if(!hmstd.is_open()) {
        std::cerr << "Error! File homestead.bin does not exist\n";
        return;
    } else {        
        int size_hmstd;
        hmstd.read((char*)& size_hmstd, sizeof(size_hmstd));
        #if DEBUG4
        std::cout << "size_hmstd = " << size_hmstd << "\n";
        #endif
        Homesteads hmstds;
        while(!hmstd.eof())
        /*for(int i = 0; i < size_hmstd; ++i) */{
            std::cout << "read homestead start \n";
            int len;
            hmstd.read((char*)& len, sizeof(len));
            #if DEBUG4
            std::cout << " ##-" << sizeof(len) << ", len = " << len;
            #endif
           // hmstds.owner.resize(len);
            hmstd.read((char*) hmstds.owner, len);
            #if DEBUG4
            std::cout << ", owner: " << hmstds.owner;
            #endif
            hmstd.read((char*)& hmstds.numberHst, sizeof(hmstds.numberHst));
            #if DEBUG4
            std::cout << " #-" << sizeof(hmstds.numberHst) << ", numberHst = " << hmstds.numberHst;
            #endif 
            hmstd.read((char*)& hmstds.squareHstSqM, sizeof(hmstds.squareHstSqM));
            #if DEBUG4
            std::cout << " ###-" << sizeof(hmstds.squareHstSqM) << ", area = "  << hmstds.squareHstSqM << "\n";
            #endif
            homestead.push_back({hmstds});
            #if DEBUG4
            std::cout << "read homestead down" << "\n";
            #endif                
        }           
        hmstd.close();
        homestead.resize(homestead.size() - 1);
        #if DEBUG4
        std::cout << "homestead.size = " << homestead.size() << "\n";
        #endif
    } 
    std::cout << "\n";
    #if DEBUG4
    for(int i = 0; i < homestead.size(); ++i) {
        std::cout << homestead[i].numberHst << " @ " << homestead[i].owner << " @@ " << homestead[i].squareHstSqM << "\n";
    }
    std::cout << "\n";
    #endif
    for(int i = 0; i < homestead.size(); ++i) {
        homestead[i].read_house(fileLocation);
        homestead[i].read_building(fileLocation);
        homestead[i].read_bathhouse(fileLocation);
    }
}

void read_village(Village& village, std::string& fileLocation) {
    std::ifstream vllg;
    vllg.clear();
    vllg.open(fileLocation + "village.bin", std::ios::in | std::ios::binary);
    if(!vllg.is_open()) {
        std::cerr << "The village is missing. Please create a village.\n";
        //create_village(village);
        return;
    } else {
        if(vllg.read((char*)& village, sizeof(village))) {
            #if DEBUG4
            std::cout << "village name and total number of homesteads = " << village.villageName << ", " 
                      << village.totalNumHmstd << "\n";
            #endif
        }
    }
    vllg.close();
    #if DEBUG4    
    std::cout << "homestead = " << village.homestead.size() << "\n";
    #endif
    village.read_homestead(fileLocation);
}

int main() {
    std::string fileLocation {"../data/210502/"};
    Village village;
    read_village(village, fileLocation);
}