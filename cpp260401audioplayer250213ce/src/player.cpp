#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <limits> // для std::numeric_limits
#include "player.h"
#include "cci.h"


bool Player::loadPlaylist() {
    bool isNoPlaylist {true};
    std::ifstream playList;
    playList.open("./data/playlist.txt");
    if(!playList.is_open()) {
        std::cerr << "There is no playlist!\n";
        isNoPlaylist = false;
    } else {
        size_t first {};
        std::tm creationDateIn {};
        int recordingDurationIn {};
        std::string titleIn {};
        while(true) {
            if(playList.eof()) {
                break;
            }
            playList >> first >> std::get_time(&creationDateIn, "%d.%m.%Y") >> recordingDurationIn;
            std::getline(playList, titleIn);
            Track second {creationDateIn, recordingDurationIn, titleIn};
            std::pair<size_t, Track> anyTrack(first, second);
            play_list.insert(anyTrack);
        }
        playList.close();
    }
    return isNoPlaylist;
}

void Player::printPlailist() {
    std::cout << "Your playlist (" << play_list.size() << " tracks): \n";
    for(const auto& [first, second] : play_list) {
        Track printedTrack {second};
        printedTrack.printTrack();
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Player::randomTrackNumber() {
    std::srand(std::time(nullptr));
    size_t numTrack {std::rand() % play_list.size()};
    iterFound = play_list.find(numTrack);
    if(iterFound == play_list.end()) {
        iterFound = play_list.begin();    
    }
}

bool Player::searchTrack(std::string& nameTrack) {
    bool isTrackFound {false};
    for(int i {0}; i < nameTrack.size(); ++i) {
        nameTrack[i] = std::tolower(nameTrack[i]);
    }
    for(std::map<size_t, Track>::iterator it {play_list.begin()};
            it != play_list.end(); ++it) {
        std::string name = it->second.getTitle();
        for(int i {0}; i < name.size(); ++i) {
            name[i] = std::tolower(name[i]);
        }
        if(name.find(nameTrack) == std::string::npos) {
            continue;
        } else {
            iterFound = it;
            isTrackFound = true;
            break;
        }
    }
    return isTrackFound;
}

bool Player::onPlauer() {
    bool isOnPlayer {true};
    std::cout << "Press the ON button to turn on your player--> ";
    std::string onButton = correctCommandInput();    
    while(onButton != "on") {
        std::cout << "Press the ON button--> ";
        onButton = correctCommandInput();
    }
    playerMode = 0;
    if(!loadPlaylist()) {
        isOnPlayer = false;
    }
    return isOnPlayer;
}

void Player::playTrack() {
    if(playerMode == 0) {
        std::string nameTrack {};
        std::cout << "Select track name--> ";
        std::cin.clear();
        getline(std::cin, nameTrack);
        if(searchTrack(nameTrack)) {
            playerMode = 1;
            Track trackFound = iterFound->second;
            trackFound.printTrack();
            std::cout << " is playing.\n";
        } else {
            std::cout << "Track not found!\n";
        }
    } else if(playerMode == 2) {
        playerMode = 1;
        Track trackPaused = iterFound->second;
        trackPaused.printTrack();
        std::cout << " continues to play.\n";
    } else {                                        // if(playerMode == 1) 
        std::cout << "Playback is already in progress. Press the STOP button to stop.\n";
    }
}

void Player::pauseTrack() {
    if(playerMode == 1) {
        playerMode = 2;
        iterFound->second.printTrack();
        std::cout << " is paused.\n";
    } else if(playerMode == 0 || playerMode == 0) {        
        std::cout << "The track does not play.\n";
    }
}

void Player::stopTrack() {
    if(playerMode == 1 || playerMode == 2) {
        playerMode = 0;
        std::cout << "The track has been stopped.\n";
    } else  {                                       //if(playerMode == 0)
        std::cout << "No track is playing. To play a track, press the PLAY button.";
    }
}

void Player::nextTrack() {
    if(playerMode == 1 || playerMode == 2) {
        playerMode = 1;
        iterFound->second.printTrack();        
        std::cout << " has been stopped.\n";
        std::map<size_t, Track>::iterator itOld {iterFound};
        while(true) {
            randomTrackNumber();
            if(itOld != iterFound) {
                break;
            }
        }
        iterFound->second.printTrack();
        std::cout << " is playing.\n";
    } else  {                                       //if(playerMode == 0)
        std::cout << "No track is playing. To play a track, press the PLAY button.";
    }
}