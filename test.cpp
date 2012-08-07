#include <stdio.h>
#include <string>
#include "math3d.h"

int main(int argc, char *argv[]) {
	printf("TESTING:\n");


	Quat	q1 = Quat().fromAngle(10.4,-30,-88.4);
	Vec3	v1 = q1.toAngles();
	Quat	q2 = Quat().fromAngle(
		v1.x,v1.y,v1.z);

	Vec3	v2 = q1.toAxis();
	float	a = q1.toAngle();

	printf("q1:%s\n",q1.toString().c_str());
	printf("v1:%s\n",v1.toString().c_str());
	printf("q2:%s\n",q2.toString().c_str());

	printf("v2:%s %3.3f\n",v2.toString().c_str(),a);

	Quat	q3 = Quat().fromAngleAxis(
		a,v2
	);
	printf("q3:%s\n",q3.toString().c_str());





	return 0;
}

