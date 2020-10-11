#ifndef GAMES_BREAKOUT_BALL_H_
#define GAMES_BREAKOUT_BALL_H_

#include "AARectangle.h"

class Screen;
struct BoundaryEdge;

class Ball
{
public:
	Ball();
	Ball(const Vec2D& pos, float radius);

	void Update(uint32_t dt);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge); /// say we bounce off something, we want the point of the edge when we bounce off
	inline void Stop() {mVelocity = Vec2D::ZERO;}
	void MoveTo(const Vec2D& point);
	void Bounce(const BoundaryEdge & edge);

	inline const AARectangle GetBoundingRect() const {return mBBox;}
	inline void SetVelocity(const Vec2D& vel) {mVelocity = vel;}
	inline Vec2D GetVelocity() const {return mVelocity;}
	inline float GetRadius() const {return mBBox.GetWidth() / 2.0f;}
	inline Vec2D GetPosition() const { return mBBox.GetCenterPoint(); } // get c e n t e r p o i n t


private:
	AARectangle mBBox; ///b o u n d i n g b o x
	Vec2D mVelocity;

	static const float RADIUS;
};

#endif /* GAMES_BREAKOUT_BALL_H_ */
