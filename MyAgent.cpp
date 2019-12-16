#include "MyAgent.h"
#include "MyGame.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include "mathtool/Box.h"

namespace GMUCS425
{

  void MyAgent::handle_event(SDL_Event & e)
  {
    if(this->movable)
    {
      //do nothing now...
    }
  }

  //update this agent's motion, looks, sound, etc
  void MyAgent::update()
  {
    //do nothing by default...
  }

  void MyAgent::display()
  {
    if(!this->visible) return; //not visible...
    //setup positions and ask sprite to draw something
    this->sprite->display(x, y, scale, degree);
  }

  //show HUD (heads-up display) or status bar
  void MyAgent::draw_HUD()
  {
    //draw nothing by defaut, your task to display the location of an agent
    //on the upper left corner
    //read http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php
  }

  bool MyAgent::collide(MyAgent * other)
  {
    mathtool::Box2d box1, box2;
    box1.x=x;
    box1.y=y;
    box1.width=this->sprite->getWidth(scale);
    box1.height=this->sprite->getHeight(scale);

    box2.x=other->x;
    box2.y=other->y;
    box2.width=other->sprite->getWidth(other->scale);
    box2.height=other->sprite->getHeight(other->scale);

    return box1.intersect(box2);
  }

  void MyAgent::draw_bounding_box()
  {
    float my_W=this->sprite->getWidth(scale);
    float my_H=this->sprite->getHeight(scale);

    SDL_Rect box; //create a rect
    box.x = x;  //controls the rect's x coordinate
    box.y = y; // controls the rect's y coordinte
    box.w = my_W; // controls the width of the rect
    box.h = my_H; // controls the height of the rect

    SDL_Renderer * renderer=getMyGame()->getRenderer();
    SDL_SetRenderDrawColor(renderer,255,100,0,100);
    //SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderDrawRect(renderer,&box);

    box.w/=10;
    box.h=box.w;
    SDL_SetRenderDrawColor(renderer,0,0,0,100);
    SDL_RenderFillRect(renderer,&box);
  }

}//end namespace
