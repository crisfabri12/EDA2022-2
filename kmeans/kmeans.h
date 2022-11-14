#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<iostream>
using namespace std;

//K. MEANS CLUSTERING ALGORITHM

struct Point
{
	int x;
	int y;
	int cluster;
};

struct Cluster
{
	int x;
	int y;
	int size;
};

void kmeans(vector<Point>& points, vector<Cluster>& clusters, int k,int iterations,vector<vector<Point>> &res)
{
	vector<vector<Point>> aux(k);
	//initialize clusters
	for (int i = 0; i < k; i++)
	{
		clusters[i].x = points[i].x;
		clusters[i].y = points[i].y;
		clusters[i].size = 1;
	}
	for (int i = 0; i < iterations; i++)
	{
		//assign points to clusters
		for (int j = 0; j < points.size(); j++)
		{
			int min = 999999;
			int cluster = 0;
			for (int l = 0; l < k; l++)
			{
				int distance = (points[j].x - clusters[l].x) * (points[j].x - clusters[l].x) + (points[j].y - clusters[l].y) * (points[j].y - clusters[l].y);
				if (distance < min)
				{
					min = distance;
					cluster = l;
				}
			}
			points[j].cluster = cluster;
		}
		
		//recalculate clusters
		for (int j = 0; j < k; j++)
		{
			clusters[j].x = 0;
			clusters[j].y = 0;
			clusters[j].size = 0;
			aux[j].clear();
		}
		for (int j = 0; j < points.size(); j++)
		{
			clusters[points[j].cluster].x += points[j].x;
			clusters[points[j].cluster].y += points[j].y;
			clusters[points[j].cluster].size++;
			aux[points[j].cluster].push_back(points[j]);
		}
		for (int j = 0; j < k; j++)
		{
			clusters[j].x /= clusters[j].size;
			clusters[j].y /= clusters[j].size;
		}
	}
	res = aux;
}
