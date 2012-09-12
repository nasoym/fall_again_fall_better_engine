#include "logger.h"
#include "engine.h"

#include "physic_engine.h"

void	Engine::setAmbientLight(Vec3 & vec3) {
	mSceneMgr->setAmbientLight(ColourValue(vec3.x,vec3.y,vec3.z));
}

Vec3	Engine::getAmbientLight() {
	ColourValue color = mSceneMgr->getAmbientLight();
	return Vec3(color.r,color.g,color.b);
}

void	Engine::setCameraFOV(float fov) {
	mCamera->setFOVy(Radian(Degree(fov)));
}

float	Engine::getCameraFOV(){
	Radian fov = mCamera->getFOVy();
	return fov.valueDegrees();
}

void	Engine::setGravity(Vec3 & vec3){
	getPhysicsEngine()->setGravity(vec3);
}

Vec3 	Engine::getGravity(){
	return getPhysicsEngine()->getGravity();
}
	
