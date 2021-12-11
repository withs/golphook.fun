//
// Created by fleur on 14/11/2021.
//

#include "Functions.hh"

// sheeeesh ez copy pasta ^^
void Functions::SetClantag(std::string withText) {
    static auto fnClantagChanged = (int(__fastcall*)(const char*, const char*))Mem::patternScan(GetModuleHandleA("engine.dll"), "53 56 57 8B DA 8B F9 FF 15");
    fnClantagChanged(withText.c_str(), withText.c_str());
}
