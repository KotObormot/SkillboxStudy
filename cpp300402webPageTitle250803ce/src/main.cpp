#include "common.h"
#include "loclib.h"

#define DEBUG false

int main() {
    using namespace std::literals;

    std::cout << "Hello\n"
              << "Specify the URL of the web page or click \"EXIT\" to exit."
              << "\n";
    while(true) { 
        std::cout << "user@computer:~$ ";
        std::string siteURL(correctCommandInput());
        
        while(siteURL.substr(0, 4) != "http"
                && siteURL != "exit"
                && siteURL != "close") {
            std::cout << "Try again--> ";
            siteURL = correctCommandInput();
        }
        if(siteURL == "exit" || siteURL == "close") {
            std::cout << "Mischief managed.\n";
            break;
        }

        cpr::Response r = cpr::Get(cpr::Url(siteURL)
                        , cpr::Header({{"Accept"
                            , "text/html"}}));
        std::cout << "\n" << "url: " << "\t" << r.url
                  << "\n" << "status_code:" << "\t" << r.status_code
                  << "\n";
        
        size_t strB(0);
        size_t strE(0);

        if (r.text.find("<h1>") != std::string::npos
                && r.text.find("</h1>") != std::string::npos) {
            strB = r.text.find("<h1>");
            strE = r.text.find("</h1>");
            std::cout << r.text.substr(strB + 4, strE - strB - 4) << "\n"; 
        } 

        if (r.text.find("<title>") != std::string::npos
                && r.text.find("</title>") != std::string::npos) {
            strB = r.text.find("<title>");
            strE = r.text.find("</title>");
            std::cout << r.text.substr(strB + 7, strE - strB - 7) << "\n";            
        } 
    }

    return 0;
}
