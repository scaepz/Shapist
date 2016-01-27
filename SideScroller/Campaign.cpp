#include "Campaign.h"
#include <fstream>

CCampaign::CCampaign(string campaignFilePath, SDL_Renderer *r, SDL_Window *w, int resX, int resY)
{
	std::fstream reader(campaignFilePath);
	while (!reader.eof())
	{
		char temp;
		reader.read(&temp, 1);
		campaignFile += temp;
	}
	renderer = r; 
	window = w;
	resolution[0] = resX;
	resolution[1] = resY;
}


CCampaign::~CCampaign()
{
}

void CCampaign::LoadLevel(int lvlNumber)
{
	bool nextLevel = false;
	CGame game(GetRow(campaignFile, lvlNumber), &nextLevel, renderer, window, resolution[0], resolution[1], "devsave", lvlNumber);
	if (nextLevel)
	{
		LoadLevel(lvlNumber + 1);
	}
}

string CCampaign::GetRow(const string & file, int rownumber)
{
	int rowCounter = 0;
	for (int i = 0; i < file.size(); i++)
	{
		if (rowCounter == rownumber)
		{
			int counter = 0;
			int tally = 0;
			string row;
			while (true)
			{
				if (i + counter < file.size())
				{
					if (file.at(i + counter) != '\n')
					{
						counter++;
					}
					else
					{
						row = file.substr(i, counter);
						return row;
					}
				}
				else return "eof";
			}
		}
		if (file.at(i) == '\n')
		{
			rowCounter++;
		}
	}
	return "eof";
}