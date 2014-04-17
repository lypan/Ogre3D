//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"

using namespace Ogre;
//!  Student infomation 
/*!Course: 3D Game Programming.\n 
Name: Liang-Yun Pan.\n
ID: 9931031.\n
Email: xxzero12@gmail.com.\n
Description: assignment1.*/

class BasicTutorial_00 : public BaseApplication
{
	private:
		Entity *mEntity;// robot1
		Entity *mEntity2;// robot2
		Entity *mEntity3;// sphere
		AnimationState *mAnimationState;
		bool frameStarted(const FrameEvent &evt);
	public:
		BasicTutorial_00(void);
		virtual void createScene(void);
};
 
#endif // #ifndef __BasicTutorial_00_h_