#include "GameState.h"
#include "GameObject.h"
#include "Command.h"
#include "SplashScreen.h"


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#define DELTATIME 1.f
SDL_Rect rect;

int dy = 100, dx = 100, speedx = 1,speedy = 1;
int directx, directy;

static void moveright(GameObj* obj, float dt) {


	rect.x += (int) (speedx * dt);

};
static void moveleft(GameObj* obj, float dt) {

	rect.x -= (int) (speedx * dt);

};
static void moveup(GameObj* obj, float dt) {

	rect.y -= (int) (speedy * dt);

};
static void movedown(GameObj* obj, float dt) {

	rect.y += (int) (speedy * dt);

};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//////////Implemention of the public Interface///////////////////////

CHANGESTATE(SplashonEnter) {
	printf("Enter State\n");
	rect.h = 50;
	rect.w = 100;

	rect.x = 50;
	rect.y = 100;

	obj->Collection[obj->CurrentStateIndex]->isActive = true;
}
CHANGESTATE(SplashonExit) {
	printf("Exit State\n");
	obj->isRunning = true;
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
}

TOPROCESS(SplashUpdate) {
	//Process All accepted Commands
	while (!obj->HolyCommands.empty())
	{
		Command* cmd = obj->HolyCommands.front();
		switch (cmd->Type)
		{
		case EXIT:
		{
			cmd->action(obj, 0.f);
			obj->HolyCommands.pop();

			//TODO(jojo): this way is unnecessary could just call directly the modules onExit function!!!
			obj->Collection[obj->CurrentStateIndex]->onExit(obj);

		}break;
		case MOVERIGHT:
		{
			cmd->action(obj, DELTATIME);
			obj->HolyCommands.pop();
		}break;
		case MOVELEFT:
		{
			cmd->action(obj, DELTATIME);
			obj->HolyCommands.pop();
		}break;
		case MOVEUP:
		{
			cmd->action(obj, DELTATIME);
			obj->HolyCommands.pop();
		}break;
		case MOVEDOWN:
		{
			cmd->action(obj, DELTATIME);
			obj->HolyCommands.pop();
		}break;
		}
	}
/*
	rect.x += (dx * delta) * speedx;
	rect.y += (dy * delta) * speedy;*/
	

}

TOPROCESS(SplashRender) {
	SDL_RenderClear(obj->Renderer);


	SDL_SetRenderDrawColor(obj->Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(obj->Renderer, &rect);
	SDL_SetRenderDrawColor(obj->Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	
	
	SDL_RenderPresent(obj->Renderer);
}

TOPROCESS(SplashInput) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			Command* cmd = createCommand(test, EXIT);
			obj->HolyCommands.push(cmd);
		}

		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE: {
				Command* cmd = createCommand(test, EXIT);
				obj->HolyCommands.push(cmd);

			}break;
			case SDLK_d: {
				directx = 1;


			}break;
			case SDLK_a: {
				Command* cmd = createCommand(moveleft, MOVELEFT);
				obj->HolyCommands.push(cmd);

			}break;
			case SDLK_w: {
				Command* cmd = createCommand(moveup, MOVEUP);
				obj->HolyCommands.push(cmd);

			}break;
			case SDLK_s: {
				Command* cmd = createCommand(movedown, MOVEDOWN);
				obj->HolyCommands.push(cmd);

			}break;



			}
			if (e.type == SDL_KEYUP)
			{
				switch (e.key.keysym.sym)
				{
					/*	case SDLK_ESCAPE: {
							Command* cmd = createCommand(test, EXIT);
							obj->HolyCommands.push(cmd);

						}break;*/
				case SDLK_d: {
					directx = 0;


				}break;
					/*	case SDLK_a: {
							Command* cmd = createCommand(moveleft, MOVELEFT);
							obj->HolyCommands.push(cmd);

						}break;
						case SDLK_w: {
							Command* cmd = createCommand(moveup, MOVEUP);
							obj->HolyCommands.push(cmd);

						}break;
						case SDLK_s: {
							Command* cmd = createCommand(movedown, MOVEDOWN);
							obj->HolyCommands.push(cmd);

						}break;
		*/


				}

				
			}

			if (directx == 1)
			{
				/*Command* cmd = createCommand(moveright, MOVERIGHT);
				obj->HolyCommands.push(cmd);*/
				rect.x += 1;
			}
		}
	}

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LEFT] && keystate[SDL_SCANCODE_UP]) {
		Command* cmd = createCommand(moveleft, MOVELEFT);
		obj->HolyCommands.push(cmd);

		cmd = createCommand(moveup, MOVEUP);
		obj->HolyCommands.push(cmd);
	}
	if (keystate[SDL_SCANCODE_LEFT] && keystate[SDL_SCANCODE_DOWN]) {
		Command* cmd = createCommand(moveleft, MOVELEFT);
		obj->HolyCommands.push(cmd);

	    cmd = createCommand(movedown, MOVEDOWN);
		obj->HolyCommands.push(cmd);
	}

	if (keystate[SDL_SCANCODE_RIGHT] && keystate[SDL_SCANCODE_UP]) {
		Command* cmd = createCommand(moveright, MOVERIGHT);
		obj->HolyCommands.push(cmd);

		cmd = createCommand(moveup, MOVEUP);
		obj->HolyCommands.push(cmd);
	}
	if (keystate[SDL_SCANCODE_RIGHT] && keystate[SDL_SCANCODE_DOWN]) {
		Command* cmd = createCommand(moveright, MOVERIGHT);
		obj->HolyCommands.push(cmd);

		cmd = createCommand(movedown, MOVEDOWN);
		obj->HolyCommands.push(cmd);
	}

	

	/* collide with edges of screen */
	if (rect.x < 0) {
		rect.x = 0;
		speedx = -speedx;
		dx += speedx;
	}
	else if (rect.x > 800 - rect.w) {
		rect.x = 800 - rect.w;
		speedx = -speedx;
	}
	if (rect.y < 0) {
		rect.y = 0;
		speedy = -speedy;
		dy += speedy;
	}
	else if (rect.y > 600 - rect.h) {
		rect.y = 600 - rect.h;
		speedy = -speedy;
	}
}



