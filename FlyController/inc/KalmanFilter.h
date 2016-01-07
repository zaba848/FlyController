/*
 * KalmanFilter.h
 *
 *  Created on: 7 sty 2016
 *      Author: User
 */

#ifndef KALMANFILTER_H_
#define KALMANFILTER_H_

#include <stm32l4xx_hal.h>
#include <stdint.h>
#include <stdio.h>
#include <cmath>


class KalmanFilter {
public:

	KalmanFilter(double angle = 0.001, double bias = 0.003, double measure = 0.03);
	double update(double newValue, double newRate);

private:

	double Q_angle, Q_bias, R_measure;
	double K_angle, K_bias, K_rate;
	double P[2][2], K[2];
	double S, y;
	double dt, kt;
};

#endif /* KALMANFILTER_H_ */
