#include "requests.h"

int main() {
    std::cout << "Hello\n"
              << "Enter the HTTP request type to the httpbin.org service or click \"EXIT\" to exit:\n";

    std::vector<Request*> requests;

    while(true) {
        Request* request;
        std::cout << "user@computer:~$ ";
        std::string command(correctCommandInput()); 

        while(command != "get"
                && command != "parameters"
                && command != "post"
                && command != "put"
                && command != "delete"
                && command != "patch"
                && command != "head"
                && command != "exit"
                && command != "close") {
            std::cout << "Try again--> ";
            command = correctCommandInput();
        }

        if(command == "parameters") {
            std::string key, parameter;
            std::cout << "KEY, PARAMETER --> ";
            std::cin >> key >> parameter;
            request = new RequestGet;
            requests.emplace_back(request);
            request->response(key, parameter);
        } else {
            if(command == "get") {
                request = new RequestGet;
                requests.emplace_back(request);
            } else if(command == "put") {
                request = new RequestPut;
                requests.emplace_back(request);            
            } else if(command == "delete") {
                request = new RequestDelete;
                requests.emplace_back(request);                    
            } else if(command == "patch") {
                request = new RequestPatch;
                requests.emplace_back(request);
            } else if(command == "post") {
                request = new RequestPost;
                requests.emplace_back(request);
            } else if(command == "head") {
                request = new RequestHead;
                requests.emplace_back(request);
            } else if(command == "exit" || command == "close") {
                std::cout << "Mischief managed.\n";
                break;
            }

            request->response();
        }

    }
    
    for(auto request : requests) {
        delete request;
    }

    return 0;
}
