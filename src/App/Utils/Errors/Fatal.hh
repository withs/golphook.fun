//
// Created by fleur on 15/11/2021.
//

#ifndef GOLPHOOK_FUN_FATAL_HH
#define GOLPHOOK_FUN_FATAL_HH

#include "exception"

#include "../../CommonIncludes.hh"

class FatalError{

    public:

         class CoreInitException : public std::exception {
             private:
                  std::string _error{};
             public:
                  CoreInitException(std::string withError) : _error{withError} { }

                  const char* what() const noexcept override {
                      PLOG_FATAL << _error;
                      MessageBoxA(0, "Fatal error (Init)", _error.c_str(), MB_OK | MB_ICONERROR);
                      return _error.c_str();
                  }
         };

        class CreateInterfaceError : public std::exception {
            private:
                std::string _error{};
            public:
                 CreateInterfaceError(std::string withError): _error{withError} { }

                const char* what() const noexcept override {
                    PLOG_FATAL << _error;
                    MessageBoxA(0, "Fatal error (Interfaces)", _error.c_str(), MB_OK | MB_ICONERROR);
                    return _error.c_str();
                }
        };

        class GetModuleProcAddrError : public std::exception {
            private:
                std::string _error{};
            public:
                 GetModuleProcAddrError(std::string withError) : _error{withError} { }

                const char* what() const noexcept override {
                PLOG_FATAL << _error;
                MessageBoxA(0, "Fatal error (GetModuleProcAddr)", _error.c_str(), MB_OK | MB_ICONERROR);
                return _error.c_str();
                }
        };

         class ApplyHookError: public std::exception {
             private:
                  std::string _error{};
             public:
                  ApplyHookError(std::string withError) : _error{withError} { }

                  const char* what() const noexcept override {
                      PLOG_FATAL << _error;
                      MessageBoxA(0, "Fatal error (ApplyHookError)", _error.c_str(), MB_OK | MB_ICONERROR);
                      return _error.c_str();
                  }
         };

};

#endif //GOLPHOOK_FUN_FATAL_HH
