#pragma once

#include "MyAgent.h"

namespace GMUCS425
{
    class MyChickenAgent : public MyAgent
    {
      public:
        MyChickenAgent(bool movable=true, bool collision=true):MyAgent(movable,collision)
        {radius=FLT_MAX; center_x=center_y=INT_MAX; ccw=false; collide_with=NULL;}
        virtual void update();
        virtual void display();
        virtual void handle_event(SDL_Event & e);
      private:
        float radius;
        int center_x, center_y;
        bool ccw;
        MyAgent * collide_with;
        
    };

}//end namespace
