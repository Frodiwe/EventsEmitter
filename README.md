# Events Emitter

Simple C++17 events emitter library

## Usage

There's `events/Demo.hpp` file showcasing the usage of this library.

Create event class holding event's data
```
struct TestEvent
{
  float data;

  TestEvent(float data)
    : data{data}
  { }
};
```

Create class derived from `Handler<EventT>`
```
class TestHandler : public Handler<TestEvent>
{
public:
  void Handle() override
  {
    std::cout << "Event data: " << event->data << std::endl;
  }
};
```

Subscribe to and publish events using instance of `Emitter` class
```
emitter.Subscribe<TestEvent>(std::make_shared<TestHandler>());

emitter.Publish<TestEvent>(6.66f);
```