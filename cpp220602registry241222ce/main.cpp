#include <iostream>
#include <map>
#include <string>

std::string name_norm(const std::string& name) {
    std::string nameNorm {};
    for(int i {0}; i < name.size(); ++i) {
        char symbol = name[i];
        if(symbol >= 'A' && symbol <= 'Z'
                  || symbol >= 'a' && symbol <= 'z') {
            nameNorm += std::tolower(symbol);
        }
    }
    return nameNorm;
}
void record(std::map<std::string, std::string>& queue, std::string name) {
    if(name_norm(name) != "next") {
        size_t count {queue.size()};
        queue.insert(std::make_pair(name_norm(name) + std::to_string(count), name));
        count++;
    } else {
        return;
    }
}

void call(std::map<std::string, std::string>& queue) {    
    if(queue.begin() != queue.end()) {
        std::map<std::string, std::string>::iterator next(queue.begin());
        std::cout << " ->> " << next->second << " is called from the queue.\n";
        queue.erase(next);
    } else {
        std::cout << "The queue is over.\n";
    }
}

int main() {
    std::map<std::string, std::string> queue;
    std::string name {};
    while(name_norm(name) != "quit") {
        std::cout << "Enter name or Next or Quit --> ";
        getline(std::cin, name);
        record(queue, name);
        if(name_norm(name) == "quit") {
            break;
        }
        if(name_norm(name) == "next") {
            call(queue);
        }
    }
}
