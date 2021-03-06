#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <vector>

using namespace std;

typedef vector <pair<float, float>> path;
typedef pair <pair<float, float>, pair<float, float>> line;
typedef pair <float, float> point;
typedef vector<point>::iterator vectoriter;
typedef vector<vector<point>::iterator> vectoritervector;

unsigned const int mapsizex = 140; // horizontal size of the map
unsigned const int mapsizey = 140; // vertical size size of the map
vectoritervector mapiter;

float resolution = 0.1;
path blank;

path shortestpath;
float lengthofshortestpath = 10000;
line directline;
vector<line> obsticals;

bool mapiteradvance()
{
	for (int w = 0; w <mapiter.size(); w++)
	{
		if ((*mapiter[w]).first == mapsizex || (*mapiter[w]).second == mapsizey)
		{
			if (w == mapiter.size() - 1){ return false; }
			path tmp;
			for (float tx = 0; tx <= mapsizex; tx += 0.1)
			{
				for (float ty = 0; ty <= mapsizey; ty += 0.1)
				{
					tmp.push_back(make_pair(tx, ty));
				}
			}
			mapiter[w] = tmp.begin();
			return true;
		}
		else
		{
			++mapiter[w];
			return true;
		}
	}
	return false;
}
//(std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it) *it
void populatemapiter(int number)
{
	path tmp;
	for (int q = 0; q < number; q++)
	{
		for (float tx = 0; tx <= mapsizex; tx += 0.1)
		{
			for (float ty = 0; ty <= mapsizey; ty += 0.1)
			{
				tmp.push_back(make_pair(tx, ty));
			}
		}
		mapiter.push_back(tmp.begin());
	}
	return;
}

void populateobsticals()
{
	obsticals.push_back(make_pair(make_pair(0,5),make_pair(10,5)));
}

bool onSegment(point p, point q, point r)
{
	if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) && q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second)){return true;}
	return false;
}

int orientation(point p, point q, point r)
{
	int val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

bool doIntersect(line a, line b)
{
	int o1 = orientation(a.first, a.second, b.first);
	int o2 = orientation(a.first, a.second, b.second);
	int o3 = orientation(b.first, b.second, a.first);
	int o4 = orientation(b.first, b.second, a.second);

	if (o1 != o2 && o3 != o4){ return true; }

	if (o1 == 0 && onSegment(a.first, b.first, a.second)) return true;
	if (o2 == 0 && onSegment(a.first, b.second, a.second)) return true;
	if (o3 == 0 && onSegment(b.first, a.first, b.second)) return true;
	if (o4 == 0 && onSegment(b.first, a.second, b.second)) return true;
	return false;
}

bool obsticalcheck(path tpath)
{
	line currentmove;
	for (int i = 1; i < tpath.size(); i++)
	{
		currentmove.first = tpath[i - 1];
		currentmove.second = tpath[i];

		for (int j = 0; j < obsticals.size(); j++)
		{
			if (doIntersect(currentmove, obsticals[i])){return false;}
		}
	}
	return true;
}

float pathlength(path tpath)
{
	float length = 0;
	for (int i = 1; i < tpath.size(); i++)
	{
		length += sqrt(pow(tpath[i].first - tpath[i - 1].first, 2) + pow(tpath[i].second - tpath[i - 1].second, 2));
	}
	return length;
}

float distancefromcenterline(point tpoint)
{
	return abs((directline.second.second - directline.first.second)*tpoint.first - (directline.second.first - directline.first.first)*tpoint.second + directline.second.first*directline.first.second - directline.second.second*directline.first.first) / (sqrt(pow(directline.second.first - directline.first.first, 2) + pow(directline.second.second - directline.first.first, 2)));
}

path findshortestpath(int maxjumps, point start, point end, bool endwhenfind = false)
{
	directline.first.first = start.first;
	directline.first.second = start.second;
	directline.second.first = end.first;
	directline.second.second = end.second;

	path directpath;
	path checkpath = blank;
	float checkpathlength;
	directpath.push_back(start);
	directpath.push_back(end);

	if (!obsticalcheck(directpath)){return directpath;}

	for (int j = 1; j <= maxjumps; j++)
	{
		populatemapiter(j);
		while (mapiteradvance())
		{
			checkpath.clear();
			checkpath.push_back(start);
			for (int p = 0; p < mapiter.size(); p++)
			{
				checkpath.push_back(*mapiter[p]);
			}
			checkpath.push_back(end);
			checkpathlength = pathlength(checkpath);
			if (obsticalcheck(checkpath) && checkpathlength < lengthofshortestpath){ shortestpath = checkpath; lengthofshortestpath = checkpathlength; }
		}
	}
	
	return checkpath;

}

void main()
{
	point startpoint = make_pair(0,0);
	point endpoint = make_pair(0,10);
	path mypath = findshortestpath(100, startpoint, endpoint);
	//populateobsticals();
	for (int k = 0; k < mypath.size(); k++)
	{
		cout << "(" << mypath[k].first << "," << mypath[k].second << ")" << endl;
	}
	cout << "Done" << endl;
	cin.ignore();
}