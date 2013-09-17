#pragma once

#include "SkinnableObject.h"
#include "SkinnableTextData.h"
#include "ofxTextBlock.h"
class SkinnableTextBlock : public SkinnableObject
{
public : 
	virtual void setup ( string _name ) ;
	virtual void update ( ) ; 
	virtual void draw ( ) ; 

	virtual void writeDataToXml( ofxXmlSettings *xml , float scale ) ; 
	virtual void loadDataFromXml( ofxXmlSettings *xml ) ; 

	//Unique to this skinnable object

	ofxTextBlock textBlock ; 
	
	SkinnableTextData textData ;
	void applyTextData ( )  ;  
	
	float lastFontSize ;
	string lastFontPath ; 
	string lastTextBlock ; 

};