

#ifndef TEAM_H 
#define TEAM_H

#include "Color.h"
class Team {

public:
  Team(Color& color) : color(color) {}

  Color color;
  int id;

};

#endif // !
