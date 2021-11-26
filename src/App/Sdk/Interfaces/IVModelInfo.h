//
// Created by fleur on 26/11/2021.
//

#ifndef GOLPHOOK_FUN_IVMODELINFO_H
#define GOLPHOOK_FUN_IVMODELINFO_H

class IVModelInfo {
    public:
         void* getModel(int index) {
             return Mem::callVirtual< void*, 1, int >(this, index);
         }

         int getModelIndex(const char* file_name) {
             return Mem::callVirtual< int, 2, const char* >(this, file_name);
         }

         const char* getModelName(const void* model) {
             return Mem::callVirtual< const char*, 3, const void* >(this, model);
         }

         void* getStudioModel(const void* model) {
             return Mem::callVirtual< void*, 32, const void* >(this, model);
         }
};

#endif //GOLPHOOK_FUN_IVMODELINFO_H
