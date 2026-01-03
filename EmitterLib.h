#pragma once
#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>

template <typename S> class Listener
{
  public:
    virtual ~Listener() = default;
    virtual void onEvent(const S &signal) = 0;
};

/*
 */
template <typename T> class Emitter
{
  public:

    using SubscriptionId = std::uint64_t;
    
    // subscribers are weak_ptr to Listener inherited
    SubscriptionId subscribe(std::weak_ptr<Listener<T>> listener)
    {
        const SubscriptionId id = next_id++; 
        subscribers.emplace(id, std::move(listener));
        return id; 
    }

    void unsubscribe(SubscriptionId id) {
      subscribers.erase(id);
    }

    void emit(const T &signal)
    {
        auto subscriber_iterator = subscribers.begin();
        while (subscriber_iterator != subscribers.end())
        {
            if (auto shared_listener =
                    subscriber_iterator->second.lock())
            {
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
    std::unordered_map<SubscriptionId, std::weak_ptr<Listener<T>>> subscribers;
    SubscriptionId next_id{0};
};
