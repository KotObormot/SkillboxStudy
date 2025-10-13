#include "swimmer.h"

std::mutex mtx1;

int main() {
    std::cout << "HELLO\n";
    std::vector<Swimmer> swimmers;
    for(size_t i(0); i < NUMBER_OF_SWIMMERS; ++i) {
        std::cout << i << ") ";
        Swimmer swimmer;
        swimmers.emplace_back(swimmer);
    }

    std::vector<std::thread> threads;
    for(auto& swimmer : swimmers) {
        threads.emplace_back(&Swimmer::timeLine, &swimmer);
    }

    bool allFinished(false);
    int timePassed(0);
    std::cout << "START ";
    while(!allFinished) {        
        {
            std::lock_guard<std::mutex> lock(mtx1);
            std::cout << timePassed << " sec\n";
            for(auto& swimmer : swimmers) {
                std::cout << "\t" << swimmer.getName()
                          << "\t" << swimmer.getDistance() << " m"
                          << "\n";
            }
            timePassed += TIME_CODE;
        }
        allFinished = true;
        for (auto& swimmer : swimmers) {
            if (!swimmer.getIsFinish()) {
                allFinished = false;
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(TIME_CODE));
    }

    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    std::cout << "\n==============RESULTS:=============\n";
    std::sort(swimmers.begin(), swimmers.end(), [](Swimmer& a, Swimmer& b) {
        return a.getTimeTaken() < b.getTimeTaken();
    });

    for (auto& swimmer : swimmers) {
        std::cout << swimmer.getName()
                  << "\t" << std::fixed << std::setprecision(0) << floor(swimmer.getTimeTaken() / 60) << " min "
                  << std::setprecision(2) << (swimmer.getTimeTaken() - floor(swimmer.getTimeTaken() / 60) * 60) << " sec"
                  << "\n";
    }

    std::cout << "\n========CALCULATION RESULT:=========\n";
    std::map<double, std::string> winners;
    for(auto& swimmer : swimmers) {
        double swimTime(RACE_DISTANCE / swimmer.getVelocity());
        std::string name(swimmer.getName());
        std::pair<double, std::string> winner(swimTime, name);
        winners.insert(winner);
    }
    
    for(const auto& [swimTime, name] : winners) {
        std::cout << name
                  << "\t" << std::fixed << std::setprecision(0) << floor(swimTime / 60) << " min "
                  << std::setprecision(2) << (swimTime - floor(swimTime / 60) * 60) << " sec"
                  << "\n";
    }
}