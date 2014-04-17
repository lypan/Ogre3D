/*! \class BasicTutorial_00
    \brief 
		    3D Game Programming
		    Name:Liang-Yu-Pan
		    ID:9931031
		    Email:xxzero12@gmail.com
*/
#include "TutorialApplication.h"
#include "BasicTools.h"
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void){
    /** Constructor\n
     *  initialize the needed variables\n
	*/
	mSelecting = false;
	mWalkSpeed = 35.0f;
	robotNumber = 0;
}

void BasicTutorial_00::createScene(void) 
{
    /** Create the scene\n
     *  setting the objects that needed\n
     *  light , plane, robot etc\n
	*/
	mSceneMgr->setAmbientLight( ColourValue( 0.3, 0.3, 0.3 ) );
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

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
	SceneNode *gNode 
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"GroundNode", Vector3( 0, 0, 0 ) ); 
	gNode->attachObject( entGround ); 	

	int numRows = 6;
	int numCols = 6;
	for (int i = 0; i < numRows; i ++) 
	{ 
		for (int j = 0; j < numCols; j ++)
		{
			std::stringstream ss;
			ss.str("");
			ss.clear();
			ss << i * 6 + j;
			std::string s;
			ss >> s;

			std::string sname = "scene" + s;
			std::string ename = "entity" + s;

			Entity *ent = mSceneMgr->createEntity( 
			ename, "robot.mesh");
			ent->setCastShadows(true);

			SceneNode *sn 
				= mSceneMgr 
				->getRootSceneNode() 
				->createChildSceneNode( 
						sname, Vector3(-j * 60 , 0, -i * 60) ); 
			mEntity.push_back(ent); 

			sn->attachObject(ent);
			mSceneNode.push_back(sn);

			if(i == 0 && j == 0)
			{
				ParticleSystem* p = mSceneMgr->createParticleSystem("explosion", "Examples/Smoke");
				ParticleEmitter *e = p->getEmitter(0);
				e->setEnabled(true);
				sn->attachObject(p);
				sn->setPosition(Vector3::ZERO);
				sn->setVisible(true);
			}
		}
	}

	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

    Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(1.0, 0, 0);
    spotLight->setSpecularColour(1.0, 0, 0);
 
    spotLight->setDirection(-25, -25, 0);
    spotLight->setPosition(Ogre::Vector3(0, 50, 0));
 
    spotLight->setSpotlightRange(Ogre::Degree(25), Ogre::Degree(50));


    Ogre::SceneNode *rotatePoint = mSceneMgr->getRootSceneNode()->createChildSceneNode("rotatePoint");
    rotatePoint->setPosition(0.0,50.0,0.0); 
    rotatePoint->attachObject(spotLight);

    spotLight->setPosition(Ogre::Vector3(50, 50, 0));

    mSelectionBox = new SelectionBox("SelectionBox");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mSelectionBox);
	mVolQuery = mSceneMgr->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList());
}
//-------------------------------------------------------------------------------------

bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
    /** Frame animation\n
     *  setting the objects animations\n
     *  to change state between idle, walk\n
     *  robots go to same locations\n
	*/
	for (size_t i = 0; i < mEntity.size(); i ++)
	{
		std::string entityName = mEntity[i]->getName();
		Entity *mEntityName = mSceneMgr->getEntity(entityName);
		AnimationState* mAnimationStateName = mEntityName->getAnimationState( "Idle" );
		mAnimationStateName->addTime(evt.timeSinceLastFrame);
		mAnimationStateName->setLoop( true );
		mAnimationStateName->setEnabled( true );			
	}


	if(!mWalkList.empty())
	{

		Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
		mDestination = mWalkList.front(); 
		std::list<Ogre::MovableObject*>::iterator iter;

		size_t index;
		for(index = 0; index < aEntity.size(); index ++)
		{
			if(aEntity[index] != NULL)
			{
				aEntity[index]->getAnimationState( "Walk" );	
				aAnimationState[index]->addTime(evt.timeSinceLastFrame);
				aAnimationState[index]->setLoop( true );
				aAnimationState[index]->setEnabled( true );		

				mDirection = mDestination - aEntity[index]->getParentSceneNode()->getPosition();
				mDistance = mDirection.normalise();
				Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
				mDistance -= move;

				if (mDistance <= 0.0f)
				{
					aEntity[index]->getParentSceneNode()->setPosition(mDestination);
					aEntity[index]->getAnimationState( "Idle" );	
					aAnimationState[index]->addTime(evt.timeSinceLastFrame);
					aAnimationState[index]->setLoop( true );
					aAnimationState[index]->setEnabled( true );	

					robotNumber --;
					aEntity[index] = NULL;
					
					if(robotNumber <= 0)
					{
						mWalkList.clear();
					}
				}
				else
				{
					aEntity[index]->getParentSceneNode()->translate(mDirection * move);

					Ogre::Vector3 src = aEntity[index]->getParentSceneNode()->getOrientation() * Ogre::Vector3::UNIT_X;
			        if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) 
			        {
			            aEntity[index]->getParentSceneNode()->yaw(Ogre::Degree(180));
			        }
			        else
			        {
			            Ogre::Quaternion quat = src.getRotationTo(mDirection);
			            aEntity[index]->getParentSceneNode()->rotate(quat);
			        }
				}
			}
		}
	}

	Ogre::SceneNode *rotatePoint = mSceneMgr->getSceneNode("rotatePoint");
	rotatePoint->rotate(Ogre::Quaternion(Ogre::Degree(10), Ogre::Vector3(0, 1, 0)) , Ogre::Node::TS_LOCAL);
	
	return true;
}

//-------------------------------------------------------------------------------------
bool BasicTutorial_00::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{	
    /** Mouse pressed event\n
     *  first check left or right button\n
     *  then do the drag event prepare for left\n
     *  or do the move event prepare for right\n
	*/
	if (id == OIS::MB_Left) {
		const OIS::MouseState &ms = mMouse->getMouseState();

		Ray mRay = mTrayMgr->getCursorRay(mCamera);
		Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());

		mStart.x = scn.x;
		mStart.y = scn.y + 1;
		mStop = mStart;

		mSelecting = true;
		mSelectionBox->clear();
		mSelectionBox->setVisible(true);
	}
	else if (id == OIS::MB_Right) {

		Ray mRay = mTrayMgr->getCursorRay(mCamera);
		RaySceneQuery *mRaySceneQuery = mSceneMgr->createRayQuery(Ray()); 
		mRaySceneQuery->setSortByDistance(true); 
		mRaySceneQuery->setRay(mRay);
		RaySceneQueryResult &result = mRaySceneQuery->execute();

		Ogre::RaySceneQueryResult::iterator itr = result.begin( );
		Vector3 intersection;
		for(; itr != result.end(); itr ++)
        {
			std::string objName = itr->movable->getName();
			if(objName == "GroundEntity")
			{
				intersection =  mRay.getPoint(itr->distance);
			}

		}

		std::list<Ogre::MovableObject*>::iterator iter;

		aEntity.clear();
		aAnimationState.clear();

		int count = 0;
		for(iter = mSelected.begin(); iter != mSelected.end(); iter++)
		{
			std::string entityName = (*iter)->getName();
			Entity *mEntityName = mSceneMgr->getEntity(entityName);

			aEntity.push_back(mEntityName);
			aAnimationState.push_back(aEntity.back()->getAnimationState("Walk"));
			aAnimationState.back()->setLoop(true);
			aAnimationState.back()->setEnabled(true);
			count ++;
		}

		robotNumber = count;
		mWalkList.clear();
		mWalkList.push_back(intersection);

	}
	return BaseApplication::mousePressed( arg, id );
}
bool BasicTutorial_00::mouseMoved(const OIS::MouseEvent& arg)
{
    /** Mouse moved event\n
     *  first check it is selecting or not\n
     *  yes-> get and record the cursor position\n
     *  no-> return form inherited function\n
	*/
	if (mSelecting)
    {
		Ray mRay = mTrayMgr->getCursorRay(mCamera);
		Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());

		mStop.x = scn.x;
		mStop.y = scn.y + 1;

        mSelectionBox->setCorners(mStart, mStop);
    }
	return BaseApplication::mouseMoved( arg);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial_00::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{	
    /** Mouse realeased event\n
     *  first check the button is left or not\n
     *  yes-> do the selection\n
     *  no-> return inherited function\n
	*/
	if (id == OIS::MB_Left)
	{	
	    performSelection(mStart, mStop);
	    mSelecting = false;
	    mSelectionBox->setVisible(false);
	}
	return BaseApplication::mouseReleased( arg, id );
}
 
//-------------------------------------------------------------------------------------
void BasicTutorial_00::performSelection(const Ogre::Vector2& first, const Ogre::Vector2& second)
{	
    /** Select the objects\n
     *  first convert all selection box to the same\n
     *  do the plane ray query\n
     *  select all of the objects queried \n
	*/
	float left = first.x, right = second.x;
	float top = first.y, bottom = second.y;
 
	if(left > right)
	{
		swap(left, right);
	}
	if(top > bottom)
	{
		swap(top, bottom);
	}

	if((right == left) && (bottom == top))
	{
		Ray mRay = mTrayMgr->getCursorRay(mCamera);
		RaySceneQuery *mRaySceneQuery = mSceneMgr->createRayQuery(Ray()); 
		mRaySceneQuery->setSortByDistance(true); 
		mRaySceneQuery->setRay(mRay);
		RaySceneQueryResult &result = mRaySceneQuery->execute();
		Ogre::RaySceneQueryResult::iterator iter;

		deselectObjects();
		bool first = true;
		for(iter = result.begin(); iter != result.end(); iter++)
		{	
			if(!first)break;
			selectObject(iter->movable);
			first = false;
		}
		return;	
	}

	if((right - left) * (bottom - top) < 0.0001)
	{
		return;
	}
	Ogre::Real nleft = left;
	Ogre::Real nright = right;
	Ogre::Real ntop = 1 + top;
	Ogre::Real nbottom = 1 + bottom;

	Ogre::Ray topLeft = mTrayMgr->screenToScene(mCamera, Vector2(left, top));
	Ogre::Ray topRight = mTrayMgr->screenToScene(mCamera, Vector2(right, top));
	Ogre::Ray bottomLeft = mTrayMgr->screenToScene(mCamera, Vector2(left, bottom));
	Ogre::Ray bottomRight = mTrayMgr->screenToScene(mCamera, Vector2(right, bottom));
 
	Ogre::PlaneBoundedVolume vol;
 
	vol.planes.push_back(Ogre::Plane(topLeft.getPoint(3), topRight.getPoint(3), bottomRight.getPoint(3)));
	vol.planes.push_back(Ogre::Plane(topLeft.getOrigin(), topLeft.getPoint(100), topRight.getPoint(100)));
	vol.planes.push_back(Ogre::Plane(topLeft.getOrigin(), bottomLeft.getPoint(100), topLeft.getPoint(100)));
	vol.planes.push_back(Ogre::Plane(bottomLeft.getOrigin(), bottomRight.getPoint(100), bottomLeft.getPoint(100)));
	vol.planes.push_back(Ogre::Plane(topRight.getOrigin(), topRight.getPoint(100), bottomRight.getPoint(100)));
 
	Ogre::PlaneBoundedVolumeList volList;
	volList.push_back(vol);
 
	mVolQuery->setVolumes(volList);	
	Ogre::SceneQueryResult& result = mVolQuery->execute();
 
	deselectObjects();
	Ogre::SceneQueryResultMovableList::iterator iter;
	for(iter = result.movables.begin(); iter != result.movables.end(); iter++)
	{
		selectObject(*iter);
	}
}
 
//-------------------------------------------------------------------------------------
void BasicTutorial_00::deselectObjects()
{
    /** Deselect the objects\n
     *  first iterate over all objects selected\n
     *  set their bounding box invisible\n
	*/
	std::list<Ogre::MovableObject*>::iterator iter;
 
	for(iter = mSelected.begin(); iter != mSelected.end(); iter++)
	{
		(*iter)->getParentSceneNode()->showBoundingBox(false);
	}
	mSelected.clear();
}
 
//-------------------------------------------------------------------------------------
void BasicTutorial_00::selectObject(Ogre::MovableObject* obj)
{
    /** Select the objects\n
     *  first iterate over all objects queried\n
     *  set their bounding box visible\n
	*/
     std::cout << "objName:" << obj->getName() << std::endl;
	if(obj->getName() != "GroundEntity")
	{
		obj->getParentSceneNode()->showBoundingBox(true);
		mSelected.push_back(obj);
	}
}
 
//-------------------------------------------------------------------------------------
//Simple function that just swaps float values
void BasicTutorial_00::swap(float& x, float& y)
{
    /** Swap the variables\n
     *  a utility function to help to swap variables\n
	*/	
	float temp = x;
	x = y;
	y = temp;
}

BasicTutorial_00::~BasicTutorial_00(void)
{
    /** Destructor\n
     *  destroy the variable to free memory\n
	*/
	if(mVolQuery)
	{
		mSceneMgr->destroyQuery(mVolQuery);
	}
 
	if(mSelectionBox)
	{
		delete mSelectionBox;
	}
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
