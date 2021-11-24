//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_CONFIG_HH
#define GOLPHOOK_FUN_CONFIG_HH

#include "CommonIncludes.hh"

#include "filesystem"
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <Utils/Structs/Vector.hh>

#include "Utils/SharedObject.hh"
#include "Utils/Structs/Color.hh"
#include "Utils/Utils.hh"

#include "nlohmann/json.hpp"
#include "libbase64.h"


struct Config_t {

    std::string name;

    // visuals
    bool snaplines = false;
    Color_t snaplinesCol = Color_t{ 255, 255, 255, 255 };
    Color_t snaplinesColOcl = Color_t{ 255, 255, 255, 255 };

    bool boxe = false;
    Color_t boxeCol = Color_t{ 255, 255, 255, 255 };
    Color_t boxeColOcl = Color_t{ 255, 255, 255, 255 };

    bool watermark = false;
    Color_t watermarkCol = Color_t{ 255, 255, 255, 255 };

    // misc

    bool indicators = false;
    Color_t indicatorsCol = Color_t{ 255, 255, 255, 255 };

    bool viewmodel = false;
    float fov = 0.f;
    float viewmodelFov = 68.f;
    Vec3 viewmodelOff = { 0.f, 0.f, 0.f };
    Vec3 viewmodelAngOff = { 0.f, 0.f, 0.f };

    bool bop = false;
    bool tag = false;
    bool fovCircle = false;

    // engine

    bool engine = false;
    float engineFov = 0.f;
    std::vector<uint32_t> engineBones = {  };
    uint32_t enginePrefBone = 0;
    uint32_t engineOnKeyForceBone = 0;


    int inslider = 0;

};

class Config: public SharedObject<Config> {
    private:
         std::vector<Config_t> _configList { Config_t("_") };
         std::shared_mutex _confMutex;

    public:

         Config_t* currentConfig = &_configList[0];

         Config();

         Config_t& currentCfg();
         void setCurrentConfig(int32_t index);

         void loadConfigFromFile(std::filesystem::path fromPath);
         void loadConfigFromName(std::string withName);
         void saveConfigToFile(std::string withName);
};


#endif //GOLPHOOK_FUN_CONFIG_HH
