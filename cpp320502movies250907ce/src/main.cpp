#include "common.h"
#include "movie.h"
#include "movies.h"

int main() {
    std::cout << "Hello\n";

    Movies movies;
    movies.read();
//    movies.print();
    movies.search("Robert De Niro");
    std::cout << "\n--------------------------------\n";
    movies.search("Thomas Hanks");
}
