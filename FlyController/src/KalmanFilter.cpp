/*
 * KalmanFilter.cpp
 *
 *  Created on: 7 sty 2016
 *      Author: User
 */

#include <KalmanFilter.h>

KalmanFilter::KalmanFilter(double angle, double bias, double measure)
{
    Q_angle = angle;
    Q_bias = bias;
    R_measure = measure;

    K_angle = 0;
    K_bias = 0;

    P[0][0] = 0;
    P[0][1] = 0;
    P[1][0] = 0;
    P[1][1] = 0;

    kt = (double)HAL_GetTick();
}

double KalmanFilter::update(double newValue, double newRate)
{
    dt = (double)(HAL_GetTick() - kt) / 1000000;

    K_rate = newRate - K_bias;
    K_angle += dt * K_rate;

    P[0][0] += dt * (P[1][1] + P[0][1]) + Q_angle * dt;
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    S = P[0][0] + R_measure;

    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    y = newValue - K_angle;

    K_angle += K[0] * y;
    K_bias += K[1] * y;

    P[0][0] -= K[0] * P[0][0];
    P[0][1] -= K[0] * P[0][1];
    P[1][0] -= K[1] * P[0][0];
    P[1][1] -= K[1] * P[0][1];

    kt = (double)HAL_GetTick();

    return K_angle;
};

