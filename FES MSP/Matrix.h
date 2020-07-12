#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "Node.h"
#include "config.h"
#include "AD2_FESMSP.h"

class Matrix {
private:
	// Node matrix that interfaces with each physical electrode
	Node electrodeMatrix[ev::matrix::cols][ev::matrix::rows];

	// Node to stimulate
	Node targetNode;

	// array that holds the initial flex probability values
	// 4 columns, 5 positive rows, 2 negative electrode that can pair with each one positive electrode
	double initialFlexProbability[4][7][2] = { 0 };


public:
	AD2_FESMSP ad2;

	Matrix();
	void initCMDMap(Node node[ev::matrix::cols][ev::matrix::rows], int start, int pol);
	void gatherInitialData();
	void activateNodePair(Node positive, Node negative);
	void toggleLatches(bool state);

	int gatherInitialHeatMapData();
	void rampAndRecord(bool direction, double& store);
	void ramp(bool direction);
};

#endif // MATRIX_H