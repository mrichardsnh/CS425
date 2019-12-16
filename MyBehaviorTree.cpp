#include "MyBehaviorTree.h"


bool MySelectorNode::run()
{
  //TODO: implement this
	for(auto kid : children)
	{
		if(kid->run())
		{
			return true;
		}
	}
  return false;
}

bool MySequenceNode::run()
{
  //TODO: implement this
	for (auto kid : children)
	{
		if (!kid->run())
		{
			return false;
		}
	}
	return true;
}
