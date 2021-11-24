//
// Created by fleur on 24/11/2021.
//

#include "Indicators.hh"
#include "Render/DrawQueue.hh"

Indicator::Indicator::_pos = { (App::Get().io.windHeight / 2) + 25, (App::Get().io.windWidth / 2), 0};

void Indicators::Indicator::draw() {
    std::shared_ptr<DrawTextb> aa;
    aa = std::shared_ptr<DrawTextb>{
            new DrawTextb(
                    Vec2<uint32_t>{static_cast<uint32_t>(this->_pos.x), static_cast<uint32_t>(this->_pos.y)},
                    this->_content,
                    this->_color)
    };
    DrawQueue::Get().push(aa);
}

void Indicators::push(std::string withContent, Color_t andColor) noexcept {

    std::unique_lock lock(this->_queueMutex);
    this->_indicatorQueue.push_back({ withContent, andColor });
}

void Indicators::clear() noexcept {

    std::unique_lock lock(this->_queueMutex);
    this->_indicatorQueue.clear();
}

uint32_t Indicators::len() noexcept {

    std::shared_lock lock(this->_queueMutex);
    return this->_indicatorQueue.size();;
}

Indicators::Indicator &Indicators::at(int32_t index) noexcept {

    std::shared_lock lock(this->_queueMutex);

    Indicator& indic = this->_indicatorQueue.at(index);
    indic._pos.x + 10 * index;

    return indic;
}


