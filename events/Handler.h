#ifndef HANDLER_H
#define HANDLER_H

#include <memory>

namespace events
{

class Handlable
{
public:
  virtual ~Handlable() = default;

  virtual void Handle() = 0;
};

template<typename T>
class Handler : public Handlable
{
protected:
  std::shared_ptr<T> event;

public:
  void SetEvent(std::shared_ptr<T> e)
  {
    event = e;
  }
};

}

#endif
