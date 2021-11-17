//
// Created by fleur on 15/11/2021.
//

#ifndef GOLPHOOK_FUN_UTILS_HH
#define GOLPHOOK_FUN_UTILS_HH

#include "CommonIncludes.hh"

#include "Errors/Fatal.hh"

class Utils {
    public:
         static void allocateConsole();
         static void freeConsole();

         static void waitForModule(std::vector<std::string> inModulesList, uint16_t withTimeout);

         static std::string stringAlign(std::string fromString, uint16_t withSpaces, std::string andSep) noexcept;

         template<class T>
         class Enumerate {

             private:

                  struct _enum {
                      private:
                           Enumerate<T>& _parent;

                      public:
                           uint32_t pos;
                           T& elem;

                           _enum(uint32_t atPos, T& withElem, Enumerate<T>& andParent) noexcept
                                   : pos(atPos),
                                     elem(withElem),
                                     _parent(andParent) {}

                           void erase() noexcept {
                               _parent._safeDeleteQueue.push_back(pos);
                           }
                  };

                  std::vector<_enum> _vec {  };
                  std::vector<uint32_t> _safeDeleteQueue {  };

                  std::vector<T>& _oVec;

             public:

                  Enumerate(std::vector<T>& vec) noexcept : _oVec(vec) {

                      uint32_t count = 0;
                      for ( auto& elem: vec ) {
                          this->_vec.push_back(_enum{ count, elem, *this });
                          count++;
                      }
                  }

                  ~Enumerate() noexcept {

                      uint32_t count = 0;
                      for (auto& toDelPos: this->_safeDeleteQueue) {
                          this->_oVec.erase(this->_oVec.begin() + (toDelPos - count));
                          count++;
                      }
                  }

                  typename std::vector<_enum>::iterator begin() noexcept {

                      return this->_vec.begin();
                  }

                  typename std::vector<_enum>::iterator end() noexcept {

                      return this->_vec.end();
                  }
         };
};


#endif //GOLPHOOK_FUN_UTILS_HH