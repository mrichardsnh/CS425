#pragma once

#include "MyAgent.h"
#include "MyBehaviorTree.h"

namespace GMUCS425
{
    class MyZombieAgent : public MyAgent
    {
      public:
		int shift = 5;
		bool ccw;
		int randDir = 0;
        MyZombieAgent(bool movable=true, bool collision=true)
        :MyAgent(movable,collision)
        {
          collide_with=NULL;
          behavior=NULL;
        }

        virtual void update();
        virtual void display();
        virtual void handle_event(SDL_Event & e);
		virtual void setShift(int x)
		{
			this->shift = x;
		}
		int getX()  { return this->x;  }
		int getY() { return this->y;  }
		int getShift() { return this->shift; }
		void rotate(float degree) { this->degree += degree; }
		void rotateTo(float degree) { this->degree = degree; }
		bool getCol() { return this->collision; }
		void tranlate(float x, float y) { this->x += x; this->y += y; }
		void tranlateTo(float x, float y) { this->x = x; this->y = y; }

		void scaleTo(float s) { this->scale = s; }
      protected:
		  
          //NEW
          void build_behavior_tree();

      private:

        MyAgent * collide_with;
        int collision_free_timer=10;
        MyBehaviorTree * behavior; //NEW, build this!
    };

}//end namespace
