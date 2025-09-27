#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits> // для std::numeric_limits
#include <ctime>

const int map_dimensions {20};
const int countGamersP {1};
const int countGamersE {5};

int handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        int x {0};
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

inline std::string ordinal_number(const int number) {
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

struct Coordinate {
    int x, y;
};

Coordinate new_coordinate(const Coordinate& coordinate, const char direction) {
    int x {coordinate.x};
    int y {coordinate.y};
    Coordinate new_coordinate = coordinate;
    if((y - 1 >= 0) && (direction == 'l' || direction == 'L')) {
        new_coordinate.y = y - 1;        
    } else if((y + 1 < map_dimensions) && (direction == 'r' || direction == 'R')) {
        new_coordinate.y = y + 1;
    } if((x - 1 >= 0) && (direction == 'u' || direction == 'U')) {
        new_coordinate.x = x - 1;
    } else if ((x + 1 < map_dimensions) && (direction == 'd' || direction == 'D')) {
        new_coordinate.x = x + 1;
    }
    return new_coordinate;
}

struct Character {
    char team; // p - player; e - enemy 
    std::string nameChar;
    int life;   // 50 ... 150
    int armor;  // 0 ... 50
    int damage; // 15 ... 30
    bool on_the_map[map_dimensions][map_dimensions] {false};
    Coordinate coordinate;
    void move(const char direction, std::vector<Character>& characters, std::vector<Character>& opponents);
    void move_enemy(std::vector<Character>& enemies, std::vector<Character>& personages);
    void take_damage(const int& damage);
};

void Character::move(const char directrion, std::vector<Character>& characters, std::vector<Character>& opponents) {
    int& x = coordinate.x;
    int& y = coordinate.y;
    int xN = new_coordinate(coordinate, directrion).x;
    int yN = new_coordinate(coordinate, directrion).y;
    bool change_place;
    int i = 0;
    while(i < characters.size()) {
        //If a player from your team is already in the new position, you cannot move!
        if(characters[i].on_the_map[xN][yN]) {
            change_place = false;
            break;
        } else {
            change_place = true;
        }
        ++i;
    } 
    i = 0;
    if(change_place) {
        while(i < opponents.size()) {
            if(opponents[i].on_the_map[xN][yN]) {
                opponents[i].take_damage(damage);
                if(opponents[i].life > 0) { 
                    change_place = false;
                } else {
                    change_place = true;
                    if(opponents[i].team == 'P') {
                        std::cout << opponents[i].nameChar << " has fallen, we mourn.\n";
                    } else {
                        std::cout << opponents[i].nameChar << " is defeated, congratulations.\n";
                    }
                    auto iter = opponents.cbegin();
                    opponents.erase(iter + i);
                }
                break;
            } 
            ++i;
        }
    }
    if(change_place) {
        on_the_map[x][y] = false;
        x = xN;
        y = yN;
        on_the_map[x][y] = true;
    }
}

void Character::move_enemy(std::vector<Character>& enemies, std::vector<Character>& personages) {
    int n_direction = std::rand() % 4;
    char direction {};
    switch (n_direction) {
        case 0:
            direction = 'l';
            break;
        case 1:
            direction = 'r';
            break;
        case 2:
            direction = 'u';
            break;
        case 3:
            direction = 'd';
            break;
        default:
            break;
    }
    move(direction, enemies, personages);
}

void Character::take_damage(const int& damage) {
    std::cout << nameChar << " take damage -" << damage << ".\n";
    armor -= damage;
    if(armor < 0) {
        life += armor;
        armor = 0;
    }
}

bool occupied(const std::vector<Character>& person, const Coordinate& coordinate) {
    bool stumble {false};
    for(int i = 0; i < person.size(); ++i) {
        if(person[i].on_the_map[coordinate.x][coordinate.y]) {
            stumble = true;
            break;
        }
    }
    return stumble; // 
}

void create_personages(std::vector<Character>& personages) {
    Character prsn;
    prsn.team = 'P';
    std::cout << "Enter the ";
    if(countGamersP > 1) {
        std::cout << ordinal_number(personages.size() + 1);
    }
    std::cout << " hero's name--> ";
    std::cin >> prsn.nameChar;
    std::cout << "Enter the hero's life (from 50 to 150)";
    prsn.life = handling_invalid_input();
    while(prsn.life < 50 || prsn.life > 150) {
        std::cout << "Life should be no less than 50 and no more than 150";
        prsn.life = handling_invalid_input();
    }
    std::cout << "Enter the hero's armor (from 0 to 50)";
    prsn.armor = handling_invalid_input();
    while(prsn.armor < 0 || prsn.armor > 50) {
        std::cout << "Armor should be no less than 0 and no more than 50";
        prsn.armor = handling_invalid_input();
    }
    std::cout << "Enter the hero's damage (from 15 to 30)";
    prsn.damage = handling_invalid_input();
    while(prsn.damage < 15 || prsn.damage > 30) {
        std::cout << "Damage should be no less than 15 and no more than 30";
        prsn.damage = handling_invalid_input();
    }
    prsn.coordinate.x = (std::rand()) % map_dimensions;
    prsn.coordinate.y = (std::rand()) % map_dimensions;
    while(occupied(personages, prsn.coordinate)) {
        prsn.coordinate.x = (std::rand()) % map_dimensions;
        prsn.coordinate.y = (std::rand()) % map_dimensions;
    }
    prsn.on_the_map[prsn.coordinate.x][prsn.coordinate.y] = true;
    personages.push_back({prsn});
}

void create_enemies(std::vector<Character>& enemies, const std::vector<Character>& personage) {
    Character prsn;
    prsn.team = 'E';
    prsn.nameChar = "Enemy # " + std::to_string(enemies.size() + 1);
    prsn.life = ((std::rand() % 101) + 50);
    prsn.armor = (std::rand()) % 51;
    prsn.damage = ((std::rand() % 16) + 15); //  15 ... 30
    prsn.coordinate.x = (std::rand()) % map_dimensions;
    prsn.coordinate.y = (std::rand()) % map_dimensions;
    while(occupied(personage, prsn.coordinate) || occupied(enemies, prsn.coordinate)) {
        prsn.coordinate.x = (std::rand()) % map_dimensions;
        prsn.coordinate.y = (std::rand()) % map_dimensions;
    }
    prsn.on_the_map[prsn.coordinate.x][prsn.coordinate.y] = true;
    enemies.push_back({prsn});
}

void print_person(const std::vector<Character>& personages, const std::vector<Character>& opponents) {
    int character_interval = personages[0].nameChar.size();
    for(int i = 0; i < personages.size(); ++i) {
        if(personages[i].nameChar.size() > character_interval) {
            character_interval = personages[i].nameChar.size();
        }
    }
    if(character_interval < 9) {
        character_interval = 9;
    }
    std::string frameP1 (character_interval - 3, '='), frameP2 (24, '=');
    std::cout << frameP1 
              << " CHARACTERS IN THE GAME " << frameP1 << "\n"
              << std::setw(character_interval + 1) << "Name"
              << std::setw(7) << "Coord."
              << std::setw(6) << "Lifes"
              << std::setw(6) << "Armor"
              << std::setw(7) << "Damage"
              << "\n";
    for(int i = 0; i < personages.size(); ++i) {
        std::cout << std::setw(character_interval + 1) << personages[i].nameChar 
                  << std::setw(3) << personages[i].coordinate.x << ":"
                  << std::setw(2) << personages[i].coordinate.y
                  << std::setw(7) << personages[i].life
                  << std::setw(6) << personages[i].armor
                  << std::setw(7) << personages[i].damage 
                  << "\n";
    }
    for(int i = 0; i < opponents.size(); ++i) {
        std::cout << std::setw(character_interval + 1) << opponents[i].nameChar 
                  << std::setw(3) << opponents[i].coordinate.x << ":"
                  << std::setw(2) << opponents[i].coordinate.y
                  << std::setw(7) << opponents[i].life
                  << std::setw(6) << opponents[i].armor
                  << std::setw(7) << opponents[i].damage 
                  << "\n";
    }
    std::cout << frameP1 << frameP2 << frameP1 << "\n";
}

void print_map(const std::vector<Character>& personages, const std::vector<Character>& opponents) {
    std::cout << "============== BATTLE MAP ==============\n";
    char map_gen[map_dimensions][map_dimensions] {};
    for(int i = 0; i < map_dimensions; ++i) {
        for(int j = 0; j < map_dimensions; ++j) {
            map_gen[i][j] = '.';
        }
    }
    for(int i = 0; i < map_dimensions; ++i) {
        for(int j = 0; j < map_dimensions; ++j) {
            for(int m = 0; m < personages.size(); ++m) {
                if(personages[m].on_the_map[i][j]) {
                    map_gen[i][j] = countGamersP > 1 
                                    ? std::toupper(personages[m].nameChar[0])
                                    : personages[m].team;
                } 
            }
            for(int m = 0; m < opponents.size(); ++m) {
                if(opponents[m].on_the_map[i][j]) {
                    map_gen[i][j] = opponents[m].team;
                } 
            }
        }
    }
    for(int i = 0; i < map_dimensions; ++i) {
        for(int j = 0; j < map_dimensions; ++j) {
            std::cout << std::setw(2) << map_gen[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "=========================================\n";
}

void safe_game(std::vector<Character>& characters, const char team, const std::string& directory) {
    std::ofstream game;
    if(team == 'P') {
        game.open(directory + "personages.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    } else {
        game.open(directory + "enemies.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    }
    int v_size = characters.size();
    game.write((char*)& v_size, sizeof(v_size));
    for(int i = 0; i < v_size; ++i) {
        game.write((char*)& characters[i].team, sizeof(characters[i].team));
        int len = characters[i].nameChar.length();
        game.write((char*)& len, sizeof(len));
        game.write(characters[i].nameChar.c_str(), len);
        game.write((char*)& characters[i].life, sizeof(characters[i].life));
        game.write((char*)& characters[i].armor, sizeof(characters[i].armor));
        game.write((char*)& characters[i].damage, sizeof(characters[i].damage));        
        game.write((char*)& characters[i].coordinate.x, sizeof(characters[i].coordinate.x));        
        game.write((char*)& characters[i].coordinate.y, sizeof(characters[i].coordinate.y));
    }
    game.close();
}

bool load_game(std::vector<Character>& characters, const char team, const std::string& directory) {
    bool isGameNoOpen {true};    
    std::ifstream game;
    if(team == 'P') {
        game.open(directory + "personages.bin", std::ios::in | std::ios::binary);
    } else {
        game.open(directory + "enemies.bin", std::ios::in | std::ios::binary);
    }
    if(!game.is_open()) {        
        return isGameNoOpen;
    } else {
        isGameNoOpen = false;
        while(true) {
            Character chrctrs;
            int v_size {};
            game.read((char*)& v_size, sizeof(v_size));
            for(int i = 0; i < v_size; ++i) {
                game.read((char*)& chrctrs.team, sizeof(chrctrs.team));
                int len;
                game.read((char*)& len, sizeof(len));
                chrctrs.nameChar.resize(len);
                game.read((char*) chrctrs.nameChar.c_str(), len);
                game.read((char*)& chrctrs.life, sizeof(chrctrs.life));
                game.read((char*)& chrctrs.armor, sizeof(chrctrs.armor));
                game.read((char*)& chrctrs.damage, sizeof(chrctrs.damage));        
                game.read((char*)& chrctrs.coordinate.x, sizeof(chrctrs.coordinate.x));        
                game.read((char*)& chrctrs.coordinate.y, sizeof(chrctrs.coordinate.y));
                characters.push_back({chrctrs});            
            }
            if(game.eof()) {
                break;
            }
        }
        game.close();
    }
    for(int m = 0; m < characters.size(); ++m) {
        for(int i = 0; i < map_dimensions && i != characters[0].coordinate.x; ++i) {
            for(int j = 0; j < map_dimensions && i != characters[0].coordinate.y; ++j) {
                characters[m].on_the_map[characters[m].coordinate.x][characters[m].coordinate.y] = false; 
            }
        } 
        characters[m].on_the_map[characters[m].coordinate.x][characters[m].coordinate.y] = true; 
    }
    std::cout << "\n";
    return isGameNoOpen;
}

int main() {
    std::cout << "Hello\ncplusplus = " << __cplusplus << "\n";
    std::srand(std::time(nullptr));
    std::vector<Character> personages;
    std::vector<Character> enemies;
//    std::cout << "Loading...\nSpecify the directory with the saved game --> ";
    std::string directory {/*"../data/210504/"*/};
//    std::cin >> directory;
    if(load_game(personages, 'P', directory) || load_game(enemies, 'E', directory)) {
        std::cerr << std::setw(8) << "No saved game. Start a new game.\nCreate a player: \n";
        for(int i = 0; i < countGamersP; ++i) {
            create_personages(personages);
        }    
        std::cout << countGamersE << " enemies are created.\n";
        for(int i = 0; i < countGamersE; ++i) {
            create_enemies(enemies, personages);
        }
    }

    print_person(personages, enemies);
    print_map(personages, enemies);
    while(personages.size() > 0 && enemies.size() >0) {
        for(int i = 0; i < personages.size(); ++i) {
            std::cout << "  * " << personages[i].nameChar << " moves. ";
            char direction;
            std::cout << "Specify the direction (l / r / u / d) or q to save and exit--> ";
            std::cin.clear();
            std::cin >> direction;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while((direction != 'l' && direction != 'L')
                    && (direction != 'r' && direction != 'R')
                    && (direction != 'u' && direction != 'U')
                    && (direction != 'd' && direction != 'D')
                    && direction != 'q' && direction != 'Q') {
                std::cout << "Finally, specify the direction already (l / r / u / d) or q to save and exit--> ";
                std::cin.clear();
                std::cin >> direction;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            direction = std::tolower(direction);
            if(direction == 'l' 
               || direction == 'r'
               || direction == 'u'
               || direction == 'd') {
                personages[i].move(direction, personages, enemies);
            } else {
//                std::cout << "Specify the directory to save the game --> ";
                std::string directory {/*"../data/210504/"*/};
//                std::cin >> directory;
                safe_game(personages, 'P', directory);
                safe_game(enemies, 'E', directory);
                std::cout << "Game saved. Goodbye.\n";
                return 0;
            }
        }
        if(enemies.size() > 0) {
            std::cout << "  * Enemies move.\n";
            for(int i = 0; i < enemies.size(); ++i) {
                enemies[i].move_enemy(enemies, personages);
            }
        }

        print_person(personages, enemies);
        print_map(personages, enemies);
    }
    if(personages.size()) {
        std::cout << "You have won. Congratulations.\n";
    } else {
        std::cout << "You lost. Sorry.\n";
    }
    
    return 0;
}