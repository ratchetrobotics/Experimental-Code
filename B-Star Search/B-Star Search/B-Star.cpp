#include <iostream>
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

