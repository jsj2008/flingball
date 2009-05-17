//
// C++ Interface: camera
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_CAMERA_H
#define INC_CAMERA_H
#include "globals.h"

class CCamera {
	public:
		CCamera();
		bool setViewport(int, int, int, int);
		
	private:
		int x;
		int y;
		
		int w;
		int h;
};

#endif