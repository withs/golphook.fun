//
// Created by fleur on 14/11/2021.
//

#include "Features.hh"

Features::Features() {
    this->visuals = std::make_unique<Visuals>();
    this->others = std::make_unique<Others>();
    this->engine = std::make_unique<Engine>();
    this->skins = std::make_unique<Skins>();
}