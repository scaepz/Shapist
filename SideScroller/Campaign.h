#ifndef CAMPAIGN_H
#define CAMPAIGN_H
#include <string>
#include "Game.h"
using std::string;
class CCampaign
{
public:
	CCampaign(string campaignFilePath, SDL_Renderer *, SDL_Window *, int resolutionX, int resolutionY);
	virtual ~CCampaign();
	void LoadLevel(int lvlNumber); //returns true if next level can be loaded, false if player quit
	string GetRow(const string & file, int rownumber);

private:
	string campaignFile;
	SDL_Renderer * renderer;
	SDL_Window * window;
	int resolution[2];
};

#endif