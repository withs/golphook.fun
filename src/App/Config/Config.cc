//
// Created by fleur on 14/11/2021.
//

#include "Config.hh"

Config::Config() {

    std::filesystem::path p1("C:\\Users\\fleur\\Documents\\golp");
    std::filesystem::path p2("C:\\Users\\fleur\\Documents\\golp\\cfg");

    if ( !std::filesystem::exists(p1) )
        std::filesystem::create_directory(p1);

    if ( !std::filesystem::exists(p2) ) {
        std::filesystem::create_directory(p2);
        this->saveConfigToFile("_");
    }

    for ( auto& entry: std::filesystem::directory_iterator(p2) ) {
        std::cout << entry.path() << std::endl;
    }
}

void Config::loadConfigFromFile(std::filesystem::path fromPath) {

    std::ifstream configFile (fromPath, std::ifstream::in);

    if ( !configFile.is_open() || !configFile.good() )
        return;
        // TODO: throw error : cannot open config file


    std::string inputJsonString;
    std::fstream::iostate readResult;

    std::getline(configFile, inputJsonString);

    nlohmann::json inputJson = nlohmann::json::parse(inputJsonString);

    if ( inputJson["name"] == "_" )
        return;
        // TODO: throw: default config overwrite

    try {
        Config_t fromFileConfig { inputJson["name"] };

        fromFileConfig.snaplines = inputJson["cfg"]["snaplines"];
        fromFileConfig.snaplinesCol.r = inputJson["cfg"]["snaplinesCol"]["r"];
        fromFileConfig.snaplinesCol.g  = inputJson["cfg"]["snaplinesCol"]["g"];
        fromFileConfig.snaplinesCol.b  = inputJson["cfg"]["snaplinesCol"]["b"];
        fromFileConfig.snaplinesCol.a  = inputJson["cfg"]["snaplinesCol"]["a"];

        fromFileConfig.boxe = inputJson["cfg"]["boxe"];
        fromFileConfig.boxeCol.r = inputJson["cfg"]["boxeCol"]["r"];
        fromFileConfig.boxeCol.g  = inputJson["cfg"]["boxeCol"]["g"];
        fromFileConfig.boxeCol.b  = inputJson["cfg"]["boxeCol"]["b"];
        fromFileConfig.boxeCol.a  = inputJson["cfg"]["boxeCol"]["a"];

        fromFileConfig.watermark = inputJson["cfg"]["watermark"];
        fromFileConfig.watermarkCol.r = inputJson["cfg"]["watermarkCol"]["r"];
        fromFileConfig.watermarkCol.g  = inputJson["cfg"]["watermarkCol"]["g"];
        fromFileConfig.watermarkCol.b  = inputJson["cfg"]["watermarkCol"]["b"];
        fromFileConfig.watermarkCol.a  = inputJson["cfg"]["watermarkCol"]["a"];

        this->_configList.push_back(fromFileConfig);
    } catch (std::exception& e) {
        PLOGD << e.what();
        // TODO: throw: Failed to laod json content, it can be corrupted
    }

}

void Config::loadConfigFromName(std::string withName) {

    std::filesystem::path configFilePath("C:\\Users\\fleur\\Documents\\golp\\cfg\\" + withName + ".gcfg");
    this->loadConfigFromFile(configFilePath);

    int32_t count = 0;
    for ( auto entry: this->_configList ) {
        if ( entry.name == withName ) {
            this->setCurrentConfig(count);
        }
        count++;
    }
}

void Config::saveConfigToFile(std::string withName) {

    if ( withName == "_" )
        return;
        // TODO: throw: default config overwrite


    nlohmann::json outputJson;
    outputJson["name"] = withName;
    outputJson["cfg"] = {
            {"snaplines", this->currentCfg().snaplines},
            {"snaplinesCol", {
                    {"r", this->currentCfg().snaplinesCol.r},
                    {"g", this->currentCfg().snaplinesCol.g},
                    {"b", this->currentCfg().snaplinesCol.b},
                    {"a", this->currentCfg().snaplinesCol.a}
            }},
            {"boxe", this->currentCfg().boxe},
            {"boxeCol", {
                                  {"r", this->currentCfg().boxeCol.r},
                                  {"g", this->currentCfg().boxeCol.g},
                                  {"b", this->currentCfg().boxeCol.b},
                                  {"a", this->currentCfg().boxeCol.a}
                          }},
            {"watermark", this->currentCfg().watermark},
            {"watermarkCol", {
                        {"r", this->currentCfg().watermarkCol.r},
                        {"g", this->currentCfg().watermarkCol.g},
                        {"b", this->currentCfg().watermarkCol.b},
                        {"a", this->currentCfg().watermarkCol.a}
            }}
    };
    std::string outputJsonString = outputJson.dump();

    std::filesystem::path configFilePath("C:\\Users\\fleur\\Documents\\golp\\cfg\\" + withName + ".gcfg");

    std::ofstream configFile (configFilePath, std::ofstream::out);

    if ( !configFile.is_open() || !configFile.good() )
        // TODO: throw error : cannot save config to file
        return;

    configFile << outputJsonString;
    configFile.close();
}

Config_t& Config::currentCfg() {
    std::shared_lock lock(this->_confMutex);
    return *this->currentConfig;
}

void Config::setCurrentConfig(int32_t index) {
    std::unique_lock(this->_confMutex);
    this->currentConfig = &this->_configList[index];
}
