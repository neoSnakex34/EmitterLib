#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

template <typename S> class Listener
{
  public:
    virtual ~Listener() = default;
    virtual void onEvent(const S& signal) = 0;
};

/*
*/
template <typename T> class Emitter
{
  public:
    // subscribers are weak_ptr to Listener inherited
    void subscribe(std::weak_ptr<Listener<T>> listener)
    {
        subscribers.emplace_back(listener);
    }
    void emit(const T &signal)
    {
        auto subscriber_iterator = subscribers.begin();
        while (subscriber_iterator != subscribers.end())
        {
            if (std::shared_ptr<Listener<T>> shared_listener = subscriber_iterator->lock()) {
              shared_listener->onEvent(signal);
              ++subscriber_iterator; 
            }
            else
            {
                subscriber_iterator = subscribers.erase(subscriber_iterator);
            }
        }
    }

  private:
    std::vector<std::weak_ptr<Listener<T>>> subscribers;

};
