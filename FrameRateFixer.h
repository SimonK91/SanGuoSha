
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
    FrameRateFixer();
	~FrameRateFixer() = default;
	
	void start();
	void regulateFPS();
	void setFPS(unsigned);
	unsigned getFrameTime();
};
