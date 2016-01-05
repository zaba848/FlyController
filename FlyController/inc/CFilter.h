/*
 * CFilter.h
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */

#ifndef CFILTER_H_
#define CFILTER_H_
#include <stdint.h>
#include <stdio.h>
//#include <cstdint>

class CFilter {
public:

	 struct sensor_data_t {
		float x;
		float y;
		float z;
	} ;

	static float filter_get_x(void);
	static float filter_get_y(void);
	static float filter_get_z(void);



	static void init();
	static void update();

protected:

	static sensor_data_t alfa;
	static sensor_data_t beta;

	static sensor_data_t x_pri;
	static sensor_data_t x_post;
	static sensor_data_t v_pri;
	static sensor_data_t v_post;

	static float dt;
	static int16_t accBuffer[3];
	static float  gyroBuffer[3];
	static int16_t magBuffer[3];

	static void internalUpdate();


};

#endif /* CFILTER_H_ */
