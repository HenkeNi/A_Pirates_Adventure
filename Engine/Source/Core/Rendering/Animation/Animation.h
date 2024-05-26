#pragma once

struct Frame
{
	unsigned Row;
	unsigned Col;
	float Duration;
};

class Animation
{
public:


	void OnAnimationFinished();

private:
	std::vector<Frame> m_frames;
	bool m_isLooping;
};

