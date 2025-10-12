#include <iostream>
#define SPRING "Spring"
#define SUMMER "Summer"
#define AUTUMN "Fall"
#define WINTER "Winter"
#define SEASON(a) ((a == SPRING) ? SPRING :\
        ((a == SUMMER) ? SUMMER :\
         ((a == AUTUMN) ? AUTUMN :\
          ((a == WINTER) ? WINTER :\
           "uncertain"))))
#define CONCLUSION1 " It's "
#define CONCLUSION2 " now.\n"
#define PROGRAMMERS_SEASON "Fall" // The programmer specifies the name of the season that he wants to see on the screen 
// or so #define PROGRAMMERS_SEASON SUMMER

#ifdef PROGRAMMERS_SEASON
int main() {
    std::cout << CONCLUSION1 << SEASON(PROGRAMMERS_SEASON) << CONCLUSION2;
}
#endif
