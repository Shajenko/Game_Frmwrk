#ifndef PLAYER_H
#define PLAYER_H

enum Direction { UP, RIGHT, DOWN, LEFT};

class Player
{
	public:
		Player();
		virtual ~Player();
		void changeDirection(Direction);
	protected:
	private:
		Direction direction;

};

#endif // PLAYER_H
