#include "SkinnableIcon.h"

void SkinnableIcon::setup ( string _name ) 
{
	SkinnableObject::setup( ) ; 
}

void SkinnableIcon::update ( ) 
{

}

void SkinnableIcon::draw ( ) 
{
	SkinnableObject::draw( ) ; 
}

void SkinnableIcon::writeDataToXml( ofxXmlSettings *xml , float scale ) 
{
	data.writeDataToXml( xml , scale ) ; 
}

void SkinnableIcon::loadDataFromXml( ofxXmlSettings *xml )
{
	data.loadDataFromXml( xml ) ; 
} 