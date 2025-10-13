#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include "track.h"

Track::Track(std::tm creationDateIn, int recordingDurationIn, std::string titleIn) {
    creationDate = creationDateIn;
    recDurationSecond = recordingDurationIn;
    title = titleIn; 
}

Track::Track() {}

void Track::printTrack() {
    std::time_t tRec = std::mktime(&creationDate);
    std::cout << title << ", duration "
              << recDurationSecond << " sec, created "
              << std::put_time(std::gmtime(&tRec), "%d.%m.%Y") << ", ";
}

std::string Track::getTitle() {
    return title;
}
