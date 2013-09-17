#ifndef OFXSKINNABLE_H
#define OFXSKINNABLE_H


#include "SkinnableObject.h"
#include "SkinnableObjectHub.h"
#include "SkinnableData.h"
#include "SkinnableTextData.h"

class ofxSkinnable
{
public : 
	ofxSkinnable() 
	{
		IMAGE_TYPE = 0 ; 
		TEXTBLOCK_TYPE = 1 ; 
		ICON_TYPE = 2 ; 
	}

	 static ofxSkinnable* Instance()
        {
            static ofxSkinnable inst ;
            return &inst ;
        }

	  ofEvent<string> ACTIVATE_SKINNABLE_OBJECT ;
      ofEvent<string> DEACTIVATE_SKINNABLE_OBJECT ;
      ofEvent<SkinnableData> HUB_UPDATE_OBJECT ;


	int IMAGE_TYPE ; 
	int TEXTBLOCK_TYPE ; 
	int ICON_TYPE ; 
};
#endif // OFXSKINNABLE_H
