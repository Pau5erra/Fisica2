#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

// TODO 1: Include Box 2 header and library
#include "Box2D\Box2D\Box2D.h"
#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled), world(NULL)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world b2World
	world = new b2World(b2Vec2(0, -10));
	
	b2Vec2 gravity(GRAVITY1, GRAVITY2);

	// - You need to send it a default gravity
	// - You need init the world in the constructor 
	// - Remember to destroy the world after using it


	// TODO 4: Create a a big static circle as "ground"
	//Creem un body i li posem tots els parametres
	int radius = 225;
	int x = 525;
	int y = 400;

	b2BodyDef bodydef;

	b2Body* body = world->CreateBody(&bodydef);

	bodydef.type = b2_staticBody;

	bodydef.position.Set(PixelToMeter(x), PixelToMeter(y));

	//creem la shape

	b2CircleShape shape;

	shape.m_radius = PixelToMeter(radius);

	//creem la fixture

	b2FixtureDef fixture;

	fixture.shape = &shape;

	body->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	world->Step(FRAME1/ FRAME2 , VELOCITY, ITERATIONS);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(MeterToPixel(pos.x), MeterToPixel(pos.y), MeterToPixel(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

float ModulePhysics::PixelToMeter(int numPixels){

	numMeters = numPixels / 100;

	return numMeters;
}

int ModulePhysics::MeterToPixel(float numMeters){

	numPixels = numMeters * 100;

	return numPixels;
}