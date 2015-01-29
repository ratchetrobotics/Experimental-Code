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

vector<pair<float, float>> path;
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