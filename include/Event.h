

#ifndef EVENT_H
#define EVENT_H

class Game;

class Event {
public:
  virtual ~Event() = default;
  virtual void execute(Game& game) = 0;
};

#endif // !EVENT_H

