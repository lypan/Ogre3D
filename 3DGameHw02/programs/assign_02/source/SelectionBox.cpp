#include "SelectionBox.h"
 
//-------------------------------------------------------------------------------------
SelectionBox::SelectionBox(const Ogre::String& name): Ogre::ManualObject(name)
{
    /** Constructor\n
     *  set projection and view identity matrix\n
     *  not query itself\n
	*/
	setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
	setUseIdentityProjection(true);
	setUseIdentityView(true);
	setQueryFlags(0);
}
 
//-------------------------------------------------------------------------------------
SelectionBox::~SelectionBox()
{
}
 
//-------------------------------------------------------------------------------------
//sets the actual corners of the box
void SelectionBox::setCorners(float left, float top, float right, float bottom)
{
    /** Set the coordinate\n
     *  first change the coordinate to -1~1\n
     *  draw the rectangle line\n
	*/
	left = left * 2 - 1;
	right = right * 2 - 1;
	top = 1 - top * 2;
	bottom = 1 - bottom * 2;
	
  	std::cout << "4......drawing\n";
	std::cout << "left:" << left << std::endl;
	std::cout << "right:" << right << std::endl;
	std::cout << "bottom:" << bottom << std::endl;
	std::cout << "top:" << top << std::endl;

	clear();
	begin("",Ogre::RenderOperation::OT_LINE_STRIP);
		position(left, top, -1);
		position(right, top, -1);
		position(right, bottom, -1);
		position(left, bottom, -1);
		position(left, top, -1);
	end();

	setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
}
 
//-------------------------------------------------------------------------------------
//an overridden function to do the same as before but you can pass vector2s instead
void SelectionBox::setCorners(const Ogre::Vector2& topLeft, const Ogre::Vector2& bottomRight)
{
    /** Set the overridden coordinate\n
     *  call the original by split out the vector2\n
	*/	
	setCorners(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
}