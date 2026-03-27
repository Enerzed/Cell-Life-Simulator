#pragma once
#include "Random.h"
//0 - turnRight
//1 - turnLeft
//2 - eat
//3 - kill
//4 - hold
//5 - go

class Gen
{
public:
	int none;
	int sameCell;
	int otherCell;
	int food;
	int wall;
	int meat;
	Random random;

	Gen()
	{
		int reaction;

		do reaction = random.generate(0, 5);
		while (reaction == 2 || reaction == 3);
		none = reaction;

		do reaction = random.generate(0, 5);
		while (reaction == 2 || reaction == 5);
		sameCell = reaction;

		do reaction = random.generate(0, 5);
		while (reaction == 2 || reaction == 5);
		otherCell = reaction;

		do reaction = random.generate(0, 5);
		while (reaction == 3 || reaction == 5);
		food = reaction;

		do reaction = random.generate(0, 5);
		while (reaction == 3 || reaction == 5);
		meat = reaction;

		do reaction = random.generate(0, 5);
		while (reaction == 2 || reaction == 3 || reaction == 5);
		wall = reaction;
	}

	void mutate()
	{
		if (random.generate(0, 19) == 0)
		{
			int reaction;
			for (int i = 0; i < random.generate(1, 6); i++)
			{
				switch (random.generate(0, 5))
				{
				case 0: {
					do reaction = random.generate(0, 5);
					while (reaction == 2 || reaction == 3);
					none = reaction;
					break;
				}
				case 1: {
					do reaction = random.generate(0, 5);
					while (reaction == 2 || reaction == 5);
					sameCell = reaction;
					break;
				}
				case 2: {
					do reaction = random.generate(0, 5);
					while (reaction == 2 || reaction == 5);
					otherCell = reaction;
					break;
				}
				case 3: {
					do reaction = random.generate(0, 5);
					while (reaction == 3 || reaction == 5);
					food = reaction;
					break;
				}
				case 4: {
					do reaction = random.generate(0, 5);
					while (reaction == 2 || reaction == 3 || reaction == 5);
					wall = reaction;
					break;
				}
				case 5: {
					do reaction = random.generate(0, 5);
					while (reaction == 3 || reaction == 5);
					meat = reaction;
					break;
				}
				}
			}
		}
	}

	Gen(const Gen& other)
	{
		none = other.none;
		sameCell = other.sameCell;
		otherCell = other.otherCell;
		food = other.food;
		wall = other.wall;;
		meat = other.meat;
	}

	Gen& operator=(const Gen& other)
	{
		if (this != &other)
		{
			none = other.none;
			sameCell = other.sameCell;
			otherCell = other.otherCell;
			food = other.food;
			wall = other.wall;
			meat = other.meat;
		}
		return *this;
	}

	std::string getStringReactionNone()
	{
		std::string returnReaction;
		switch (none)
		{
		case 0: returnReaction = "Turn Right "; break;
		case 1: returnReaction = "Turn Left  "; break;
		case 2: returnReaction = "Eat        "; break;
		case 3: returnReaction = "Kill       "; break;
		case 4: returnReaction = "Hold       "; break;
		case 5: returnReaction = "Move       "; break;
		}
		return returnReaction;
	}

	std::string getStringReactionSameCell()
	{
		std::string returnReaction;
		switch (sameCell)
		{
		case 0: returnReaction = "Turn Right "; break;
		case 1: returnReaction = "Turn Left  "; break;
		case 2: returnReaction = "Eat        "; break;
		case 3: returnReaction = "Kill       "; break;
		case 4: returnReaction = "Hold       "; break;
		case 5: returnReaction = "Move       "; break;
		}
		return returnReaction;
	}

	std::string getStringReactionOtherCell()
	{
		std::string returnReaction;
		switch (otherCell)
		{
		case 0: returnReaction = "Turn Right "; break;
		case 1: returnReaction = "Turn Left  "; break;
		case 2: returnReaction = "Eat        "; break;
		case 3: returnReaction = "Kill       "; break;
		case 4: returnReaction = "Hold       "; break;
		case 5: returnReaction = "Move       "; break;
		}
		return returnReaction;
	}

	std::string getStringReactionFood()
	{
		std::string returnReaction;
		switch (food)
		{
		case 0: returnReaction = "Turn Right "; break;
		case 1: returnReaction = "Turn Left  "; break;
		case 2: returnReaction = "Eat        "; break;
		case 3: returnReaction = "Kill       "; break;
		case 4: returnReaction = "Hold       "; break;
		case 5: returnReaction = "Move       "; break;
		}
		return returnReaction;
	}

	std::string getStringReactionWall()
	{
		std::string returnReaction;
		switch (wall)
		{
		case 0: returnReaction = "Turn Right "; break;
		case 1: returnReaction = "Turn Left  "; break;
		case 2: returnReaction = "Eat        "; break;
		case 3: returnReaction = "Kill       "; break;
		case 4: returnReaction = "Hold       "; break;
		case 5: returnReaction = "Move       "; break;
		}
		return returnReaction;
	}

	std::string getStringReactionMeat()
	{
		std::string returnReaction;
		switch (meat)
		{
		case 0: returnReaction = "Turn Right "; break;
		case 1: returnReaction = "Turn Left  "; break;
		case 2: returnReaction = "Eat        "; break;
		case 3: returnReaction = "Kill       "; break;
		case 4: returnReaction = "Hold       "; break;
		case 5: returnReaction = "Move       "; break;
		}
		return returnReaction;
	}

	bool operator == (const Gen& g)
	{
		if (none == g.none && sameCell == g.sameCell && otherCell == g.otherCell && food == g.food && wall == g.wall && meat == g.meat)
			return true;
		return false;
	}
};

