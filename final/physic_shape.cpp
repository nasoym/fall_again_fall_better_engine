#include "logger.h"
#include "physic_shape.h"
#include "engine.h"
#include "physic_engine.h"
#include "actor.h"

PhysicShape::PhysicShape(Engine* engine,Actor* actor,PxShape* shape) :
	EngineGuiShape(engine),
	mShape(shape),
	mActor(actor),
	mMesh(0),
	mShapeType(NOP)
	{
}

PhysicShape::~PhysicShape() {

}

void	PhysicShape::enableCollisions(){
	mShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,true);
}

void	PhysicShape::dissableCollisions(){
	mShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,false);
}

void	PhysicShape::setBoxShape(){
	mShapeType = BOX;
}

void	PhysicShape::setSphereShape(){
	mShapeType = SPHERE;
}

void	PhysicShape::setCapsuleShape(){
	mShapeType = CAPSULE;
}

void	PhysicShape::setPlaneShape(){
	mShapeType = PLANE;
}


bool	PhysicShape::isBoxShape(){
	if (mShapeType == BOX) return true;
	return false;
}

bool	PhysicShape::isSphereShape(){
	if (mShapeType == SPHERE) return true;
	return false;
}

bool	PhysicShape::isCapsuleShape(){
	if (mShapeType == CAPSULE) return true;
	return false;
}

bool	PhysicShape::isPlaneShape(){
	if (mShapeType == PLANE) return true;
	return false;
}

void PhysicShape::createGuiBox(Vec3& vec3) {
    setEntity(getEngine()->getSceneManager()->createEntity("Prefab_Cube"));
    getNode()->attachObject(getEntity());
	setLocalSize(vec3);
}

void PhysicShape::createGuiSphere(Vec3& vec3) {
    setEntity(getEngine()->getSceneManager()->createEntity("Prefab_Sphere"));
    getNode()->attachObject(getEntity());
	setLocalSize(vec3);
}

void PhysicShape::createGuiCapsule(Vec3& vec3) {
	if (mMesh != 0 ) {
		getNode()->detachObject(getEntity());
		getEngine()->getSceneManager()->destroyEntity(getEntity());
		setEntity(0);
		MeshManager::getSingleton().remove(mMesh->getHandle());
		mMesh = 0;
	}

	Procedural::CapsuleGenerator capsule = Procedural::CapsuleGenerator();
	capsule.setHeight(vec3.x*2.0f);
	capsule.setRadius(vec3.y);

	//capsule.setNumRings(3); //8
	//capsule.setNumSegments(8); //16

	capsule.setNumSegHeight(1); //1

	capsule.setOrientation(Quat().fromAngles(0,0,90).toOgre());
	MeshPtr meshPtr = capsule.realizeMesh();

    setEntity(getEngine()->getSceneManager()->createEntity(meshPtr));
    getEntity()->setMaterialName("Body");
    getNode()->attachObject(getEntity());
	mMesh = meshPtr.get();

	if (hasColour()) {
		setCustomMaterial();
	}
}

void PhysicShape::updateGuiCapsule(Vec3& vec3) {
	createGuiCapsule(vec3);
}

void        PhysicShape::setLocalPosition(Vec3& vec3){
    PxTransform t = mShape->getLocalPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mShape->setLocalPose(t);
	EngineGuiShape::setLocalPosition(vec3);
	mActor->resetMass();
	mActor->wakeUp();
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
	mActor->resetMass();
	mActor->wakeUp();
}

Quat 		PhysicShape::getLocalOrientation(){
    PxTransform t = mShape->getLocalPose();
	return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void        PhysicShape::setLocalSize(Vec3& vec3){
	switch(mShape->getGeometryType()){
		case PxGeometryType::eBOX:
			mShape->setGeometry(PxBoxGeometry(vec3.toPhysx()));
			EngineGuiShape::setLocalSize(vec3);
			break;
		case PxGeometryType::eSPHERE:
			mShape->setGeometry(PxSphereGeometry(vec3.x));
			EngineGuiShape::setLocalSize(vec3);
			break;
		case PxGeometryType::eCAPSULE:
			mShape->setGeometry(PxCapsuleGeometry(vec3.y,vec3.x));
			//updateGuiCapsule(vec3.x*2,vec3.y);
			updateGuiCapsule(vec3);
			mLocalSize = vec3;
			break;
	}
	mActor->resetMass();
	mActor->wakeUp();
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

