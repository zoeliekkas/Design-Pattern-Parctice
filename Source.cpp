#include <iostream>
#include <functional>
#include "Header.h"
#include <vector>



class Wall {};
class Floor {};

class EnchantedWall : public Wall
{

};

class EnchantedFloor : public Floor {

};

class Maze
{
public:
	std::vector<Wall> m_walls;
	Floor m_floor;
};



class MazeBuilder
{
public:
	virtual void buildMaze() = 0;
	virtual void buildfloor() = 0;
	virtual void buildwall() = 0;
			
	virtual Maze* getMaze() = 0;

};

class StanderdMazeBuilder : public MazeBuilder
{
public:
	virtual void buildMaze() override {
		_maze = new Maze();
	}
	virtual void buildfloor() override {
		_maze->m_floor = Floor();
	}
	virtual void buildwall() override {
		_maze->m_walls.push_back(Wall());
	}

	virtual Maze* getMaze() override { return nullptr; }
private:
	Maze* _maze;
};

//Abstract Factory
class MazeFactory
{
public:
	virtual Maze* makeMaze() = 0;
	virtual Wall* makeWall() = 0;
	virtual Floor* makeFloor() = 0;

};

class EnchantedMazeFactory : public MazeFactory
{
public:
	EnchantedMazeFactory() {};
	virtual Maze* makeMaze() override
	{
		return new Maze();
	}

	virtual Floor* makeFloor() override {
		return new EnchantedFloor();
	}

	virtual Wall* makeWall() override {
		return new EnchantedWall();
	}
};

//===========================================Client Code=========================================//

class MazeGame
{
public:

	//use builder pattern
	Maze* createMaze(MazeBuilder& builder)
	{
		builder.buildMaze();
		builder.buildfloor();
		builder.buildwall();

		return builder.getMaze();
	}

	//use Abstract Factory patterm
	Maze* createMaze(MazeFactory& factory)
	{
		Maze* maze = factory.makeMaze();
		Floor* floor = factory.makeFloor();
		Wall* wall = factory.makeWall();


		return maze;
	}


	Maze* m_maze;
};


int main()
{
	//builder pattern
	Maze* maze;
	MazeGame game;
	StanderdMazeBuilder std_builder;
	
	game.m_maze = game.createMaze(std_builder);


	//abstract factory
	MazeGame game_with_midder_difficulty;
	MazeFactory* factory = new EnchantedMazeFactory();
	game_with_midder_difficulty.m_maze = game_with_midder_difficulty.createMaze(*factory);


	return 0;
}