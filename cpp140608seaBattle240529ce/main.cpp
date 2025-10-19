#include <iostream>

bool is_field_OK(bool field[][10], int x, int y) {
    bool isOK = false;
        if(!field[x][y]) {
            field[x][y] = true;
            isOK = true;
        }

        return isOK;
}

void single_ship(bool field[][10], char name, int quantity) {
    int x, y, counter = 0;
    while(counter < quantity) {
        std::cout << "Gamer " << name << " moves.\n";
        begin:
        std::cout << "Enter the coordinates of " << quantity << " small boats from 0 to 9 horizontally and vertically: ";
        std::cin >> x >> y;
        if((x >= 0 && x <=9) && (y >= 0 && y <=9)) {
            if(is_field_OK(field, x, y)) {
                ++counter;
            } else {
                std::cout << "This position is already taken. Be careful!" << "\n";
                goto begin;
            }
        } else {
            std::cout << "You are mistaken. Be careful!\n";
            goto begin;
        }
    }
    return;
}

void multi_person_ship(bool field[][10], char name, int quantity, int draught) {
    int xS, yS, xE, yE, counter = 0;
    while(counter < quantity) {
        std::cout << "Gamer " << name << " moves.\n";
        begin:
        std::cout << "Enter the start and end coordinates coordinates of " << quantity << " " << draught << "-seater boats from 0 to 9 horizontally and vertically: ";
        std::cin >> xS >> yS >> xE >> yE;
        if((xE >= 0 && xE <=9) && (yE >= 0 && yE <=9) && (xS >= 0 && xS <=9) && (yS >= 0 && yS <=9) )  {
            if(((xE - xS == 0) && (yE - yS < draught) && (yE > yS)) 
            || ((xE - xS < draught) && (xE > xS) && (yE - yS == 0))) {
                for(int i = xS; i <= xE; ++i) {
                    for(int j = yS; j <= yE; ++j) {
                        if(is_field_OK(field, i, j)) {
                            ++counter;
                        } else {
                            std::cout << "This position is already taken. Be careful!" << "\n";
                            goto begin;
                        }
                    }
                }
            } else {
                std::cout << "You are mistaken. Ships can only be installed strictly vertically or horizontally. "; 
                std::cout << "Installing the ship diagonally is not allowed. Be careful!\n";
                goto begin;
            }
        } else {
            std::cout << "You are mistaken. Be careful!\n";
            goto begin;
        }

    } 
    return;
}

bool fire(char name, bool field[][10]) {
    std::cout << "Gamer " << name << " moves.\n";
    int x, y;    
    bool isHit = false;
    begin:
    std::cout << "Enter the coordinates of the enemy ship from 0 to 9 horizontally and vertically: ";
    std::cin >> x >> y;
    if((x >= 0 && x <=9) && (y >= 0 && y <=9)) {
        if(!is_field_OK(field, x, y)) { 
            isHit = true;
            field[x][y] = false;
            std::cout << "Target hit!\n";
        } else {
            std::cout << "Fail!!\n";
        }
    } else {
        std::cout << "You are mistaken. Be careful!\n";
        goto begin;
    }
    return isHit;
}

int main() {
    bool playing_field_A[10][10] {};
    bool playing_field_B[10][10] {};

    std::cout << "Let's start the game. Players place four 1-tile ships.\n";
    single_ship(playing_field_A, 'A', 4);
    single_ship(playing_field_B, 'B', 4);

    std::cout << "Players place three 2-tile ships.\n";
    multi_person_ship(playing_field_B, 'B', 3, 2);
    multi_person_ship(playing_field_A, 'A', 3, 2);

    std::cout << "Players place two 3-tile ships.\n";
    multi_person_ship(playing_field_A, 'A', 2, 3);
    multi_person_ship(playing_field_B, 'B', 2, 3);    

    std::cout << "Players place one 4-tile ship.\n";
    multi_person_ship(playing_field_B, 'B', 1, 4);
    multi_person_ship(playing_field_A, 'A', 1, 4);

    std::cout << "To battle!\n";
    int hit_A = 0, hit_B = 0;
    while(hit_A < 20 && hit_B < 20) {
        if(fire('A', playing_field_B)) {
            hit_A++;
        }
        if(fire('B', playing_field_A)) {
            hit_B++;
        }
    }
    if(hit_A > hit_B) {
        std::cout << "Gaymer A wins. Congratulations!\n";
    } else if(hit_B > hit_A) {
        std::cout << "Gaymer B wins. Congratulations!\n";
    } else {
        std::cout << "Draw. Thanks for playing!\n";
    }

    return 0;
}