#include "logger.h"
#include "physic_shape.h"
#include "engine.h"
#include "physic_engine.h"
#include "actor.h"

PhysicShape::PhysicShape(Engine* engine,Actor* actor,PxShape* shape) :
	EngineGuiShape(engine),
	mShape(shape),
	mActor(actor)
	{
	mMeshPtr.setNull();
}

PhysicShape::~PhysicShape() {

}

void PhysicShape::createGuiBox() {
    setEntity(getEngine()->getSceneManager()->createEntity("Prefab_Cube"));
    getNode()->attachObject(getEntity());
}

void PhysicShape::createGuiSphere() {
    setEntity(getEngine()->getSceneManager()->createEntity("Prefab_Sphere"));
    getNode()->attachObject(getEntity());
}

void PhysicShape::createGuiCapsule(float height,float radius) {

	if (!mMeshPtr.isNull()){
		getNode()->removeAndDestroyAllChildren();
		OGRE_DELETE mMeshPtr.get();
		mMeshPtr.setNull();
		Logger::debug("deleted mesh ptr");
	}

	Procedural::CapsuleGenerator capsule = Procedural::CapsuleGenerator();
	capsule.setHeight(height);
	capsule.setRadius(radius);

	capsule.setNumRings(3); //8
	capsule.setNumSegments(8); //16
	capsule.setNumSegHeight(1); //1
	//capsule.setEnableNormals(false); //true
	capsule.setOrientation(Quat().fromAngles(0,0,90).toOgre());
	mMeshPtr = capsule.realizeMesh();
	Logger::debug("created new Mesh ptr");

    setEntity(getEngine()->getSceneManager()->createEntity(mMeshPtr));
	Logger::debug("created new entity");
    getEntity()->setMaterialName("Body");
    getNode()->attachObject(getEntity());
	Logger::debug("attached new entity to node");
}

void        PhysicShape::setLocalPosition(Vec3& vec3){
    PxTransform t = mShape->getLocalPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mShape->setLocalPose(t);
	EngineGuiShape::setLocalPosition(vec3);
}

Vec3    	PhysicShape::getLocalPosition(){
    PxTransform t = mShape->getLocalPose();
	return Vec3(t.p.x,t.p.y,t.p.z);
}

void        PhysicShape::setLocalOrientation(Quat& quat){
    PxTransform t = mShape->getLocalPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mShape->setLocalPose(t);
	EngineGuiShape::setLocalOrientation(quat);
}

Quat 		PhysicShape::getLocalOrientation(){
    PxTransform t = mShape->getLocalPose();
	return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void        PhysicShape::setLocalSize(Vec3& vec3){
	switch(mShape->getGeometryType()){
		case PxGeometryType::eBOX:
			Logger::debug("set size box type");
			mShape->setGeometry(PxBoxGeometry(vec3.toPhysx()));
			EngineGuiShape::setLocalSize(vec3);
			break;
		case PxGeometryType::eSPHERE:
			Logger::debug("set size sphere type");
			mShape->setGeometry(PxSphereGeometry(vec3.x));
			EngineGuiShape::setLocalSize(vec3);
			break;
		case PxGeometryType::eCAPSULE:
			Logger::debug("set size capsule type");
			mShape->setGeometry(PxCapsuleGeometry(vec3.x*2, vec3.y));
			createGuiCapsule(vec3.x,vec3.y);
			Logger::debug("created new gui capsule");
			mLocalSize = vec3;
			Logger::debug("set local size");
			break;
	}
	mActor->resetMass();
	Logger::debug("resetted mass");

}

Vec3    	PhysicShape::getLocalSize(){
	PxBoxGeometry		boxGeometry;
	PxSphereGeometry	sphereGeometry;
	PxCapsuleGeometry	capsuleGeometry;
	switch(mShape->getGeometryType()){
		case PxGeometryType::eBOX:
			if (mShape->getBoxGeometry(boxGeometry)) {
				return Vec3(boxGeometry.halfExtents);
			}
			break;
		case PxGeometryType::eSPHERE:
			if (mShape->getSphereGeometry(sphereGeometry)) {
				return Vec3(
					sphereGeometry.radius,
					sphereGeometry.radius,
					sphereGeometry.radius
					);
			}
			break;
		case PxGeometryType::eCAPSULE:
			if (mShape->getCapsuleGeometry(capsuleGeometry)) {
				return Vec3(
					capsuleGeometry.halfHeight,
					capsuleGeometry.radius,
					capsuleGeometry.radius
					);
			}
			break;
	}
	return Vec3();
}

