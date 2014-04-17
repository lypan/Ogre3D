//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"
#include "SelectionBox.h"

// #include <CEGUI.h>
// #include <CEGUISchemeManager.h>
// #include <RendererModules/Ogre/CEGUIOgreRenderer.h>

using namespace Ogre;
class BasicTutorial_00 : public BaseApplication
{
	protected:	 
		virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
		virtual bool mouseMoved(const OIS::MouseEvent& arg);
		virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	 
		void performSelection(const Ogre::Vector2& first, const Ogre::Vector2& second);
		void deselectObjects();
		void selectObject(Ogre::MovableObject* obj);

	private:
		std::vector<Ogre::Entity*> mEntity;
		std::vector<Ogre::Entity*> aEntity;
		std::vector<Ogre::SceneNode*> mSceneNode;
		std::vector<Ogre::AnimationState*> mAnimationState;
		std::vector<Ogre::AnimationState*> aAnimationState;

		bool frameStarted(const FrameEvent &evt);

	   	Ogre::Real mDistance;                  
    	Ogre::Vector3 mDirection;              
	    Ogre::Vector3 mDestination;            
	    std::deque<Ogre::Vector3> mWalkList;   
	    Ogre::Real mWalkSpeed;                 

		Ogre::Vector2 mStart, mStop;
		Ogre::PlaneBoundedVolumeListSceneQuery* mVolQuery;
		std::list<Ogre::MovableObject*> mSelected;
		bool mSelecting;
		SelectionBox* mSelectionBox;
		int robotNumber;

	static void swap(float& x, float& y);
	public:
		BasicTutorial_00(void);
		~BasicTutorial_00(void);
		virtual void createScene(void);

};
 
#endif // #ifndef __BasicTutorial_00_h_

 


