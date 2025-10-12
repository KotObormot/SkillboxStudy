#include <iostream>
#include <iomanip>
#include <ctime>

#define ARTYOM true
#define DEBUG false

int main() {
    std::cout << "Hello!\n Enter time with format mm:ss--> ";
    std::tm tm_timer {};
    std::cin >>  std::get_time(&tm_timer, "%M:%S");
#if ARTYOM
    std::time_t t_timer = tm_timer.tm_min * 60 + tm_timer.tm_sec;
#else    
    std::time_t t_timer = mktime(&tm_timer);
#endif

    while(true) {
        std::tm* tm_local = std::localtime(&t_timer);
        std::cout << std::put_time(tm_local, "%M:%S") << "\n";

        if(tm_local->tm_min + tm_local->tm_sec <= 0) {
            std::cout << "\a" << "DING! DING! DING!\n";
            break;
        }

        std::time_t t_start = std::time(nullptr);
        std::tm* tm_start = std::localtime(&t_start);        
        int c_start = clock();

        #if DEBUG            
            std::cout << "* " << t_timer << "\t" << t_start << "\t" << c_start << "\t";
        #endif
        
        --t_timer;

        while(true) {
            std::time_t t_finish = std::time(nullptr);
            double diff_time = std::difftime(t_finish, t_start);
            int c_finish = clock();

            if(((int)diff_time >= 1) && ((c_finish - c_start) * 1000 / CLOCKS_PER_SEC) >= 1000) {
                #if DEBUG
                    std::cout << std::fixed << diff_time << " sec.\t" 
                            << c_finish << "\t"
                            << (c_finish - c_start) * 1000 / CLOCKS_PER_SEC << " msec.\t ";
                #endif                
                break;
            }
        }

    }

    return 0;
}