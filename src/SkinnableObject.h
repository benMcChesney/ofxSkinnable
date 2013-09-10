#pragma once

#include "ofMain.h"
#include "BasePolyObject.h"
#include "ofxAlphaStackItem.h"
#include "SkinnableData.h"
#include "ofxSkinnableEvents.h"

class SkinnableObject : public ofxAlphaStackItem
{
    public:
        SkinnableObject();
        virtual ~SkinnableObject();

        //If you already have the data you need
        void setup ( SkinnableData _data ) ;
        void activateEventHandler ( string &args ) ;
        void deactivateEventHandler( string &args ) ;
        void hubUpdateHandler ( SkinnableData &args ) ;
        
		bool bSelected ;

		//Overwritten functions in super clsses
		virtual void draw  ( ) ;
		virtual void setup ( ) ; 
		virtual void update ( ) ; 
		virtual void writeDataToXml( ofxXmlSettings *xml , float scale ) ; 
		virtual void loadDataFromXml( ofxXmlSettings *xml ) ; 

		bool checkHitTest( float x , float y ) ; 

		 SkinnableData data ;
		 float rotation ; 

    private:
};

