//
// Created by fleur on 24/11/2021.
//

#ifndef GOLPHOOK_FUN_INDICATORS_HH
#define GOLPHOOK_FUN_INDICATORS_HH

#include "CommonIncludes.hh"

#include <mutex>
#include <shared_mutex>

#include "Utils/SharedObject.hh"

class Indicators: public SharedObject<Indicators> {
    private:
         struct Indicator {
             std::string _content;
             Color_t _color { 0,0,0,0 };
             Vec3 _pos;

             void draw();

         };

         std::vector<Indicator> _indicatorQueue = {  };
         std::shared_mutex _queueMutex;
    public:

         void push(std::string withContent, Color_t andColor) noexcept;

         void clear() noexcept;

         uint32_t len() noexcept;

         Indicator& at(int32_t index) noexcept;
};



#endif //GOLPHOOK_FUN_INDICATORS_HH
