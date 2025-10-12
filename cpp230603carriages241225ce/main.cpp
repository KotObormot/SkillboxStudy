#include <iostream>
#include <limits> // для std::numeric_limits
const int TOTAL_CARRIAGES {10};
const int CARRIAGE_CAPACITY_OPTIMAL {20};

int handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        int x {0};
        std::cin >> x;
        // Проверяем на неудачное извлечение
        if (std::cin.fail()) { // предыдущее извлечение не удалось?        
            // да, давайте разберемся с ошибкой
            std::cin.clear(); // возвращаем нас в "нормальный" режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // и удаляем неверные входные данные
            std::cout << "Oops, that input is invalid.  Please try again: ";
        }   
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; // удаляем любые посторонние входные данные
            return x;
        }
    }   
}

#define INVITATION (printf("%s \n", "Specify the number of passengers in each carriage:"))
#define FOR for(int i = 0; i < TOTAL_CARRIAGES; ++i)
#define PASSENGER_ENTRY(i)  ({printf("%s #%d", "Carrige", i); \
                           carriage[i] = handling_invalid_input();})
                           
#define CONSOLE_OUTPUT(i) (printf(#i" = %d \n", i))

#define OVERCROWDED_CARRIAGES (printf("\n%s\n%s\t%s\n", "Overcrowded carriages:", "Carriage#", "Overflow"))

#define OVERFLOW(i) ({if(carriage[i] - CARRIAGE_CAPACITY_OPTIMAL > 0) { \
                           sum += carriage[i]; \
                           printf("\t%d\t%d\n", i, carriage[i] - CARRIAGE_CAPACITY_OPTIMAL);}}       )     

#define INCOPLETE_CARRIAGES (printf("\n%s\n%s\t%s\n", "Incomplete carriges:", "Carriage#", "Free seats"))

#define INCOMPLETE(i) ({if(CARRIAGE_CAPACITY_OPTIMAL - carriage[i] > 0) { \
                           sum += carriage[i]; \
                           printf("\t%d\t%d\n", i, CARRIAGE_CAPACITY_OPTIMAL - carriage[i]);}})

#define COMPLETE(i) ({if(CARRIAGE_CAPACITY_OPTIMAL - carriage[i] == 0) { \
                           sum += carriage[i];}})

#define RESULT (printf("\n%s %d\n", "Total number of passengers on the train:",  sum))

int main() {
   int carriage [TOTAL_CARRIAGES] {};
   INVITATION;
   FOR PASSENGER_ENTRY(i);
   int sum {};
   OVERCROWDED_CARRIAGES;
   FOR OVERFLOW(i);
   INCOPLETE_CARRIAGES;
   FOR INCOMPLETE(i);
   FOR COMPLETE(i);
   RESULT;

   return 0;
}
