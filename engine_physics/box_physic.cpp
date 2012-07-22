//-------------------------------------
#include "box_physic.h"
#include "logger.h"
//-------------------------------------
Actor::Actor(PhysicsEngine& engine, object size, object pos):
        mEngine(&engine)  
        {
    mSizeX = boost::python::extract<float>(size[0]);
    mSizeY = boost::python::extract<float>(size[1]);
    mSizeZ = boost::python::extract<float>(size[2]);

    mBody = (mEngine->getPhysics())->createRigidDynamic(
        PxTransform(PxVec3(
            boost::python::extract<float>(pos[0]),
            boost::python::extract<float>(pos[1]),
            boost::python::extract<float>(pos[2])
            ))
        );
    mShape = mBody->createShape(
        PxBoxGeometry(PxVec3(
            mSizeX,mSizeY,mSizeZ
        )),
        *(mEngine->getMaterial())
        );
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);

    (mEngine->getScene())->addActor(*mBody);
}

Actor::~Actor( ){
    deleteAllJoints();
    mBody->release();
    mBody = 0;
}

PxRigidActor*    Actor::getBody() {
    return mBody;
}

void    Actor::wakeUp() {
    mBody->wakeUp();
}

float   Actor::getForceFactor() {
    return mEngine->getForceFactor();
}

int     Actor::dGetSolverIterCount() {
    PxU32 itercount;
    PxU32 veliter;
    mBody->getSolverIterationCounts(itercount,veliter);
    return itercount;
}

int     Actor::dGetVelocityIterCount() {
    PxU32 itercount;
    PxU32 veliter;
    mBody->getSolverIterationCounts(itercount,veliter);
    return veliter;
}

void    Actor::dSetSolverIterCount(int count) {
    mBody->setSolverIterationCounts(
        count,
        dGetVelocityIterCount()
        );
}
void    Actor::dSetVelocityIterCount(int count) {
    mBody->setSolverIterationCounts(
        dGetSolverIterCount(),
        count
        );
}

tuple   Actor::getPosition( ) {
    PxTransform t = mBody->getGlobalPose();
    return make_tuple(t.p.x,t.p.y,t.p.z);
}

tuple   Actor::getOrientation() {
    PxTransform t = mBody->getGlobalPose();
    return make_tuple(t.q.w,t.q.x,t.q.y,t.q.z);
}

tuple   Actor::getSize() {
    return make_tuple(mSizeX, mSizeY, mSizeZ);
}

void    Actor::setPosition(object args) {
    PxTransform t = mBody->getGlobalPose();
    t.p.x = boost::python::extract<float>(args[0]);
    t.p.y = boost::python::extract<float>(args[1]);
    t.p.z = boost::python::extract<float>(args[2]);
    mBody->setGlobalPose(t);
    wakeUp();
}

void    Actor::setOrientation(object args) {
    PxTransform t = mBody->getGlobalPose();
    t.q.x = boost::python::extract<float>(args[1]);
    t.q.y = boost::python::extract<float>(args[2]);
    t.q.z = boost::python::extract<float>(args[3]);
    t.q.w = boost::python::extract<float>(args[0]);
    mBody->setGlobalPose(t);
    wakeUp();
}

void    Actor::setSize(object args) {
    mSizeX = boost::python::extract<float>(args[0]);
    mSizeY = boost::python::extract<float>(args[1]);
    mSizeZ = boost::python::extract<float>(args[2]);
    mShape->setGeometry(PxBoxGeometry(PxVec3(
        mSizeX,mSizeY,mSizeZ
        )));
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    wakeUp();
}

void    Actor::setMass(float newMass) {
    mBody->setMass(PxReal(newMass));
    //TODO how to reset inertia?
    wakeUp();
}

float    Actor::getMass() {
    return mBody->getMass();
}

void    Actor::addForce(object args) {
    mBody->addForce(
        PxVec3(
            extract<float>(args[0]) * getForceFactor(),
            extract<float>(args[1]) * getForceFactor(),
            extract<float>(args[2]) * getForceFactor()
        ),
        PxForceMode::eIMPULSE,
        //PxForceMode::eFORCE,
        true
        );
}



/*
void    Actor::deleteAllJoints() {
    std::set<Joint*>::iterator  mJointsIterator;
    for (mJointsIterator = mJoints.begin(); 
        mJointsIterator != mJoints.end(); ++mJointsIterator) {
        delete (*mJointsIterator);
    }
    mJoints.clear();
}

void    Actor::deleteJoint(Joint* joint) {
    std::set<Joint*>::iterator  mJointsIterator;
    for (mJointsIterator = mJoints.begin(); 
        mJointsIterator != mJoints.end(); ++mJointsIterator) {
        if ( (*mJointsIterator) == joint ){
            delete (*mJointsIterator);
            mJoints.erase( mJointsIterator);
            break;
        }
    }
}

void    Actor::deleteJointPtr( Joint* joint ) {
    std::set<Joint*>::iterator  mJointsIterator;
    for (mJointsIterator = mJoints.begin(); 
        mJointsIterator != mJoints.end(); ++mJointsIterator) {
        if ( (*mJointsIterator) == joint ){
            mJoints.erase( mJointsIterator);
            break;
        }
    }
}

int     Actor::howManyJoints() {
    return mJoints.size();
}

void    Actor::addJoint(Joint* joint){
    mJoints.insert(joint);
}
*/

