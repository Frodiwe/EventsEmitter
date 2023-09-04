#ifndef EMITTER_H
#define EMITTER_H

#include <functional>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <typeindex>
#include <memory>

#include "Handler.h"

namespace events
{

using ListenerId = int32_t;

class Emitter
{
  using Listeners = std::vector<
    std::pair<
      ListenerId,
      std::shared_ptr<Handlable>
    >
  >;
  
  using ListenersMap = std::map<std::type_index, Listeners>;
  
private:
  ListenersMap listeners = {};
  
  ListenerId GenEventId(const Listeners& listeners)
  {
    return listeners.empty() ? 0 : listeners.back().first + 1;
  };
  
  template<typename EventT>
  ListenerId AddListener(ListenerId id, std::shared_ptr<Handlable> listener)
  {
    listeners.at(typeid(EventT)).emplace_back(id, listener);
    
    return id;
  }
  
public:
  template<typename EventT>
  ListenerId Subscribe(std::shared_ptr<Handlable> listener)
  {
    if (listeners.count(typeid(EventT)) == 0) {
      listeners[typeid(EventT)] = {};
    }
    
    return AddListener<EventT>(GenEventId(listeners.at(typeid(EventT))), listener);
  }
  
  template<typename EventT>
  void Unsubscribe(ListenerId listener_id)
  {
    if (listeners.count(typeid(EventT)) == 0) {
      return;
    }
    
    auto& event_listeners = listeners.at(typeid(EventT));
    
    event_listeners.erase(
      std::remove_if(
        event_listeners.begin(),
        event_listeners.end(),
        [&listener_id](const auto& l) { return l.first == listener_id; }
      ),
      event_listeners.end()
    );
  }
  
  template<typename EventT, typename... Args>
  void Publish(Args&&... args)
  { 
    if (listeners.count(typeid(EventT)) == 0)
    {
      return;
    }

    auto event = std::make_shared<EventT>(std::forward<Args>(args)...);

    for (const auto& listener : listeners.at(typeid(EventT)))
    {
      std::static_pointer_cast<Handler<EventT>>(listener.second)->SetEvent(event);
      listener.second->Handle();
    }
  }
};

}

#endif
