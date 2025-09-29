#include <iostream>

#define MO "Monday."
#define TU "Tuesday."
#define WE "Wednesday."
#define TH "Thursday."
#define FR "Friday."
#define SA "Saturday."
#define SU "Sunday."
#define INVITATION "Enter day number--> "
#define NOTHING "non-existent day."
#define CONCLUSION1 "You entered the number "
#define CONCLUSION2 ". This is "
#define DAY(num) ((num == 1) ? MO : ((num == 2) ? TU : ((num == 3) ? WE : ((num == 4) ? TH : ((num == 5) ? FR : ((num == 6) ? SA : ((num == 7) ? SU : NOTHING)))))))

int main() {
    std::cout << INVITATION;
    int num_day;
    std::cin >> num_day;
    std::cout << CONCLUSION1 << num_day << CONCLUSION2 << DAY(num_day) << "\n";
}