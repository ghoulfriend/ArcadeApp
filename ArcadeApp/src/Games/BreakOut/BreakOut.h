#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakoutGameLevel.h"
#include <vector>

enum BreakOutGameState
{
	IN_PLAY = 0,
	IN_SERVE,
	IN_GAME_OVER
};

class BreakOut : public Game  //We are going to make bottom up design for this game
{
public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
private:
	const int NUM_LIVES = 3;

	void ResetGame(size_t toLevel =0);

	BreakoutGameLevel& GetCurrentLevel() {return mLevels[mCurrentLevel];}
	void SetToServeState();


	bool IsBallPassedCutoffY() const;
	void ReduceLifeByOne();
	inline bool IsGameOver() const {return mLives < 0;}

	const float INITIAL_BALL_SPEED = 100;
	const Vec2D INITIAL_BALL_VEL = Vec2D(100,-100);
	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	std::vector<BreakoutGameLevel> mLevels;
	size_t mCurrentLevel;
	int mLives;
	float mYCutoff;

	BreakOutGameState mGameState;


};


#endif /* GAMES_BREAKOUT_H_ */
