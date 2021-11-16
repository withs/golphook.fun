//
// Created by fleur on 15/11/2021.
//

#include "Utils.hh"

FILE* f;

void Utils::allocateConsole() {

    if ( !AllocConsole() ) {
        throw std::runtime_error("Failed to allocate console");
    }

    if ( freopen_s(&f, "CONOUT$", "w", stdout) ) {
        throw std::runtime_error("Failed to open previously allocated console");
    }
}

void Utils::freeConsole() {

    if ( fclose(f) != 0 ) {
        throw std::runtime_error("Failed to close console previously allocated console");
        return;
    }

    if ( !FreeConsole() ) {
        throw std::runtime_error("Failed to free console");
        return;
    }
}

void Utils::waitForModule(std::vector<std::string> inModulesList, uint16_t withTimeout) {

    uint16_t totalWaited = 0;

    while ( true ) {
        uint16_t index = 0;
        for ( auto& elem: inModulesList ) {
            if(GetModuleHandleA(elem.c_str())) {
                PLOGD << "module " << elem << " ok\n";
                inModulesList.erase(inModulesList.begin() + index);
            }
            index++;
        }

        if ( inModulesList.size() != 0 ) {
            if( totalWaited < withTimeout ) {
                PLOGD << "waiting for another check " << totalWaited << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                totalWaited++;
            } else {
                PLOGD << "some module arn't laoded\n";
                throw FatalError::CoreInitException("Some game module failed to load");
                break;
            }
        } else {
            PLOGD << "all modules laoded\n";
            break;
        }
    }

}

std::string Utils::stringAlign(std::string fromString, uint16_t withSpaces, std::string andSep) noexcept {
    std::stringstream final;
    final << fromString;

    int32_t ss;
    if ( ( ss = fromString.length() - withSpaces) < 0 ) ss *= -1;
    for ( uint16_t i = 0; i != ss; i++ ) final << " ";

    final << andSep << " ";
    return final.str();
}