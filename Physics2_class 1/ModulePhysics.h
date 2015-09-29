#pragma once
#include "Module.h"
#include "Globals.h"

#define GRAVITY1  0.0f
#define GRAVITY2  -10
#define FRAME1  1.0f
#define FRAME2  60.0f
#define VELOCITY  8
#define ITERATIONS  3
class b2World;


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	float PixelToMeter(int numPixels);
	int MeterToPixel(float numMeters);

private:

	int numPixels;
	float numMeters;

	b2World* world;
	bool debug;
};