#pragma once

class Train {
  private:  
    char designation;
    int travelTime;
    bool isArrived;
    bool isOnPlatform;
    bool isDeparted;

  public:
    Train(char);
    ~Train() = default;
    void arrival();
    void wait();
    char getDesignation();
    bool getIsArrived();
    bool getIsOnPlatform();
    void setIsOnPlatform(bool);
    bool getIsDeparterd();
    void setIsDeparted(bool);
};

void depart(std::vector<Train>&);