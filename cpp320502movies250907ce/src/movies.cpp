#include "movies.h"

void Movies::print() {
    for(auto& [title, movie] : movieCollection) {
        std::cout << "* Title:\t" << title << "\n";
        movie.print();
        std::cout << "\n-----------------------------\n";
    }
}

void Movies::read() {
    std::ifstream fileJ("movies.json");
    if(!fileJ.is_open()) {
        std::cerr << "File \"movies.json\" not found\n";
        return;
    }

    json moviesJ(json::parse(fileJ));
    fileJ.close();

    moviesJ.at("Movies").get_to(movieCollection);
}

void Movies::search(const std::string& nameToSearch) {
    std::vector<std::map<std::string, std::string>::iterator> iterNameFound {};
    std::vector<std::map<std::string, Movie>::iterator> iterMovieFound{};

    for(std::map<std::string, Movie>::iterator iterMovie {movieCollection.begin()}
            ; iterMovie != movieCollection.end(); ++iterMovie) {
        for(std::map<std::string, std::string>::iterator iterName {iterMovie->second.cast.begin()}
                ; iterName != iterMovie->second.cast.end(); ++iterName) {
            
            if(iterName->first.find(nameToSearch) == std::string::npos) {
                continue; 
            } else {
                iterNameFound.emplace_back(iterName);
                iterMovieFound.emplace_back(iterMovie);                
            }
        }
    }

    if(iterMovieFound.empty() && iterNameFound.empty()) {    
        std::cout << nameToSearch << " not found.\n";
    } else {
        std::cout << nameToSearch << " found:\n";
        for(int i(0); i < iterNameFound.size(); ++i) {
            std::cout << "\t" << iterMovieFound[i]->first << ":\t" << iterNameFound[i]->second << "\n";
        }
    }
}