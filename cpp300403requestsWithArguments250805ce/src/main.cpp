#include "common.h"

int main() {
    std::cout << "Hello\n";

    std::map<std::string, std::string> arguments;
    cpr::Response response;
    
    while(true) {
        std::pair<std::string, std::string> oneArgument;
        std::string key, value;
        std::cout << "KEY VALUE--> ";
        std::cin >> key;

        if(key == "get") {            
            std::cout << "\n===================\n";
            cpr::Parameters parameters;
            for (const auto& pair : arguments) {
                parameters.Add({{pair.first.c_str(), pair.second.c_str()}});
            }
            response = cpr::Get(cpr::Url("http://httpbin.org/get")
                                , parameters);
            break;

        } else if(key == "post") {            
            std::cout << "\n===================\n";                   
            cpr::Payload payload({});
            for (const auto& pair : arguments) {
                payload.Add(cpr::Pair{pair.first.c_str(), pair.second.c_str()});
            }
            response = cpr::Post(cpr::Url("http://httpbin.org/post")
                                , payload);
            break;

        } else {
            std::cin >> value;
            oneArgument.first = key;
            oneArgument.second = value;
            arguments.insert(oneArgument);
        }
    }

    if(response.status_code == 200) {
        std::cout << response.text << "\n";
    } else {
        std::cout << "Your request failed\n";
    }

    return 0;
}
