//
// Created by fleur on 17/11/2021.
//

#include "DrawQueue.hh"

DrawQueue::DrawQueue() {

}

void DrawQueue::push(std::shared_ptr<DrawToolBase> drawAction) noexcept {
    std::unique_lock lock(this->_queueMutex);
    this->_queue.push_back(drawAction);
}

uint32_t DrawQueue::len() noexcept {

    std::shared_lock lock(this->_queueMutex);
    return this->_queue.size();;
}

std::vector<std::shared_ptr<DrawToolBase>>::iterator DrawQueue::begin() noexcept {

    std::shared_lock lock(this->_queueMutex);
    return this->_queue.begin();
}

std::vector<std::shared_ptr<DrawToolBase>>::iterator DrawQueue::end() noexcept {

    std::shared_lock lock(this->_queueMutex);
    return this->_queue.end();
}

void DrawQueue::clear() noexcept {

    std::unique_lock lock(this->_queueMutex);
    this->_queue.clear();
}


std::shared_ptr<DrawToolBase> DrawQueue::operator[](int32_t index) {
    std::shared_lock lock(this->_queueMutex);
    return this->_queue.at(index);
}
