
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits> // для std::numeric_limits

inline void eatline() {
    while(std::cin.get() !='\n') {
        continue;
    }
}

double handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        double x {0};
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
    void add_rooms();
    void write_rooms(const std::string& fileLocation);
    void read_rooms(const std::string& fileLocation);
    void print_rooms(int num_room);    
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
    void add_floor(const int countFloors);
    void write_floors(const std::string& fileLocation);
    void read_floors(const std::string& fileLocation);
    void print_floors(int num_floor);
};

struct Bathhouse {
    double area;
    bool isFurnace;
};

struct Homesteads { // структура "Участки"    
    std::string owner;          // имя собственника    
    int numberHst {0};              // номер участка
    double squareHstSqM {0};         // площадь участка, га.
    int tot_builds;
    std::vector<House> hous;
    std::vector<Building> building;    
    Bathhouse bathhouse;    
    void add_house();
    void append_house();
    void add_building(const size_t bldngType);
    void add_bathhouse();
    void write_house(const std::string& fileLocation);
    void write_building(const std::string& fileLocation);
    void read_building(const std::string& fileLocation);
    void read_house(const std::string& fileLocation);
    void print_house(int num);
    void print_building(int indexB);
    void print_bathhouse();
};
struct Village {
    std::string villageName;
    int totalNumHmstd;
    std::vector<Homesteads> homestead;
    void add_homestead();
    void write_homestead(const std::string& fileLocation);
    void read_homestead(const std::string& fileLocation);
    void print_homestead(int num);
};

void Floors::add_rooms() {  // метод для добавления объекта в список
    Rooms rms {0, 0, 0};
    for(size_t i = static_cast<size_t>(Room::START) + 1; i < static_cast<size_t>(Room::END); i = i << 1) {
        Room purpose_of_room = static_cast<Room>(static_cast<size_t>(i));
        std::cout << std::setw(8) << " " << "Enter the total number of " << room_name(purpose_of_room) << "s ";
        unsigned int roomNumTmp {0};
        roomNumTmp = (int)handling_invalid_input();
        while(roomNumTmp > 3) {
            std::cout << std::setw(8) << " " << "Why do you need so many " << roomNumTmp << " " << room_name(purpose_of_room) << "s??? ))) Make it smaller please";
            roomNumTmp = (int)handling_invalid_input();
        }
        for(int j = 0; j < roomNumTmp; ++j) {
            if(roomNumTmp > 1) {
                std::cout << std::setw(8) << " " << "Enter the" << ordinal_number(j + 1) << room_name(purpose_of_room)  << " area (sq.m)";
            } else {
                std::cout << std::setw(8) << " " << "Enter the " << room_name(purpose_of_room)  << " area (sq.m)";
            }
            double areaTmp = handling_invalid_input();
            if(areaTmp > 0) {
                if(static_cast<size_t>(purpose_of_room) & (static_cast<size_t>(Room::Bedroom)
                                    | static_cast<size_t>(Room::Children_room)
                                    | static_cast<size_t>(Room::Living_room))) {
                    rms.areaLiving = areaTmp;
                    rms.areaNonLiving = 0;
                } else {
                    rms.areaLiving = 0;
                    rms.areaNonLiving = areaTmp;
                }
            rms.roomType = i;
            rooms.push_back({rms});
            }
        }
    }
}

void Floors::write_rooms(const std::string& fileLocation) {
    std::ofstream rm(fileLocation + "room.bin", std::ios::out | std::ios::app | std::ios::binary);
    int rooms_size = rooms.size();
    rm.write((char*)& rooms_size, sizeof(rooms_size));
    for(int i = 0; i < rooms_size; ++i) {
        rm.write((char*)& rooms[i].roomType, sizeof(rooms[i].roomType));
        rm.write((char*)& rooms[i].areaLiving, sizeof(rooms[i].areaLiving));
        rm.write((char*)& rooms[i].areaNonLiving, sizeof(rooms[i].areaNonLiving));
    }
    rm.close();
}

void Floors::read_rooms(const std::string& fileLocation) {
    std::ifstream rm(fileLocation + "room.bin", std::ios::in | std::ios::binary);
    if(!rm.is_open()) {
        std::cerr << std::setw(8) << " " << "The room is missing. Please plan. ";
        return;
    } else {
        int rooms_size {0}, shear {0};
        Rooms rms {0, 0, 0};
        while(true) {
            rm.read((char*)& rooms_size, sizeof(rooms_size));
            for(int i = 0; i < rooms_size; ++i) {
                rm.read((char*)& rms.roomType, sizeof(rms.roomType));
                rm.read((char*)& rms.areaLiving, sizeof(rms.areaLiving));
                rm.read((char*)& rms.areaNonLiving, sizeof(rms.areaNonLiving));
                rooms.push_back({rms});
            }
            if(rm.eof()) {
                break;
            }
            shear += rooms_size;
        }
        rm.close();
        auto begin = rooms.cbegin();
        auto end = rooms.cend();
        rooms.erase(begin + shear, end);
    }
}

void Floors::print_rooms(int num_room) {
        Room rm = static_cast<Room>(static_cast<size_t>(rooms[num_room].roomType));
        std::cout  << std::setw(30) << std::right << room_name(rm) << ": "
                   << std::setw(9)
                   << print_square_any_room(rooms[num_room].areaLiving + rooms[num_room].areaNonLiving) << "\n";
}

void House::add_floor(const int countFloors) {
    Floors flrs {0, 0, 0};
    std::cout << std::setw(6) << " " << "Enter the ceiling height on the " << ordinal_number(countFloors + 1) << " floor";
    flrs.ceiling = handling_invalid_input();
    while(flrs.ceiling < 2.6) {
        std::cout << std::setw(6) << " " << "Ceiling too low. Enter more 2.6 m";
        flrs.ceiling = handling_invalid_input();
    } 
    while (flrs.ceiling > 3.2) {
        std::cout << std::setw(6) << " " << "Why do you need such a high ceiling? Reduce it to a maximum of 3.2 m";
        flrs.ceiling = handling_invalid_input();
    }
    flrs.add_rooms();
    flrs.totalRooms = flrs.rooms.size();
    
    for(int i = 0; i < flrs.totalRooms; ++i) {
        flrs.floorArea += flrs.rooms[i].areaLiving + flrs.rooms[i].areaNonLiving;
    }
    flor.push_back({flrs});
}

void House::write_floors(const std::string& fileLocation) {
    std::ofstream flr(fileLocation + "floor.bin", std::ios::out | std::ios::app | std::ios::binary);
    int flor_size = flor.size();
    flr.write((char*)& flor_size, sizeof(flor_size));
    for(int i = 0; i < flor_size; ++i) {
        flor[i].write_rooms(fileLocation);
        flr.write((char*)& flor[i].ceiling, sizeof(flor[i].ceiling));
        flr.write((char*)& flor[i].floorArea, sizeof(flor[i].floorArea));
        flr.write((char*)& flor[i].totalRooms, sizeof(flor[i].totalRooms));
    }
    flr.close();
}

void House::read_floors(const std::string& fileLocation) {
    std::ifstream flr(fileLocation + "floor.bin", std::ios::in | std::ios::binary);
    if(!flr.is_open()) {
        std::cerr << "The floor is missing. Please plan. ";
        return;
    } else {
        int flor_size, shear{0};
        Floors flrs {0, 0, 0};
        while(true) {
            flr.read((char*)& flor_size, sizeof(flor_size));
            for(int i = 0; i < flor_size; ++i) {
                flr.read((char*)& flrs.ceiling, sizeof(flrs.ceiling));
                flr.read((char*)& flrs.floorArea, sizeof(flrs.floorArea));
                flr.read((char*)& flrs.totalRooms, sizeof(flrs.totalRooms));
                flor.push_back({flrs});
            }
            if(flr.eof()) {
                break;
            }
            shear += flor_size;
        }        
        flr.close();
        auto begin = flor.cbegin(); 
        auto end = flor.cend();
        flor.erase(begin + shear, end);
        for(int i = 0; i < flor.size(); ++i) {
            flor[i].read_rooms(fileLocation);
        }
    }
}

void House::print_floors(int num_floor) {
    std::cout << std::setw(5)
              << " floor: ceiling = " << std::setprecision(1) << flor[num_floor].ceiling << " m"
              << ", area = " << print_square_any_room(flor[num_floor].floorArea)
              << ", total number of rooms = " << flor[num_floor].totalRooms
              << "\n";
    int k_start {0};
    for(int i = 0; i < num_floor; ++i) {
            k_start += flor[i].totalRooms;        
    }
    double areaTotalLiving {0};
    double areaTotalNonLiv {0};
    for(int i = k_start; i < k_start + flor[num_floor].totalRooms; ++i) {
        flor[num_floor].print_rooms(i);
        areaTotalLiving += flor[num_floor].rooms[i].areaLiving;
        areaTotalNonLiv += flor[num_floor].rooms[i].areaNonLiving;
    }
    std::cout << std::setw(40) << "--------------------\n"
            << std::setw(40) << "Living floor area " << print_square_any_room(areaTotalLiving) << "\n"
            << std::setw(40) << "Non-residential area " << print_square_any_room(areaTotalNonLiv) << "\n"
            << std::setw(40) << "Total floor area " << print_square_any_room(areaTotalLiving + areaTotalNonLiv)
            << "\n";
    std::cout << "\n";
}

void Homesteads::append_house() {
    House house {0, 0, 0};
    std::cout << std::setw(5) << " " << "Enter the total number of floors in the house";
    house.number_of_storeys = (int)handling_invalid_input();
    while(house.number_of_storeys < 1 || house.number_of_storeys > 3) {
        std::cout << std::setw(5) << std::setw(3) << " "  << "The number of floors in the house must be from 1 to 3";
        house.number_of_storeys = (int)handling_invalid_input();
    }
    
    house.add_floor(0);
    while(house.flor[0].floorArea > squareHstSqM * 10000) {
        std::cout << std::setw(5) << " " << "The rooms are too big. Change the layout of the" << ordinal_number(1) << "floor. ";
        house.flor.pop_back();
        house.add_floor(0);
    }    
    house.areaHouseAlongThePerimeter = house.flor[0].floorArea;
    
    for(int i = 1; i < house.number_of_storeys; ++i) {
        house.add_floor(i);
        while(house.flor[i].floorArea > house.flor[i - 1].floorArea) {
            std::cout << std::setw(5) << " " << "The rooms are too big. Change the layout of the" << ordinal_number(i + 1) << "floor.";
            house.flor.pop_back();
            house.add_floor(i);
        }
    }

    std::cout << std::setw(5) << " "  << "Is there a furnace in the house? (y/n)--> ";
    char yn {};
    std::cin >> yn;
    while(yn != 'y' && yn != 'Y' && yn != 'n' && yn !='N') {
        std::cout << std::setw(5) << " "  << "Is there a furnace in the house??? (y/n)--> ";
        std::cin >> yn;
    }
    if(yn == 'y' || yn == 'Y') {
        house.isFurnace = true;
    }
    hous.push_back({house});
}

void Homesteads::write_house(const std::string& fileLocation) {
    int size_hous = hous.size();
    std::ofstream hs(fileLocation + "house.bin", std::ios::out | std::ios::app | std::ios::binary);
    hs.write((char*)& size_hous, sizeof(size_hous));
    for(int i = 0; i < size_hous; ++i) {        
        hous[i].write_floors(fileLocation);        
        hs.write((char*)& hous[i].areaHouseAlongThePerimeter, sizeof(hous[i].areaHouseAlongThePerimeter));
        hs.write((char*)& hous[i].number_of_storeys, sizeof(hous[i].number_of_storeys));
        hs.write((char*)& hous[i].isFurnace, sizeof(hous[i].isFurnace));
    }
    hs.close();
}

void Homesteads::read_house(const std::string& fileLocation) {
    std::ifstream hs(fileLocation + "house.bin", std::ios::in | std::ios::binary);
    if(!hs.is_open()) {
        std::cerr << "Error! File house.bin does not exist\n";
        return;
    } else {
        House house;
        int size_hous, shear {0};
        while(true) {
            hs.read((char*)& size_hous, sizeof(size_hous));
            for(int i = 0; i < size_hous; ++i) {
                hs.read((char*)& house.areaHouseAlongThePerimeter, sizeof(house.areaHouseAlongThePerimeter));
                hs.read((char*)& house.number_of_storeys, sizeof(house.number_of_storeys));
                hs.read((char*)& house.isFurnace, sizeof(house.isFurnace));
                hous.push_back({house});
            }
            if(hs.eof()) {
                break;
            }
            shear += size_hous;
        }
        hs.close();
        auto begin = hous.cbegin();
        auto end = hous.cend();
        hous.erase(begin + shear, end);
        for(int i = 0; i < hous.size(); ++i) {
            hous[i].read_floors(fileLocation);
        }
    }
}

void Homesteads::print_house(int num) {
    std::cout << std::setw(5) << "-" << "House area along the perimeter =" << print_square_any_room(hous[num].areaHouseAlongThePerimeter)
            << ", number of storeys = " << hous[num].number_of_storeys << ".";
    if(hous[num].isFurnace) {
        std::cout << " The house has a wood furnace with a chimney.";
    }
    std::cout << "\n";
    int k_start {0};
    for(int i = 0; i < num; ++i) {
        k_start += hous[i].number_of_storeys;
    }
    int num_fl {0};
    for(int i = k_start; i < k_start + hous[num].number_of_storeys; ++i) {
        std::cout << std::setw(6) << "* " << ordinal_number(++num_fl);
        hous[num].print_floors(i);
    }
}

void Homesteads::add_building(const size_t bldngType) {
    Building bldng {bldngType, 0};
    Buildings bldngs = static_cast<Buildings>(static_cast<size_t>(bldngType));
    std::cout << std::setw(5) << " " << "Enter the " << building_name(bldngs)  << " area (sq.m) or 0 if none";
    bldng.buildingArea = handling_invalid_input();
    building.push_back({bldng});
}

void Homesteads::write_building(const std::string& fileLocation) {
    std::ofstream bldng(fileLocation + "building.bin", std::ios::out | std::ios::app | std::ios::binary);
    int size_build = building.size();    
    bldng.write((char*)& size_build, sizeof(size_build));
    for(int i = 0; i < building.size(); ++i) {
        bldng.write((char*)& building[i].buildingType, sizeof(building[i].buildingType));
        bldng.write((char*)& building[i].buildingArea, sizeof(building[i].buildingArea));
    }        
    bldng.close();
}

void Homesteads::read_building(const std::string& fileLocation) {
    std::ifstream bldng(fileLocation + "building.bin", std::ios::in | std::ios::binary);
    if(!bldng.is_open()) {
        std::cerr << "Error! File building.bin does not exist\n";
        return;
    } else {
        Building bldngs;
        while(true) {
            bldng.read((char*)& tot_builds, sizeof(tot_builds));
            for(int i = 0; i < /*sz_bld*/ tot_builds; ++i) {
                bldng.read((char*)& bldngs.buildingType, sizeof(bldngs.buildingType));
                bldng.read((char*)& bldngs.buildingArea, sizeof(bldngs.buildingArea));
                building.push_back({bldngs});                
            }
            if(bldng.eof()) {
                break;
            }
        }
        bldng.close();
        building.resize(building.size() - tot_builds);
    }
}

void Homesteads::print_building(int indexB) {
    int k_start {0};
    for(int i = 0; i < indexB; ++i) {        
        k_start += tot_builds;
    }
    for(int i = k_start; i < k_start + tot_builds; ++i) {    
        Buildings bldngs = static_cast<Buildings>(static_cast<size_t>(building[i].buildingType));                
        if((int)building[i].buildingArea != 0) {
            std::cout << std::setw(5) << "-" << building_name(bldngs) << ": " << print_square_any_room(building[i].buildingArea) << "\n";
        }
    }
}

void Homesteads::add_bathhouse() {
    bathhouse.isFurnace = false;
    bathhouse.area = 0;
    std::cout << std::setw(5) << " " << "Enter the bathhouse area (sq.m) or 0 if none";
    bathhouse.area = handling_invalid_input();
    if((int)bathhouse.area > 0) {
        char yn {};
        std::cout << std::setw(5) << " " << "Is there a furnace in the bathhouse? (y/n)--> ";
        std::cin >> yn;
        while(yn != 'y' && yn != 'Y' && yn != 'n' && yn !='N') {
            std::cout << std::setw(5) << " "  << "Is there a furnace in the bathhouse??? (y/n)--> ";
            std::cin >> yn;
        }
        if(yn == 'y' || yn == 'Y') {
            bathhouse.isFurnace = true;
        }
    }
}

void Homesteads::print_bathhouse() {
        std::cout << std::setw(5) << "-" << "Bathhouse area = " << print_square_any_room(bathhouse.area) ;
        if(bathhouse.isFurnace) {
            std::cout << " The bathhouse has a wood furnace with a chimney.";
        }
        std::cout << "\n";
}

void Village::add_homestead() {
    Homesteads hmstds {"", 0, 0, 0};
    hmstds.numberHst = totalNumHmstd + 1;
    std::cout << "----------------------------------\n" 
              << std::setw(12) << "Homestead #" << hmstds.numberHst << ": ";        
    std::cout << std::setw(3) << " " << "Enter owner name--> ";
    std::cin >> hmstds.owner;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::setw(3) << " " << "Enter the area of the plot (ha) from 0.06 to 1.5";
    hmstds.squareHstSqM = 0;
    hmstds.squareHstSqM = handling_invalid_input();
    while (hmstds.squareHstSqM < .06 || hmstds.squareHstSqM > 1.5) {
        std::cout << std::setw(3) << " " << "The area of the plot must be no less than 0.06 and no more than 1.5 hectares";
        hmstds.squareHstSqM = handling_invalid_input();
    }
    
    std::cout << std::setw(3) << " " << "Description of the house:\n";
    hmstds.append_house();
    double sumOfAllBuildingAreas = hmstds.hous[0].areaHouseAlongThePerimeter;
    
    std::cout << std::setw(3) << " "  << "What buildings are on the plot?\n";
    hmstds.add_bathhouse();
    while(sumOfAllBuildingAreas + hmstds.bathhouse.area > hmstds.squareHstSqM * 10000) {
        std::cout << std::setw(5) << " " << "The area of the bathhouse is too large. Reduce it. ";
        hmstds.add_bathhouse();
    }
    sumOfAllBuildingAreas += hmstds.bathhouse.area;

    int bldng_count = 0;
    for(size_t i = static_cast<size_t>(Buildings::START) + 1; i < static_cast<size_t>(Buildings::END); i = i << 1) {
        hmstds.add_building(i);
        while((sumOfAllBuildingAreas + hmstds.building[bldng_count].buildingArea) > (hmstds.squareHstSqM * 10000)) {
            hmstds.building.pop_back();
            std::cout << std::setw(5) << " " << "The area of the " 
                        << building_name(static_cast<Buildings>(static_cast<size_t>(hmstds.building[bldng_count].buildingType))) 
                        << " is too large. Reduce it. ";
            hmstds.add_building(i);
        }
        sumOfAllBuildingAreas += hmstds.building[i].buildingArea;
        bldng_count++;
    }
    homestead.push_back({hmstds});
    totalNumHmstd++;
}

void Village::write_homestead(const std::string& fileLocation) {    
    std::ofstream hmstd(fileLocation + "homestead.bin", std::ios::out | std::ios::app | std::ios::binary);
    int hmstd_count = homestead.size();
    hmstd.write((char*)& hmstd_count, sizeof(hmstd_count));
    for(int i = 0; i < hmstd_count; ++i) {
        homestead[i].write_house(fileLocation);
        homestead[i].write_building(fileLocation);
        int len = homestead[i].owner.length();
        hmstd.write((char*)& len, sizeof(len));
        hmstd.write(homestead[i].owner.c_str(), len);        
        hmstd.write((char*)& homestead[i].numberHst, sizeof(homestead[i].numberHst));
        hmstd.write((char*)& homestead[i].squareHstSqM, sizeof(homestead[i].squareHstSqM));
        hmstd.write((char*)& homestead[i].tot_builds, sizeof(homestead[i].tot_builds));
        hmstd.write((char*)& homestead[i].bathhouse, sizeof(homestead[i].bathhouse));
    }        
    hmstd.close();
}    

void Village::read_homestead(const std::string& fileLocation) {
    std::ifstream hmstd(fileLocation + "homestead.bin", std::ios::in | std::ios::binary );
    if(!hmstd.is_open()) {
        std::cerr << std::setw(2) << " " << "The village is uninhabited. Add at least one homestead.\n";
        add_homestead();
        write_homestead(fileLocation);
    } else {
        int hmstd_count {0}, shear {0};
        Homesteads hmstds;
        while(true) {
            int hmstd_count;
            hmstd.read((char*)& hmstd_count, sizeof(hmstd_count));
            for(int i = 0; i < hmstd_count; ++i) {
                int len;
                hmstd.read((char*)& len, sizeof(len));
                hmstds.owner.resize(len);
                hmstd.read((char*) hmstds.owner.c_str(), len);
                hmstd.read((char*)& hmstds.numberHst, sizeof(hmstds.numberHst));
                hmstd.read((char*)& hmstds.squareHstSqM, sizeof(hmstds.squareHstSqM));
                hmstd.read((char*)& hmstds.tot_builds, sizeof(hmstds.tot_builds));
                hmstd.read((char*)& hmstds.bathhouse, sizeof(hmstds.bathhouse));
                homestead.push_back({hmstds});
            }
            if(hmstd.eof()) {
                break;
            }            
            shear += hmstd_count;
        }
        hmstd.close();
        auto begin = homestead.cbegin();
        auto end = homestead.cend();
        homestead.erase(begin + shear, end);
    }
    for(int i = 0; i < homestead.size(); ++i) {
        homestead[i].read_building(fileLocation);
        homestead[i].read_house(fileLocation);
    }
    
}

void Village::print_homestead(int num) {
    int i {0};
    while(true) {
        if(homestead[i].numberHst == num) {
            break;
        } else {
            i++;
        }
        if(i >= homestead.size()) {
            std::cerr << "Plot number " << num << " is missing (" << "\n";
            return;
        }
    }
    std::cout << std::setw(3) << "=" 
              << " # " << homestead[i].numberHst
              << ", owner: " << homestead[i].owner 
              << ", area = " << homestead[i].squareHstSqM
              << " ha\n";
    homestead[i].print_house(i);
    if((int)homestead[i].bathhouse.area != 0) {
        homestead[i].print_bathhouse();
    }
    homestead[i].print_building(i);
}

void create_village(Village& village) {
    village.totalNumHmstd = 0;
    std::cout << std::setw(3) << " " << "Enter the name of the village--> ";
    std::cin >> village.villageName;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i = 0; i < village.villageName.size(); ++i) {
        village.villageName[i] = std::toupper(village.villageName[i]);
    }
}

void write_village(Village& village, const std::string& fileLocation) {
    std::ofstream vllg(fileLocation + "village.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    int len = village.villageName.length();
    vllg.write((char*)& len, sizeof(len));
    vllg.write(village.villageName.c_str(), len);
    vllg.write((char*)& village.totalNumHmstd, sizeof(village.totalNumHmstd));    
    vllg.close();
}

void read_village(Village& village, const std::string& fileLocation) {
    std::ifstream vllg;
    vllg.clear();
    vllg.open(fileLocation + "village.bin", std::ios::in | std::ios::binary);
    if(!vllg.is_open()) {
        std::cerr << "The village is missing. Please create a village.\n";
        create_village(village);
        write_village(village, fileLocation);
    } else {
        int len;
        vllg.read((char*)& len, sizeof(len));
        village.villageName.resize(len);
        vllg.read((char*)village.villageName.c_str(), len);
        vllg.read((char*)& village.totalNumHmstd, sizeof(village.totalNumHmstd));
    }
    vllg.close();
}

void print_village(const Village& village) {
    std::cout << "================================== PARAMETERS OF HOMESTEADS OF THE VILLAGE  \"" 
              << village.villageName << "\" ======================================\n";
    int hmstdSize = village.homestead[0].owner.size();
    for(int i = 0; i < village.homestead.size(); ++i) {
        if(village.homestead[i].owner.size() > hmstdSize) {
            hmstdSize = village.homestead[i].owner.size();
        }
    }
    if(hmstdSize < 5) {
        hmstdSize = 5;
    }
    std::cout << std::setw(4) << "No" << std::setw(hmstdSize + 1) << "OWNER" << std::setw(8) << "AREA"
            << std::setw(12) << "AreaOfH*" << std::setw(7) << "Floors"
            << std::setw(10) << "Bathhouse" << std::setw(3) << "+Furnace" << std::setw(13) << "Garage"
            << std::setw(12) << "Pool"
            << std::setw(12) << "Tenn.court"
            << std::setw(12) << "Pigsty"
            << std::setw(12) << "Chick.coop"
            << "\n";

    int k_start {0}; // k_start
    for(int i = 0; i < std::size(village.homestead); ++i) {        
        std::cout << std::setw(3) << village.homestead[i].numberHst << ")"
                << std::right
                << std::setw(hmstdSize + 1) << village.homestead[i].owner
                << std::setw(5) << std::right
                << std::fixed << std::setprecision(2) << village.homestead[i].squareHstSqM << " ha"
                << std::setw(13) << print_square_any_room(village.homestead[i].hous[i].areaHouseAlongThePerimeter)
                << std::setw(3) << village.homestead[i].hous[i].number_of_storeys
                << std::setw(15) << print_square_any_room(village.homestead[i].bathhouse.area)
                << std::setw(3) << print_square_any_room(village.homestead[i].bathhouse.isFurnace)
                << std::setw(5) << " ";
        int k_step = village.homestead[i].tot_builds;  //tot_builds;
        for(size_t j = static_cast<size_t>(Buildings::START) + 1; j < static_cast<size_t>(Buildings::END); j = j << 1) {
            for(int k = k_start; k < k_start + k_step; ++k) {
                if(j == village.homestead[i].building[k].buildingType) {
                    std::cout << std::setw(12) << print_square_any_room(village.homestead[i].building[k].buildingArea);
                }
            }
        }
        k_start += k_step;
        std::cout << "\n";
    }    
    std::cout << "\n--------------------------------------------------\n"
            << "*Note: AreaOfH is occupied area of the house along the perimeter\n";
}

void accessing_data(const Village& village) {
    std::cout << "Welcome to " << village.villageName << "!\n"
              << "Total number of plots = " << village.totalNumHmstd << "\n";
        std::cout << "Enter the plot number";
        int plotNumber = handling_invalid_input();
        std::cout << "Total number of houses = " << village.homestead[plotNumber - 1].hous.size() << "\n"
                  << "Total number of floors in the house = " << village.homestead[plotNumber - 1].hous[plotNumber - 1].flor.size() << "\n"
                  << "Enter the floor number";
        int floorNumber = handling_invalid_input();
        std::cout << "Total number of rooms on the floor = " << village.homestead[plotNumber - 1].hous[plotNumber - 1].flor[floorNumber - 1].rooms.size() << "\n";
        for(int k = 0; k < village.homestead[plotNumber - 1].hous[plotNumber - 1].flor[floorNumber - 1].rooms.size(); ++k) {
            std::cout << village.homestead[plotNumber - 1].hous[plotNumber - 1].flor[floorNumber - 1].rooms[k].roomType << " "
                      << village.homestead[plotNumber - 1].hous[plotNumber - 1].flor[floorNumber - 1].rooms[k].areaLiving +
                         village.homestead[plotNumber - 1].hous[plotNumber - 1].flor[floorNumber - 1].rooms[k].areaNonLiving
                      << "\n";
        }
}

int main() {
    std::cout << "Hello\n";
    std::cout.setf(std::ios::fixed);    
    std::string fileLocation /*{"../data/210502/"}*/;
    std::cout << "File location-->";
    std::cin >> fileLocation;
    
    char choice {};
    while(choice != 'q') {
        std::cout << "Enter the operating mode please:\n"
                  << "+ Add homesteads / "
                  << "< Show a general plan of the entire village / "
                  << "h Show a detailed plan of any homestead / "
                  << "? Accessing data of nested structure vectors (incorrect)"
                  << "q End work"
                  << "--> ";                
        std::cin.clear();        
        std::cin >> choice;
        if(choice == '<') {
            Village village;
            read_village(village, fileLocation);
            village.read_homestead(fileLocation);
            write_village(village, fileLocation);
            print_village(village);            
        } else if (choice == 'h' || choice == 'H') {
            Village village;
            read_village(village, fileLocation);
            village.read_homestead(fileLocation);
            write_village(village, fileLocation);
            std::cout << "Enter the plot number";
            int homesteadNumber = handling_invalid_input();
            village.print_homestead(homesteadNumber);            
        } else if(choice == '+') {
            Village village;
            read_village(village, fileLocation);
            std::cout << "Enter the total number of added plots";
            int totalHmstds = (int)handling_invalid_input();
            for(int i = 0; i < totalHmstds; ++i) {
                village.add_homestead();
            }
            village.write_homestead(fileLocation);
            write_village(village, fileLocation);
        } else if(choice == '?') {
            Village village;
            read_village(village, fileLocation);
            village.read_homestead(fileLocation);
            accessing_data(village);
        }
    }
    
    return 0;
}
