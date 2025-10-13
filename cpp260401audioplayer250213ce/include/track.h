#pragma once
#include <ctime>

class Track {
  private:
    std::tm creationDate;
    int recDurationSecond;
    std::string title;
  public:
    Track();
    Track(std::tm crD, int recDur, std::string tttl);
    void printTrack();
    std::string getTitle();
};
