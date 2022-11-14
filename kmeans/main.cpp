#include<GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "kmeans.h"

using namespace std;

vector<vector<Point>> res;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	glBegin(GL_POINTS);
	
	for(int i = 0; i < res.size();i++){
		float randomR = (double)rand() / (RAND_MAX);
		float randomG = (double)rand() / (RAND_MAX);
		float randomB = (double)rand() / (RAND_MAX);
		glColor3f(randomR, randomG, randomB);
		for(int j = 0; j < res[i].size();j++){
			glVertex2f(res[i][j].x, res[i][j].y);
		}
	}
	glEnd();
	glFlush();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0,100.0);
}

int main(int argc, char** argv) {
	
	int n;
	int k;
	cout<<"Ingrese el numero de púntos: ";
	cin>>n;
	cout<<endl;
	cout<<"Ingrese el numero de clusters: ";
	cin>>k;

	vector<Point> points(n);
	for(int i = 0 ; i < n; i++){
		points[i].x = rand()%100;
		points[i].y = rand()%100;	
	}
	
	//k-means clustering
	vector<Cluster>clusters(k);
	kmeans(points, clusters, k, 10,res);
	

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Points");
	glutDisplayFunc(display);
	
	myinit();
	glutMainLoop();
	
	return 0;
}
