#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <vector>

using namespace std;

unsigned const int mapsizex = 140; // horizontal size of the map
unsigned const int mapsizey = 140; // vertical size size of the map

vector<pair<float, float>> shortestpath;
pair < pair<float, float>, pair<float, float> >  directline;

float pathlength(vector<pair<float, float>> tpath)
{
	float length;
	for (int i = 1; i < tpath.size(); i++)
	{
		length += sqrt(pow(tpath[i].first - tpath[i - 1].first, 2) + pow(tpath[i].second - tpath[i - 1].second, 2));
	}
	return length;
}

float distancefromcenter(pair<float, float> tpoint)
{
	return abs((directline.second.second - directline.first.second)*tpoint.first - (directline.second.first - directline.first.first)*tpoint.second + directline.second.first*directline.first.second - directline.second.second*directline.first.first) / (sqrt(pow(directline.second.first - directline.first.first, 2) + pow(directline.second.second - directline.first.first, 2)));
}