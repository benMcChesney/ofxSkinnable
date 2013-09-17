#pragma once
#include "ofMain.h"
#include "ofEvents.h"
#include "SkinnableData.h"

class ofxSkinnableEvents
{
public : 
	
	 static ofxSkinnableEvents* Instance()
        {
            static ofxSkinnableEvents inst ;
            return &inst ;
        }

	  ofEvent<string> ACTIVATE_SKINNABLE_OBJECT ;
      ofEvent<string> DEACTIVATE_SKINNABLE_OBJECT ;
      ofEvent<SkinnableData> HUB_UPDATE_OBJECT ;
};