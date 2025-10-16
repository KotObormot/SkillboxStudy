#include "movie.h"

void Movie::print() {
    std::cout /*<< "* Title:\t" << title*/
            << "\n" << "  Country:\t" << country
            << "\n" << "  Year:\t\t" << year
            << "\n" << "  Studio:\t" << studio
            << "\n" << "  Writers:"
            << "\n";
    for(const auto& writer : writers) {
        std::cout << "\t" << writer << "\n";
    }
    std::cout << "  Director:\t" << director
            << "\n" << "  Producer:\t" << producer
            << "\n" << "  Composer:\t" << composer
            << "\n";
    std::cout << "  " << "Cast:" << "\n";
    for(const auto& [name, character] : cast) {
        std::cout << "\t" << name << ":\t" << character << "\n";
    }
}

void from_json(const json& dict, Movie& oneMovie) {
    dict.at("Country").get_to(oneMovie.country);
    dict.at("Year").get_to(oneMovie.year);
    dict.at("Studio").get_to(oneMovie.studio);
    dict.at("Writers").get_to(oneMovie.writers);
    dict.at("Director").get_to(oneMovie.director);
    dict.at("Producer").get_to(oneMovie.producer);
    dict.at("Composer").get_to(oneMovie.composer);
    dict.at("Cast").get_to(oneMovie.cast);
}
