#include <iostream>
#include <cstdio>
#include <sstream>

enum switches 
{
    LIGHTS_INSIDE = 1, 
    LIGHTS_OUTSIDE = 2, 
    HEATERS = 4, 
    WATER_PIPE_HEATING = 8, 
    CONDITIONER = 16,
    Power_Entire_House = 32,
    Home_Sockets = 64
};

int colorTemperature = 5000;
int currentSwitchPosition = 111; // all ON, withoot CONDITIONER

void lightsInside(std::string lights, int time) {
    int lightInHouse = lights == "off" ? 0 : (lights == "on" ? 1 : 1);        
    int time_o = time % 24;
    if(time_o >= 0 && time_o <= 16) {
        colorTemperature = 5000;
    } else if(time_o > 16 && time_o <= 20) {
        if(lightInHouse) {
            colorTemperature -= 575;
        }
    }
    if(lightInHouse ^ (currentSwitchPosition & LIGHTS_INSIDE)) { // The switch has changed
        if(lightInHouse) {
            currentSwitchPosition |= LIGHTS_INSIDE;
            std::cout << "\tThe lights in the house are on. Color temperature is " << colorTemperature << " K.\n";
        } else {
            currentSwitchPosition &= ~LIGHTS_INSIDE;
            std::cout << "\tThe lights in the house are turned off." <<  "\n";
        }
    } else { //nothing changed
        if(lightInHouse) {
            std::cout << "\tColor temperature is " << colorTemperature << " K.\n";
        }
    }
    
    return;
}

void lightsInTheGarden(std::string movInGarden, int time) {
    int isDark = ((time < 5 || time >=16) && (time < 29 || time >= 40)) ? 2 : 0;
    int lightInGgarden = (movInGarden == "no") ? 0 : ((movInGarden == "yes") ? 2 : 2);
    if((lightInGgarden & isDark) ^ (currentSwitchPosition & LIGHTS_OUTSIDE)) { // The switch has changed
        if(lightInGgarden && isDark) {
            currentSwitchPosition |= LIGHTS_OUTSIDE;
            std::cout << "\tNight. There is someone in the garden. Lights on.\n";
        } else {
            currentSwitchPosition &= ~LIGHTS_OUTSIDE;
            std::cout << "\tThe garden is empty. The lights are turned off.\n";
        }
    }
    
    return;
}

void waterPapeHeating(int t) {
    int isColdOutside = (t <= 0) ? 8 : 0;
    int isWarmOutside = (t > 5) ? -9 : 0;        
    if(currentSwitchPosition & WATER_PIPE_HEATING) {   // The water heating system is already turned on.
        if(isColdOutside) {
            std::cout << "\tIt's cold outside (t = " << t << "). The water heating system is already turned on.\n";
        } else if(isWarmOutside) {
            currentSwitchPosition &= ~WATER_PIPE_HEATING;
            std::cout << "\tIt's getting warmer outside (t = " << t << "). Turn off the heating of the water supply.\n";
        } else {
            std::cout << "\tIt's cold outside (t = " << t << "). The hot water heating system remains on.\n";
        }
    } else { // The water heating system is already turned off.
        if(isColdOutside) {
            currentSwitchPosition |= WATER_PIPE_HEATING;
            std::cout << "\tIt got cold outside (t = " << t << "). Turn on the heating of the water supply.\n";
        } else if(isWarmOutside) {
            std::cout << "\tWarm outside (t = " << t << "). There is no need to turn on the heating of the water supply.\n";
        } else {
            std::cout << "\tIt's still warm outside. (t = " << t << "). There is no need to turn on the heating of the water supply.\n";
        }
    }

    return;
}

void homeHeating(int t) {
    int isColdInside = (t < 22) ? 4 : 0;
    int isWarmInside = (t > 25 && t < 30) ? -5 : 0;
    int isHotInside = (t >= 30) ? 16 : 0;
    int isComfortInside = (t >= 22 && t <= 25) ? -17 : 0;

    if(currentSwitchPosition & HEATERS) {   // The heater is already turned on.
        if(isColdInside) {
            std::cout << "\tIt's cold inside (t = " << t << "). The heater is already turned on.\n";
        } else if(isWarmInside) {
            currentSwitchPosition &= ~HEATERS;
            std::cout << "\tIt's getting warmer inside (t = " << t << "). Turn off the heater.\n";
        }
    } else { // The heater is already turned off.
        if(isColdInside) {
            currentSwitchPosition |= HEATERS;
            std::cout << "\tIt got cold inside (t = " << t << "). Turn on the heater.\n";
        } else if(isWarmInside) {
            std::cout << "\tWarm inside (t = " << t << "). There is no need to turn on the heater.\n";
        }
    }

    if(currentSwitchPosition & CONDITIONER) {   // The conditioner is already turned on.
        if(isHotInside) {
            std::cout << "\tIt's hot inside (t = " << t << "). The conditioner is already turned on.\n";
        } else if(isComfortInside) {
            currentSwitchPosition &= ~CONDITIONER;
            std::cout << "\tIt's comfortable inside (t = " << t << "). Turn off the conditioner.\n";
        }
    } else { // The conditioner is already turned off.
        if(isHotInside) {
            currentSwitchPosition |= CONDITIONER;
            std::cout << "\tIt got hot inside (t = " << t << "). Turn on the conditioner.\n";
        } else if(isComfortInside) {
            std::cout << "\tIt's comfortable inside (t = " << t << "). There is no need to turn on the conditioner.\n";
        }
    }
    
    return;
}

int main() {
    std::cout << "Disclaimer: at the start of the smart home model, all appliances are turned on, with the exception of the air conditioner.\n";
    for(int time = 0; time < 48; time++) {
        std::printf("%dst day, %d:00 o'clock.\n", time / 24 + 1, time % 24);
        double temperatureOutside, temperatureInside = 0;
        std::string movement, lights, buffer;
        std::cout << "Input temperature inside (degrees Celsius), temperature outside (degrees Celsius), "
                  << "is there movement outside (yes/no), are the lights on in the house (on/off): ";
        std::getline(std::cin, buffer);
        std::stringstream temp_stream(buffer);
        temp_stream >> temperatureInside >> temperatureOutside >> movement >> lights;
        
        lightsInside(lights, time);
        lightsInTheGarden(movement, time);
        waterPapeHeating(temperatureOutside);
        homeHeating(temperatureInside);
    }


    return 0;
}
