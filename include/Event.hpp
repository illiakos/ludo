#ifndef EVENT_H
#define EVENT_H

#include <string>
class Event {
public:
  /*virtual void execute() = 0;*/
  virtual ~Event() = default;
  virtual std::string getType() const = 0;
  explicit Event(bool blocking = true): isBlocking(blocking) {}

  bool isBlocking;
  virtual bool isCompleted() const {return true;}
};

#endif // !EVENT_H
