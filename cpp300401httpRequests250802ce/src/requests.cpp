
//#include <cpr/cpr.h>
#include "requests.h"

void RequestGet::response() {
    cpr::Response r = cpr::Get(cpr::Url("http://httpbin.org/get"));
    std::cout << r.text
              << "\n" << "url: " << "\t" << r.url
              << "\n" << "status_code:" << "\t" << r.status_code
              << "\n";
}

void RequestGet::response(std::string& key, std::string& parameter) {
    cpr::Response r = cpr::Get(cpr::Url("http://httpbin.org/get")
                        , cpr::Parameters{{key.c_str(), parameter.c_str()}}
                    );
    std::cout << r.text
              << "\n" << "url: " << "\t" << r.url
              << "\n" << "status_code:" << "\t" << r.status_code
              << "\n";
}
void RequestPost::response() {
    std::string name, city;
    std::cout << "Name, City--> ";
    std::cin >> name >> city;
    cpr::Response r = cpr::Post(cpr::Url("http://httpbin.org/post")
                            , cpr::Payload({{"name", name.c_str()}
                                            , {"city", city.c_str()}}));
    std::cout << r.text << "\n";    
}

void RequestDelete::response() {
    cpr::Response r = cpr::Delete(cpr::Url("http://httpbin.org/delete"));
    std::cout << r.text << "\n";
}

void RequestPatch::response() {
    cpr::Response r = cpr::Patch(cpr::Url("http://httpbin.org/patch"));
    std::cout << r.text << "\n";
}

void RequestPut::response() {
    cpr::Response r = cpr::Put(cpr::Url("http://httpbin.org/put"));
    std::cout << r.text << "\n";
}

void RequestHead::response() {
    cpr::Response r = cpr::Get(cpr::Url("http://skillbox.ru/"));
        std::cout //<< r.text
              << "\n" << "status_code:" << "\t" << r.status_code
              << "\n" << "content-type:" << "\t" << r.header["content-type"]
//              << "\n" << "Accept:" << "\t" << r.header["Accept"]
//              << "\n" << "Accept-Encoding:" << "\t" << r.header["Accept-Encoding"]
//              << "\n" << "Host:" << "\t" << r.header["Host"]
//              << "\n" << "User-Agent:" << "\t" << r.header["User-Agent"]
              << "\n";
}
