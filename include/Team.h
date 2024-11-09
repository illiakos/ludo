

#ifndef TEAM_H 
#define TEAM_H

#include "Color.h"
#include <string>
#include <vector>
class Team {

public:
  Team(Color& color, int id) : color(color), id(id) {}

  Color color;
  int id;
private:
  std::vector<std::string> players;
};

#endif // !
