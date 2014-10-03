#ifndef LIGHT_F_H_
#define LIGHT_F_H_

#include "CGFlight.h"

class Light: public CGFlight {
	private:
		bool visible;
	public:
		Light(unsigned int lightid, float* pos);
		~Light();
		void Light::draw();
		void setEnabled(bool enabled);
		void setVisible(bool visible);
		void setTarget(float target[4]);
		void setAngle(float angle);
		void setExponent(float exponent);
};

#endif

