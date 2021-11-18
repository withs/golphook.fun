//
// Created by fleur on 15/11/2021.
//

#ifndef GOLPHOOK_FUN_FATAL_HH
#define GOLPHOOK_FUN_FATAL_HH

#include "exception"

class FatalError{

    public:

         class CoreInitException : public std::exception {
             private:
                  std::string _error{};
             public:
                  CoreInitException(std::string withError) : _error{withError} {
                      PLOG_FATAL << _error;
                      MessageBoxA(0, _error.c_str(), "Fatal error (Init)", MB_OK | MB_ICONERROR);
                  }

                  const char* what() const noexcept override {
                      return _error.c_str();
                  }
         };

        class CreateInterfaceError : public std::exception {
            private:
                std::string _error{};
            public:
                 CreateInterfaceError(std::string withError): _error{withError} {
                     PLOG_FATAL << _error;
                     MessageBoxA(0, _error.c_str(), "Fatal error (Interfaces)", MB_OK | MB_ICONERROR);
                 }

                const char* what() const noexcept override {
                    return _error.c_str();
                }
        };

        class GetModuleProcAddrError : public std::exception {
            private:
                std::string _error{};
            public:
                 GetModuleProcAddrError(std::string withError) : _error{withError} {
                     PLOG_FATAL << _error;
                     MessageBoxA(0, _error.c_str(), "Fatal error (GetModuleProcAddr)", MB_OK | MB_ICONERROR);
                 }

                const char* what() const noexcept override {
                    return _error.c_str();
                }
        };

         class ApplyHookError: public std::exception {
             private:
                  std::string _error{};
             public:
                  ApplyHookError(std::string withError) : _error{withError} {
                      PLOG_FATAL << _error;
                      MessageBoxA(0, _error.c_str(), "Fatal error (ApplyHookError)", MB_OK | MB_ICONERROR);
                  }

                  const char* what() const noexcept override {
                      return _error.c_str();
                  }
         };

         class NetvarNullError: public std::exception {
             private:
                  std::string _error{};
             public:
                  NetvarNullError(std::string withError) : _error{withError} {
                      PLOG_FATAL << _error;
                      MessageBoxA(0, _error.c_str(), "Netvar error (NetvarNullError)", MB_OK | MB_ICONERROR);
                  }

                  const char* what() const noexcept override {
                      return _error.c_str();
                  }
         };

};

#endif //GOLPHOOK_FUN_FATAL_HH
