//MathUtils.cpp - some math functions for assignment 4

#ifdef TEST_BUILD
#define _USE_MATH_DEFINES
#include <cmath>
#endif
#include <iomanip>//setw()
#include <iostream>
#include <vector>

using namespace std;

//These variables and functions should be in a class somewhere...
vector<double> weights;
const double freq = 50.0;
const int steps = 360;
const double PI = 3.141592653589793238;

int train();
int ErrorAnalysis();

//train - Generate the weights for the prediction model
//        The weights are based on a sine wave. The sine wave is approximated by a Taylor Series
//        sin(wt) = wt - (wt)^3/3! + (wt)^5/5! - (wt)^7/7! + (wt)^9/9! ...
//        sin(x)  =  x -  (x)^3/3! +  (x)^5/5! -  (x)^7/7! +  (x)^9/9! ... where x=wt
int train() {
	const double w = 2.0 * PI * freq;//w=2*pi*frequency
	const double P = 1.0 / freq;//the period
	double time;//from time=0 to time=P, divided into steps
//	double fact3 = 3.0 * 2.0 * 1.0;
//	double fact5 = 5.0 * 4.0 * fact3;
//	double fact7 = 7.0 * 6.0 * fact5;
//	double fact9 = 9.0 * 8.0 * fact7;

	weights.resize(steps);
	//Generate the first quarter of the sine wave, where the Taylor Series is stable
	for (int i = 0; i <= steps / 4; ++i) {
		time = P * (double)i / steps;//from 0 to P seconds
		double x = w * time;
		weights[i] = x;// - x * x * x / fact3;// + x * x * x * x * x / fact5;// - x * x * x * x * x * x * x / fact7;// + x * x * x * x * x * x * x * x * x / fact9;
#ifdef TEST_BUILD//define TEST_BUILD to visually see the accuracy of the Taylor Series
		std::cout.precision(6);
		std::cout.setf(std::ios::fixed);
		double trueValue = sin(x);
		std::cout << "i: " << i << " time: " << time << " weights:" << weights[i] << " trueValue: " << trueValue << std::endl;*/
#endif
	}

	//Generate the second quarter of the sine wave from the first quarter
	for (int i = steps / 4; i < steps / 2; ++i) {
		weights[i] = weights[steps / 2 - i];
	}

	//Generate the second half of the sine wave from the first half
	for (int i = steps / 2; i < steps; ++i) {
		weights[i] = -weights[i - steps / 2];
	}
	return ErrorAnalysis();//modify the code such that if ErrorAnalysis returns -1, go back and extend the Taylor series by one.
	                       //Keep extending the Taylor series until ErrorAnalysis returns 0 (the series is within tolerance).
}

//ErrorAnalysis - Calculates the standard deviation of weights as compared to a true sine wave.
//                If the standard deviation is greater than a tolerance of 0.001, the function
//                returns a error.
//                standard deviation = sqrt(sum(estimate-true)^2)/(len-1))
int ErrorAnalysis() {
	double stdDev = 0.0;
	const double TOLERANCE = 0.001;
	int retVal = 0;
	const double w = 2.0 * PI * freq;
	const double P = 1.0 / freq;//the period
	double diffSum = 0.0;
	for (int i = 0; i < steps; ++i) {
		double time = P * (double)i / steps;
		double trueValue = sin(w * time);
		diffSum += (weights[i] - trueValue) * (weights[i] - trueValue);
	}
	stdDev = sqrt(diffSum / (steps - 1));
	if (stdDev > TOLERANCE) {
		std::cout << std::endl << "stdDev: " << stdDev << std::endl;
		std::cout << "ERROR: The training model is inaccurate!" << std::endl << std::endl;
		retVal = -1;
	}
	else {
		std::cout << "The training model is accurate." << std::endl << std::endl;
	}
	return retVal;
}

int main() {
	int ret = train();
	return ret;
}