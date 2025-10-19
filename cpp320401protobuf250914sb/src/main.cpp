#include <iostream>
#include "enterprise.pb.h"

int main() {
    Enterprise enterprise;
    enterprise.set_name("ОАО Ромашка");
    enterprise.set_foundation_year(2000);
    enterprise.set_legal_address("г. Москва, ул. Ленина, д. 1");
    enterprise.set_activity_type("Производство");
    enterprise.set_has_foreign_activity(true);

    std::cout << "Название: " << enterprise.name() << std::endl;
    return 0;
}

