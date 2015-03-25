#include<stdio.h>
#include<SDL2/SDL.h>

enum arrowkey
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_NONE
};

#define TOTAL_KEYS 5

int load_img_surfs(SDL_Surface* surfs[TOTAL_KEYS],char paths[TOTAL_KEYS][20])
/*loads images into surfs and returns the number of images that failed to load*/
{
	int i,ret=0;
	for(i=0;i<TOTAL_KEYS;++i)
	{
		surfs[i]=SDL_LoadBMP(paths[i]);
		if(surfs[i]==NULL)
		{
			ret++;
			fprintf(stderr,"%s\n",SDL_GetError());
		}
	}
	return ret;
}

int main()
{
	SDL_Window* window=NULL;
	SDL_Surface* win_surf=NULL;
	SDL_Event e;
	enum arrowkey pressed_key=KEY_NONE;
	char img_paths[TOTAL_KEYS][20]={
		"images/up.bmp",
		"images/down.bmp",
		"images/left.bmp",
		"images/right.bmp",
		"images/none.bmp"};
	SDL_Surface* img_surfs[TOTAL_KEYS]={NULL,NULL,NULL,NULL,NULL};
	SDL_Keycode my_keycodes[TOTAL_KEYS-1]={SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT};
	char quit='n';
	int i=0;
	
	fprintf(stdout,"%s\n","Welcome to arrow key press detector");
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		fprintf(stderr,"%s\n",SDL_GetError());
		return -1;
	}
	
	window=SDL_CreateWindow("Title",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,256,256,SDL_WINDOW_SHOWN);
	if(window==NULL)
		fprintf(stderr,"%s\n",SDL_GetError());
	else if(load_img_surfs(img_surfs,img_paths)==0)
	{
		win_surf = SDL_GetWindowSurface(window);
		SDL_BlitSurface(img_surfs[KEY_NONE],NULL,win_surf,NULL);
		SDL_UpdateWindowSurface(window);
		while(quit!='y')
			while(SDL_PollEvent(&e)!=0)
			{
				if(e.type==SDL_QUIT)
					quit='y';
				else if(e.type==SDL_KEYDOWN)
				{
					pressed_key=KEY_NONE;
					for(i=0;i<TOTAL_KEYS-1;++i)
						if(e.key.keysym.sym==my_keycodes[i])
						{pressed_key=i;break;}
					if(pressed_key!=KEY_NONE)
					{
						printf("Blitting %s\n",img_paths[pressed_key]);
						SDL_BlitSurface(img_surfs[pressed_key],NULL,win_surf,NULL);
						SDL_UpdateWindowSurface(window);
					}
				}
			}
	}

	for(i=0;i<TOTAL_KEYS;++i)
		SDL_FreeSurface(img_surfs[i]);
	SDL_DestroyWindow(window);	
	SDL_Quit();
	return 0;
}
