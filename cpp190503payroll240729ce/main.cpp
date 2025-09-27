#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void date_format(std::string& date) {
    if(date.find('.') == std::string::npos) {
        return;
    }
    if(date.find('.') == 1) {
        date.insert(0, "0");
    }
    if(date.find('.', 3) == 4) {
        date.insert(3, "0");
    }
    date.erase(10);
    return;
}

int main() {
    std::ifstream payRoll;
    payRoll.open("../data/payroll.txt", std::ios::binary);
    if(!payRoll.is_open()) {
        std::cerr << "Error opening file!\n";
    } else {
        std::cout << "File opened.\n";
    }
    
    std::vector<std::string> starName;
    std::vector<std::string> starSurname;
    std::vector<double> starFee;
    std::vector<std::string> paymentDate;
    int count = 0;

    while(!payRoll.eof()) {
        std::string stName = {""};
        std::string stSurname = {""};
        double stFee = 0;
        std::string pmntDate = {""};
        
        payRoll >> stName >> stSurname >> stFee >> pmntDate;
        
        date_format(pmntDate);
        
        count++;
        
        starName.push_back(stName);
        starSurname.push_back(stSurname);
        starFee.push_back(stFee);
        paymentDate.push_back(pmntDate);
    }

    double maxFee = starFee[0];
    int iMax = 0;
    double sumFee = 0;
    for(int i = 0; i < starFee.size() - 1; ++i) {
        sumFee += starFee[i];    
        if(maxFee < starFee[i]) {
            maxFee = starFee[i];
            iMax = i;
        }
    }
    std::cout << "Total amount of funds paid: "  << sumFee  << ".\n" 
                << starName[iMax] << " " << starSurname[iMax]  << " has the highest fee " << maxFee 
                << " on " << paymentDate[iMax] << ".\n";

    payRoll.close();
}

