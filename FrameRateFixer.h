#ifndef FRAMES_H
#define FRAMES_H

//The timer
class FrameRateFixer
{
private:
	unsigned FPS;
	unsigned frameDelay;
    unsigned startTicks;
	unsigned lastTick;
	
    unsigned get_ticks();
public:
    FrameRateFixer(unsigned fps = 30);
	~FrameRateFixer() = default;
	
	void start();
	void regulateFPS();
	void setFPS(unsigned);
	unsigned getFrameTime();
};

#endif