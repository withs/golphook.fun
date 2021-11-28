//
// Created by fleur on 14/11/2021.
//

#include "Config.hh"
#include "App.hh"


Config::Config() {

    std::string path = std::string(InterfacesCollection::i_engineClient->GetGameDirectory()) + std::string("\\golp");

    std::filesystem::path p1(path);
    std::filesystem::path p2(path + std::string("\\cfg"));

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

        fromFileConfig.snaplinesColOcl.r = inputJson["cfg"]["snaplinesColOcl"]["r"];
        fromFileConfig.snaplinesColOcl.g  = inputJson["cfg"]["snaplinesColOcl"]["g"];
        fromFileConfig.snaplinesColOcl.b  = inputJson["cfg"]["snaplinesColOcl"]["b"];
        fromFileConfig.snaplinesColOcl.a  = inputJson["cfg"]["snaplinesColOcl"]["a"];


        fromFileConfig.boxe = inputJson["cfg"]["boxe"];
        fromFileConfig.boxeCol.r = inputJson["cfg"]["boxeCol"]["r"];
        fromFileConfig.boxeCol.g  = inputJson["cfg"]["boxeCol"]["g"];
        fromFileConfig.boxeCol.b  = inputJson["cfg"]["boxeCol"]["b"];
        fromFileConfig.boxeCol.a  = inputJson["cfg"]["boxeCol"]["a"];

        fromFileConfig.boxeColOcl.r = inputJson["cfg"]["boxeColOcl"]["r"];
        fromFileConfig.boxeColOcl.g  = inputJson["cfg"]["boxeColOcl"]["g"];
        fromFileConfig.boxeColOcl.b  = inputJson["cfg"]["boxeColOcl"]["b"];
        fromFileConfig.boxeColOcl.a  = inputJson["cfg"]["boxeColOcl"]["a"];

        fromFileConfig.names = inputJson["cfg"]["names"];
        fromFileConfig.namesCol.r = inputJson["cfg"]["namesCol"]["r"];
        fromFileConfig.namesCol.g  = inputJson["cfg"]["namesCol"]["g"];
        fromFileConfig.namesCol.b  = inputJson["cfg"]["namesCol"]["b"];
        fromFileConfig.namesCol.a  = inputJson["cfg"]["namesCol"]["a"];

        fromFileConfig.namesColOcl.r = inputJson["cfg"]["namesColOcl"]["r"];
        fromFileConfig.namesColOcl.g  = inputJson["cfg"]["namesColOcl"]["g"];
        fromFileConfig.namesColOcl.b  = inputJson["cfg"]["namesColOcl"]["b"];
        fromFileConfig.namesColOcl.a  = inputJson["cfg"]["namesColOcl"]["a"];

        fromFileConfig.watermark = inputJson["cfg"]["watermark"];
        fromFileConfig.watermarkCol.r = inputJson["cfg"]["watermarkCol"]["r"];
        fromFileConfig.watermarkCol.g  = inputJson["cfg"]["watermarkCol"]["g"];
        fromFileConfig.watermarkCol.b  = inputJson["cfg"]["watermarkCol"]["b"];
        fromFileConfig.watermarkCol.a  = inputJson["cfg"]["watermarkCol"]["a"];

        fromFileConfig.indicators = inputJson["cfg"]["indicators"];
        fromFileConfig.indicatorsCol.r = inputJson["cfg"]["indicatorsCol"]["r"];
        fromFileConfig.indicatorsCol.g  = inputJson["cfg"]["indicatorsCol"]["g"];
        fromFileConfig.indicatorsCol.b  = inputJson["cfg"]["indicatorsCol"]["b"];
        fromFileConfig.indicatorsCol.a  = inputJson["cfg"]["indicatorsCol"]["a"];

        fromFileConfig.fovCircle = inputJson["cfg"]["fovCircle"];
        fromFileConfig.fovCircleCol.r  = inputJson["cfg"]["fovCircleCol"]["r"];
        fromFileConfig.fovCircleCol.g  = inputJson["cfg"]["fovCircleCol"]["g"];
        fromFileConfig.fovCircleCol.b  = inputJson["cfg"]["fovCircleCol"]["b"];
        fromFileConfig.fovCircleCol.a  = inputJson["cfg"]["fovCircleCol"]["a"];

        fromFileConfig.viewmodel = inputJson["cfg"]["viewmodel"];
        fromFileConfig.viewmodelOff.x = inputJson["cfg"]["viewmodelOffs"]["x"];
        fromFileConfig.viewmodelOff.y = inputJson["cfg"]["viewmodelOffs"]["y"];
        fromFileConfig.viewmodelOff.z = inputJson["cfg"]["viewmodelOffs"]["z"];
        fromFileConfig.viewmodelAngOff.x = inputJson["cfg"]["viewmodelOffs"]["yaw"];
        fromFileConfig.viewmodelAngOff.y = inputJson["cfg"]["viewmodelOffs"]["pitch"];
        fromFileConfig.viewmodelAngOff.z = inputJson["cfg"]["viewmodelOffs"]["roll"];
        fromFileConfig.viewmodelFov = inputJson["cfg"]["viewmodelOffs"]["viewmodelFov"];
        fromFileConfig.fov = inputJson["cfg"]["viewmodelOffs"]["fov"];

        fromFileConfig.bop = inputJson["cfg"]["bop"];
        fromFileConfig.tag = inputJson["cfg"]["tag"];

        fromFileConfig.engine = inputJson["cfg"]["engine"];
        fromFileConfig.engineFov = inputJson["cfg"]["engineSettings"]["fov"];
        //fromFileConfig.engineBones = inputJson["cfg"]["engineSettings"]["bones"];

        fromFileConfig.enginePrefBone = inputJson["cfg"]["engineSettings"]["prefBone"];
        fromFileConfig.engineOnKeyForceBone = inputJson["cfg"]["engineSettings"]["onKeyForceBone"];

        this->_configList.push_back(fromFileConfig);
    } catch (std::exception& e) {
        PLOGD << e.what();
        // TODO: throw: Failed to laod json content, it can be corrupted
    }

}

void Config::loadConfigFromName(std::string withName) {

    std::string path = std::string(InterfacesCollection::i_engineClient->GetGameDirectory()) + std::string("\\golp\\cfg\\" + withName + ".gcfg");
    std::filesystem::path configFilePath(path);
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
        {"snaplinesColOcl", {
            {"r", this->currentCfg().snaplinesColOcl.r},
            {"g", this->currentCfg().snaplinesColOcl.g},
            {"b", this->currentCfg().snaplinesColOcl.b},
            {"a", this->currentCfg().snaplinesColOcl.a}
        }},
        {"boxe", this->currentCfg().boxe},
        {"boxeCol", {
            {"r", this->currentCfg().boxeCol.r},
            {"g", this->currentCfg().boxeCol.g},
            {"b", this->currentCfg().boxeCol.b},
            {"a", this->currentCfg().boxeCol.a}
        }},
        {"boxeColOcl", {
            {"r", this->currentCfg().boxeColOcl.r},
            {"g", this->currentCfg().boxeColOcl.g},
            {"b", this->currentCfg().boxeColOcl.b},
            {"a", this->currentCfg().boxeColOcl.a}
        }},
        {"names", this->currentCfg().names},
        {"namesCol", {
            {"r", this->currentCfg().namesCol.r},
            {"g", this->currentCfg().namesCol.g},
            {"b", this->currentCfg().namesCol.b},
            {"a", this->currentCfg().namesCol.a}
        }},
        {"namesColOcl", {
            {"r", this->currentCfg().namesColOcl.r},
            {"g", this->currentCfg().namesColOcl.g},
            {"b", this->currentCfg().namesColOcl.b},
            {"a", this->currentCfg().namesColOcl.a}
        }},
        {"watermark", this->currentCfg().watermark},
        {"watermarkCol", {
            {"r", this->currentCfg().watermarkCol.r},
            {"g", this->currentCfg().watermarkCol.g},
            {"b", this->currentCfg().watermarkCol.b},
            {"a", this->currentCfg().watermarkCol.a}
        }},

        {"indicators", this->currentCfg().indicators},
        {"indicatorsCol", {
            {"r", this->currentCfg().indicatorsCol.r},
            {"g", this->currentCfg().indicatorsCol.g},
            {"b", this->currentCfg().indicatorsCol.b},
            {"a", this->currentCfg().indicatorsCol.a}
        }},
        {"fovCircle", this->currentCfg().snaplines},
        {"fovCircleCol", {
            {"r", this->currentCfg().fovCircleCol.r},
            {"g", this->currentCfg().fovCircleCol.g},
            {"b", this->currentCfg().fovCircleCol.b},
            {"a", this->currentCfg().fovCircleCol.a}
        }},
        {"viewmodel", this->currentCfg().viewmodel},
        {"viewmodelOffs", {
            {"x", this->currentCfg().viewmodelOff.x},
            {"y", this->currentCfg().viewmodelOff.y},
            {"z", this->currentCfg().viewmodelOff.z},
            {"yaw", this->currentCfg().viewmodelAngOff.x},
            {"pitch", this->currentCfg().viewmodelAngOff.y},
            {"roll", this->currentCfg().viewmodelAngOff.z},
            {"fov", this->currentCfg().fov},
            {"viewmodelFov", this->currentCfg().viewmodelFov}
        }},
        {"bop", this->currentCfg().bop},
        {"tag", this->currentCfg().tag},

        {"engine", this->currentCfg().engine},
        {"engineSettings", {
            {"fov", this->currentCfg().engineFov},
            //{"bones", this->currentCfg().engineBones},
            {"prefBone", this->currentCfg().enginePrefBone},
            {"onKeyForceBone", this->currentCfg().engineOnKeyForceBone}
        }}
    };
    std::string outputJsonString = outputJson.dump();

    std::string path = std::string(InterfacesCollection::i_engineClient->GetGameDirectory()) + std::string("\\golp\\cfg\\" + withName + ".gcfg");
    std::filesystem::path configFilePath(path);

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
