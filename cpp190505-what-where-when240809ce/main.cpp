#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void spinning_top(int& pos, const int& offset, int* sectors) {
    pos = (pos + offset % 13 >= 13) ? (pos + offset % 13 - 13) : (pos + offset % 13);
    
    if(*(sectors + pos) != 0) {
        while(*(sectors + pos) != 0) {
            pos = (pos + 1 >= 13) ? (pos + 1 - 13) : (pos + 1);
        }
    }    
    
    *(sectors + pos) = 1;
    
    return;
}

int main() {
    std::ifstream questions, answers;
    questions.open("../data/questions190505.txt", std::ios::binary);
    answers.open("../data/answers190505.txt", std::ios::binary);
    if(!answers.is_open() || !questions.is_open()) {
        std::cerr << "Error opening files!\n";
    } else {
        std::cout << "Files opened. \n";
    }

    std::vector<std::string> question {};
    std::vector<std::string> answer {};
    while(!questions.eof()) {
        std::string bufferQ {""};
        std::getline(questions, bufferQ);
        question.push_back(bufferQ);
        std::string bufferA {""};
        std::getline(answers, bufferA);
        answer.push_back(bufferA);
    }
    question.resize(question.size() - 1);
    answer.resize(answer.size() - 1);
    
    std::cout << "The game begins." << "\n";
    int sectors[13] {};
    int playersPoints {0}, viewersPoints {0}, iPos {0}, arrowOffset;
    while(playersPoints < 6 && viewersPoints < 6) {        
        std::cout << "Spin the whirligig.--> ";
        std::cin >> arrowOffset;
    
        spinning_top(iPos, arrowOffset, sectors);
    
        std::cout << question[iPos] << "\n";
        std::string yourAnswer {""};
        std::cout << "What is your answer? --> ";
        std::cin >> yourAnswer;
        
        if(!yourAnswer.compare(answer[iPos])) {
            ++playersPoints;
            std::cout << "That's right! One point in your favor.\nGame score " 
                    << playersPoints << " : " << viewersPoints << "\n";
        } else {
            ++viewersPoints;
            std::cout << "Incorrect! The correct answer is " << answer[iPos] 
                    << ". The point goes to the TV viewers.\nGame score " 
                    << playersPoints << " : " << viewersPoints << "\n";
        }
        std::cout << "\n================\n";
    }
    std::cout << "Game over. ";
    if(playersPoints < viewersPoints) {
        std::cout << "Players won.\n";
    } else {
        std::cout << "TV viewers won.\n";
    }
    
    answers.close();
    questions.close();
}