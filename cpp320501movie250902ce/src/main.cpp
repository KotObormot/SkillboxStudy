#include "common.h"
#include "movie.h"

#define WRITE_AND_READ true

int main() {
    std::cout << "Hello\n";
    Movie movieFirst;
#if WRITE_AND_READ
    movieFirst.make_tmp();
    std::cout << "============= movie first ================\n";
    movieFirst.print();
    movieFirst.write();
#endif 
    std::cout << "============= movie second ===============\n";
    Movie movieSecond;
    movieSecond.read();
    movieSecond.print();    
}