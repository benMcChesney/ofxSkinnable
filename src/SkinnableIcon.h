#pragma once

#include "SkinnableObject.h"
#include "ofxSvg.h"

class SkinnableIcon : public SkinnableObject
{

public : 
	SkinnableIcon() { } 
	~SkinnableIcon( ) { } 

	virtual void setup ( string _name ) ;
	virtual void update ( ) ; 
	virtual void draw ( ) ; 

	virtual void writeDataToXml( ofxXmlSettings *xml  , float scale ) ; 
	virtual void loadDataFromXml( ofxXmlSettings *xml ) ; 
	

	//Unique things....
	//ofxSvg icon ; 
};


