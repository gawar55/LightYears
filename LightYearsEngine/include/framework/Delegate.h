#pragma once
#include "framework/Core.h"
#include <functional>

namespace ly
{   
    class Object;

    template<typename... Args>
    class Delegate
    {
    public:

        template<typename ClassName>
        void BindAction(weak<Object> Obj, void(ClassName::*callback)(Args...))
        {
            std::function<bool(Args...)> callbackFunc = [Obj, callback](Args... args)->bool
            {
                if(!Obj.expired())
                {
                    (static_cast<ClassName*>(Obj.lock().get())->*callback)(args...);
                    return true;
                }
                return false;
            };
            mCallbacks.push_back(callbackFunc);
        }

        void Broadcast(Args... args)
        {
            for(auto iter = mCallbacks.begin(); iter != mCallbacks.end();)
            {
                if((*iter)(args...))
                {
                    ++iter;
                }
                else
                {
                    iter = mCallbacks.erase(iter);
                }
            }
        }

    private:
        List<std::function<bool(Args...)>> mCallbacks;
    };
} // namespace ly
