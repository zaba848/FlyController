/*
 * CCFilter.cpp
 *
 *  Created on: 5 sty 2016
 *      Author: User
 */

#include <CFilter.h>

CFilter::sensor_data_t CFilter::alfa;
CFilter::sensor_data_t CFilter::beta;

CFilter::sensor_data_t CFilter::x_pri;
CFilter::sensor_data_t CFilter::x_post;
CFilter::sensor_data_t CFilter::v_pri;
CFilter::sensor_data_t CFilter::v_post;

float CFilter::dt;

void CFilter::init()
{
	  dt = 0.1;

	 alfa.x = 0.2;
	 alfa.y = 0.2;
	 alfa.z = 0.2;

	 beta.x = 0.05;
	 beta.y = 0.05;
	 beta.z = 0.05;

	 x_pri.x = 0;
	 x_pri.y = 0;
	 x_pri.z = 0;

	 x_post.x = 0;
	 x_post.y = 0;
	 x_post.z = 0;

	 v_pri.x = 0;
	 v_pri.y = 0;
	 v_pri.z = 0;

	 v_post.x = 0;
	 v_post.y = 0;
	 v_post.z = 0;


}
 float CFilter::CFilter_get_x(void) {
	return x_post.x;
}

 float CFilter::CFilter_get_y(void) {
	return x_post.y;
}

 float CFilter::CFilter_get_z(void) {
	return x_post.z;
}

 void CFilter::update() {



	x_pri.x = x_post.x + dt * v_post.x;
	x_pri.y = x_post.y + dt * v_post.y;
	x_pri.z = x_post.z + dt * v_post.z;

	v_pri.x = v_post.x;
	v_pri.y = v_post.y;
	v_pri.z = v_post.z;

	x_post.x = x_pri.x + alfa.x * (sensor_acc_get_x() - x_pri.x);
	x_post.y = x_pri.y + alfa.y * (sensor_acc_get_y() - x_pri.y);
	x_post.z = x_pri.z + alfa.z * (sensor_acc_get_z() - x_pri.z);
	v_post.x = v_pri.x + beta.x * (sensor_acc_get_x() - x_pri.x) / dt;
	v_post.y = v_pri.y + beta.y * (sensor_acc_get_y() - x_pri.y) / dt;
	v_post.z = v_pri.z + beta.z * (sensor_acc_get_z() - x_pri.z) / dt;

}

