//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"

using namespace Ogre;

BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::createScene(void) 
{
    /**
     * create scene and entity\n
     * set light and shadow
     */
	// task1
	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) );
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	// robot1
	mEntity 
		= mSceneMgr
		->createEntity( "Robot", "robot.mesh" ); 
	mEntity->setCastShadows(true);
	SceneNode *sNode 
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"RobotNode", Vector3( 50, 0, 0 ) ); 

	sNode->attachObject( mEntity ); 

	// robot2
	mEntity2 
		= mSceneMgr
		->createEntity( "Robot2", "robot.mesh" ); 
	mEntity2->setCastShadows(true);
	SceneNode *sNode2 
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"RobotNode2", Vector3( 50, 0, 100) ); 
	sNode2->attachObject( mEntity2 ); 
	// robot2 scale up
	Real scaleRate = 2;
	Vector3 planeScale = Vector3(scaleRate, scaleRate, scaleRate);
	sNode2->setScale(planeScale);
	// rotate
	sNode2->yaw( Ogre::Degree( -120 ) );
	// animation
	mAnimationState = mEntity->getAnimationState( "Idle" );
	mAnimationState->setLoop( true );
	mAnimationState->setEnabled( true );
	// plane
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane( 
	"ground", 
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
	 plane, 
	 1500,1500, // width, height 
	 20,20, // x- and y-segments 
	 true, // normal 
	 1, // num texture sets 
	 5,5, // x- and y-tiles 
	 Vector3::UNIT_Z // upward vector 
	 );
    Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	// cubes
	// cube one
	int numCubes = 30; 
	int L = 255; 
	for (int i = 0; i < numCubes; i ++) 
	{
		// generate unique name
		std::stringstream ss;
		ss.str("");
		ss.clear();
		ss << i;
		std::string s;
		ss >> s;
		std::string sname = "scene1" + s;
		std::string ename = "entity1" + s;
		// entity and sceneNode
		Entity *ent = mSceneMgr->createEntity( 
		ename, "cube.mesh");
		ent->setMaterialName("Examples/SphereMappedRustySteel");
		ent->setCastShadows(true);
		AxisAlignedBox bb = ent->getBoundingBox(); 
		Real cubeSize = bb.getMaximum().x 
		- bb.getMinimum().x; 
		Real x = 0, y = 0, z = -125; 
		SceneNode *sn 
			= mSceneMgr 
			->getRootSceneNode() 
			->createChildSceneNode(sname); 
		sn->attachObject(ent);

		Real fx = i/((Real)numCubes-1); 
		x = fx*L - L/2; 
		Real h = (1+cos(fx*3.1415*2))*50; 
		Real unitF = 1.0/cubeSize/numCubes*L*0.8;   
		sn->scale(unitF, h/cubeSize, unitF); 
		sn->setPosition(x, 50, z); 
	}
	// cube two
	numCubes = 30; 
	L = 255; 
	for (int i = 0; i < numCubes; i ++) 
	{
		// generate unique name
		std::stringstream ss;
		ss.str("");
		ss.clear();
		ss << i;
		std::string s;
		ss >> s;
		std::string sname = "scene2" + s;
		std::string ename = "entity2" + s;
		// entity and sceneNode
		Entity *ent2 = mSceneMgr->createEntity( 
		ename, "cube.mesh");
		ent2->setMaterialName("Examples/Chrome");
		ent2->setCastShadows(true);
		AxisAlignedBox bb = ent2->getBoundingBox(); 
		Real cubeSize = bb.getMaximum().x 
		- bb.getMinimum().x; 
		Real x = 0, y = 0, z = 125; 
		SceneNode *sn2
			= mSceneMgr 
			->getRootSceneNode() 
			->createChildSceneNode(sname); 
		sn2->attachObject(ent2);

		Real fx = i/((Real)numCubes-1); 
		x = fx*L - L/2; 
		Real h = 20*(1+sin(fx*3.1415*2)); 
		Real unitF = 1.0/cubeSize/numCubes*L*0.8;   
		sn2->scale(unitF, h/cubeSize, unitF); 
		sn2->setPosition(x, 50, z); 
	}
	// two light
	// light1
	Light* light1 = mSceneMgr->createLight("Light1");
	light1->setType(Light::LT_POINT); 
	light1->setPosition(Vector3(150, 250, 100)); 
	light1->setDiffuseColour(0.0, 1.0, 0.0); 
	light1->setSpecularColour(0.0, 1.0, 0.0); 

	// light2
	Light* light2 = mSceneMgr->createLight("Light2"); 
	light2->setType(Light::LT_POINT);
	light2->setPosition(Vector3(-150, 300, 250));
	light2->setDiffuseColour(0.5, 0.5, 0.5); 
	light2->setSpecularColour(0.5, 0.5, 0.5); 
	// task2
	// mSceneMgr2
	mSceneMgr2->setAmbientLight( ColourValue(1, 0, 0) ); 
	mSceneMgr2->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// plane2
	Plane plane2(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane( 
	"ground2", 
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
	 plane2, 
	 1500,1500, // width, height 
	 20,20, // x- and y-segments 
	 true, // normal 
	 1, // num texture sets 
	 5,5, // x- and y-tiles 
	 Vector3::UNIT_Z // upward vector 
	 );
    Entity* entGround2 = mSceneMgr2->createEntity("GroundEntity2", "ground2");
    entGround2->setMaterialName("Examples/Rockwall");
    entGround2->setCastShadows(false);
	mSceneMgr2->getRootSceneNode()->createChildSceneNode()->attachObject(entGround2);
	// ligh3
	Light* light3 = mSceneMgr2->createLight("Light3");
	light3->setType(Light::LT_POINT); 
	light3->setPosition(Vector3(100, 150, 250)); 
	light3->setDiffuseColour(0.0, 0.0, 1.0); //blue 
	light3->setSpecularColour(0.0,0.0, 1.0); //blue
	// sphere
	mEntity3 
		= mSceneMgr2
		->createEntity( "Sphere", "sphere.mesh" );
	mEntity3->setMaterialName("Examples/green");
	mEntity3->setCastShadows(true);
	SceneNode *sNode3 
		= mSceneMgr2
		->getRootSceneNode()
		->createChildSceneNode( 
		"SphereNode", Vector3( 0, 0, 0) ); 
	sNode3->attachObject( mEntity3 ); 
	Vector3 scaleSphere = Vector3(1, (Real)1/2, 0.6);
	sNode3->setScale(scaleSphere);
}
bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	mAnimationState->addTime(evt.timeSinceLastFrame);
	if ( mKeyboard->isKeyDown(OIS::KC_S) ) {
		mAnimationState = mEntity->getAnimationState( "Walk" );
		mAnimationState->setLoop( true );
		mAnimationState->setEnabled( true );
	}
	return true;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
