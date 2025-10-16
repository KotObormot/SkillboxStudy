#include "movie.h"

void Movie::make_tmp() {
    composer = "Ennio Morricone";
    country = "USA";
    director = "Sergio Leone";
    producer = "Claudio Mancini";
    studio = "Warner Bros.";
    title = "Once Upon a Time in America";
    writers = {"Harry Grey", "Leonardo Benvenuti", "Piero De Bernardi"};
    year = 1984;
    cast.insert({"Robert De Niro", "Noodles"});
    cast.insert({"James Woods", "Max"});
    cast.insert({"Elizabeth McGovern", "Deborah"});
}

void Movie::print() {
    std::cout << "* Title:\t" << title
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

void Movie::write() {
    std::ofstream movie("movie.json");
    json dict = {
        {"Title", title}
        , {"Country", country}
        , {"Year", year}
        , {"Studio", studio}
        , {"Writers", writers}
        , {"Director", director}
        , {"Producer", producer}
        , {"Composer", composer}
        , {"Cast", cast}
    };
    movie << dict.dump(4);
    movie.close();
}

void Movie::read() {
    std::ifstream file("movie.json");

    if(!file.is_open()) {
        std::cerr << "File not found.\n";
        return;
    }

    json dict = json::parse(file);
    file.close();

    title = dict["Title"].get<std::string>();
    country = dict["Country"].get<std::string>();
    year = dict["Year"].get<int>();
    studio = dict["Studio"].get<std::string>();
    dict["Writers"].get_to<std::vector<std::string>>(writers);    
    director = dict["Director"].get<std::string>();
    producer = dict["Producer"].get<std::string>();
    composer = dict["Composer"].get<std::string>();
    dict["Cast"].get_to<std::map<std::string, std::string>>(cast); 
}
