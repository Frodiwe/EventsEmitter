#ifndef DEMO_H
#define DEMO_H

#include "Emitter.h"
#include "Handler.h"

namespace events
{

namespace demo
{

struct TestEvent
{
  float data;

  TestEvent(float data)
    : data{data}
  { }
};

class TestHandler : public Handler<TestEvent>
{
public:
  void Handle() override
  {
    std::cout << "Event data: " << event->data << std::endl;
  }
};

void run()
{
  auto emitter = Emitter{};

  emitter.Subscribe<TestEvent>(std::make_shared<TestHandler>());
  emitter.Publish<TestEvent>(6.66f);
};

}

}

#endif