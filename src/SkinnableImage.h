//
//  SkinnableImage.h
//  layoutToXML_tool
//
//  Created by Ben McChesney on 9/17/13.
//
//

#ifndef __layoutToXML_tool__SkinnableImage__
#define __layoutToXML_tool__SkinnableImage__

#include <iostream>

#include "SkinnableObject.h"
#include "SkinnableImageData.h"
#include "ofxMatrixTransformImage.h"

class SkinnableImage: public SkinnableObject
{
    public :
    SkinnableImage() { }
    ~SkinnableImage() { }
    
	virtual void setup ( string _name ) ;
	virtual void update ( ) ;
	virtual void draw ( ) ;
    
	virtual void writeDataToXml( ofxXmlSettings *xml , float scale ) ;
	virtual void loadDataFromXml( ofxXmlSettings *xml ) ;
    
	//Unique to this skinnable object
    ofxMatrixTransformImage image ;
    SkinnableImageData imageData ; 
    
};

#endif /* defined(__layoutToXML_tool__SkinnableImage__) */
