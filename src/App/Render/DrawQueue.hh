//
// Created by fleur on 17/11/2021.
//

#ifndef GOLPHOOK_FUN_DRAWQUEUE_HH
#define GOLPHOOK_FUN_DRAWQUEUE_HH

#include "CommonIncludes.hh"
#include "App.hh"

#include "Utils/SharedObject.hh"

#include "DrawTools.hh"
#include "DrawItemsCollection.hh"

#include <thread>
#include <mutex>
#include <shared_mutex>


class DrawQueue: public SharedObject<DrawQueue> {
    private:
         std::shared_mutex _queueMutex;
         std::vector<std::shared_ptr<DrawToolBase>> _queue { };

    public:

         DrawQueue();

         void push(std::shared_ptr<DrawToolBase> drawAction) noexcept;

         uint32_t len() noexcept;

         std::vector<std::shared_ptr<DrawToolBase>>::iterator begin() noexcept;

         std::vector<std::shared_ptr<DrawToolBase>>::iterator end() noexcept;

         void clear() noexcept;
};


#endif //GOLPHOOK_FUN_DRAWQUEUE_HH
