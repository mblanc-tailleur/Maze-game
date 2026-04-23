#pragma once
#include <vector>
#include "SpriteAnimation.h"

using namespace std;

class AnimatedSprite : public SpriteAnimation
{
	private:
		vector<SpriteAnimation> Animations;
		vector<const char*> sources;

	public:
		void DecodeJson();
};