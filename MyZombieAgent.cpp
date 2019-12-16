#include "MyZombieAgent.h"
#include "MyGame.h"
#include <typeinfo>
namespace GMUCS425
{
  //The base class of all zombie behavior nodes
  //again, this is an abstract class because "run" is not implemented
  class MyZombieTaskNode : public MyTaskNode
  {
  public:
    MyZombieTaskNode(MyZombieAgent * agent){ zombie=agent; }
  protected:
    MyZombieAgent * zombie;
  };

  //TODO: Define more tasks here
  class MyZombieTask01 : public MyZombieTaskNode
  {
  public:
	MyZombieAgent *agent;
    MyZombieTask01(MyZombieAgent * agent):MyZombieTaskNode(agent) //Basic patrol movement
    {
		this->agent = agent;
    }
    bool run(){
      //TODO: implement this
		if (agent->getX() + 5 > (agent->startX + 100))
		{
			agent->setShift(-2);
		}
		else if (agent->getX() <= agent->startX)
		{
			agent->setShift(2);
		}
		agent->tranlate(agent->getShift(), 0);
		return true;
    }
  private:
  };

  //TODO: Define more tasks here
  class MyZombieTask02 : public MyZombieTaskNode
  {
  public:
	  MyZombieAgent * agent;
    MyZombieTask02(MyZombieAgent * agent):MyZombieTaskNode(agent)//move back to basic patrol area
    {
		this->agent = agent;
    }
    bool run(){
      //TODO: implement this
		if (agent->getX() < agent->startX)
		{
			agent->tranlate(5, 0);
			return true;
		}
		else if (agent->getX() > agent->startX + 100)
		{
			agent->tranlate(-5, 0);
			return true;
		}
		return false;
    }
  private:
  };
  class MyZombieTask03 : public MyZombieTaskNode
  {
  public:
	  MyZombieAgent * agent;
	  MyZombieTask03(MyZombieAgent * agent) :MyZombieTaskNode(agent)//dragon in sight line check and move
	  {
		  this->agent = agent;
	  }
	  bool run() {
		  //TODO: implement this
		  std::list<MyAgent * > mAgent = getMyGame()->getSceneManager()->get_active_scene()->get_agents();
		  MyAgent *dragon = NULL;
		  for (MyAgent * a : mAgent)
		  {
			  std::string as = typeid(*a).name();
			  if (as.compare("class GMUCS425::MyDragonAgent") == 0)
			  {
				  dragon = a;
			  }
		  }
		  bool blocked = false;
		  if (agent->getX() > dragon->getX())
		  {
			  if (dragon->getY() >= agent->getY() && dragon->getY() <= (agent->getY() + 35))
			  {
				  if (agent->getX() < 480 && !agent->getCol())
				  {
					  for (MyAgent * a : mAgent)
					  {
						  std::string as = typeid(*a).name();
						  if (((a != dragon) && (a->getY() >= agent->getY() && a->getY() + 30 <= agent->getY() + 35)))
						  {
							  if (a->getX() > dragon->getX() && a->getX() < agent->getX())
							  {
								  blocked = true;
							  }
						  }
					  }
					  if (!blocked && agent->getX() < 480)
					  {
//						  agent->setShift(5);
//						  agent->tranlate(agent->getShift(), 0);
						  return true;
					  }
				  }
			  }
		  }
		  else if (agent->getX() < dragon->getX())
		  {
			  if (dragon->getY() >= agent->getY() && dragon->getY() <= (agent->getY() + 35))
			  {
				  for (MyAgent * a : mAgent)
				  {
					  std::string as = typeid(*a).name();
					  if ((a != dragon) && (a->getY() >= agent->getY() && a->getY() + 30 <= agent->getY() + 35))
					  {
						  if (a->getX() < dragon->getX() && a->getX() > agent->getX())
						  {
							  blocked = true;
						  }
					  }
				  }
				  if (!blocked && agent->getX() > 0)
				  {
//					  agent->setShift(-5);
//					  agent->tranlate(agent->getShift(), 0);
					  return true;
				  }
			  }
		  }
		  return false;
	  }
  private:
  };
  class MyZombieTask04 : public MyZombieTaskNode
  {
  public:
	  MyZombieAgent *agent;
	  MyZombieTask04(MyZombieAgent * agent) :MyZombieTaskNode(agent) //moving away from dragon
	  {
		  this->agent = agent;
	  }
	  bool run() {
		  //TODO: implement this
		  std::list<MyAgent * > mAgent = getMyGame()->getSceneManager()->get_active_scene()->get_agents();
		  MyAgent *dragon = NULL;
		  for (MyAgent * a : mAgent)
		  {
			  std::string as = typeid(*a).name();
			  if (as.compare("class GMUCS425::MyDragonAgent") == 0)
			  {
				  dragon = a;
			  }
		  }
		  if (agent->getX() > dragon->getX())
		  {
			  agent->setShift(-3);
			  agent->tranlate(agent->getShift(), 0);
			  return true;
		  }
		  else if (agent->getX() < dragon->getX())
		  {
			  agent->setShift(3);
			  agent->tranlate(agent->getShift(), 0);
			  return true;
		  }
		  return false;
	  }
  private:
  };

  //TODO: make sure that you define more tasks here, ex: MyZombieTask03~MyZombieTask99

  //TODO: build your behavior tree here
  void MyZombieAgent::build_behavior_tree()
  {
    MyTaskNode * root=NULL;

    //TODO:
    //Create a root
    //Create more nodes using MyZombieTask1~MyZombieTask100
    //use add_kid to build the rest of the tree!
	randDir = rand() % 2;
	if (randDir == 1)
	{
		tranlateTo(startX + 100, startY);
	}
    //EXAMPLE: REMOVE THIS BLOCK
    MySelectorNode * selector=new MySelectorNode();
    MyZombieTask01 * patrol=new MyZombieTask01(this);
	MySequenceNode * seq = new MySequenceNode();
    MyZombieTask02 * back_to_patrol=new MyZombieTask02(this);
	MyZombieTask03 * dragon_check = new MyZombieTask03(this);
	MyZombieTask04 * move_zomb_away = new MyZombieTask04(this);
	seq->add_kid(dragon_check);
	seq->add_kid(move_zomb_away);
	selector->add_kid(seq);
	selector->add_kid(back_to_patrol);
	selector->add_kid(patrol);
    //EXAMPLE: REMOVE THIS BLOCK
	root = selector;
    //build the tree using the root
    this->behavior=new MyBehaviorTree(root);
  }

  void MyZombieAgent::display()
  {
    if(!this->visible) return; //not visible...
    //setup positions and ask sprite to draw something
    this->sprite->display(x, y, scale, degree);

   //draw_bounding_box();
  }

  void MyZombieAgent::update()
  {
    if(this->behavior==NULL)
    {
        this->build_behavior_tree();
        assert(this->behavior);
    }
	if (this != NULL)
	{
		this->behavior->run();
	}
    if(!this->collision)
    {
      if(collision_free_timer>=0) collision_free_timer--;
      else collide_with=NULL; //no collision
    }

    this->collision=false;
  }

  void MyZombieAgent::handle_event(SDL_Event & e)
  {

    if(this->collision && collide_with!=NULL)
    {
      return;
    }

    if(e.type==SDL_USEREVENT)
    {
      if(e.user.code == 1)
      {
        if(e.user.data1==this || e.user.data2==this)
        {
          MyAgent * other = (MyAgent *)((e.user.data1!=this)?e.user.data1:e.user.data2);

          if(other!=collide_with)
          {
            collide_with=other;
			this->setShift(this->getShift() * -1);
          }
          this->collision_free_timer=1;
          this->collision=true;
        }
      }
    }
  }

}//end namespace
