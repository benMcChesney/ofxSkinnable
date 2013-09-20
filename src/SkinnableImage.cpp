//
//  SkinnableImage.cpp
//  layoutToXML_tool
//
//  Created by Ben McChesney on 9/17/13.
//
//
#include "SkinnableImage.h"

void SkinnableImage::setup ( string _name )
{
    imageData.anchorX = 0 ;
    imageData.anchorY = 0 ;
    imageData.imagePath = "none" ; 
    imageData.imageScale = 1.0f ; 
    data.type = 0 ;


}

void SkinnableImage::update ( )
{
    
    
}

void SkinnableImage::draw ( )
{
    SkinnableObject::draw( ) ; 	
    //image.alphaStackUpdate( 1.0f ) ;
    ofSetColor( 255 ) ;
    ofPushMatrix() ;
		ofTranslate( data.x , data.y ) ; 
        ofScale( imageData.imageScale , imageData.imageScale ) ;
        if ( image.bAllocated() == true )
        image.draw( 0 , 0 ) ;
    ofPopMatrix() ;
}

void SkinnableImage::writeDataToXml( ofxXmlSettings *xml , float scale )
{
    data.writeDataToXml( xml , scale ) ;
    imageData.writeDataToXml( xml , scale ) ; 
    
}

void SkinnableImage::loadDataFromXml( ofxXmlSettings *xml )
{
    data.loadDataFromXml( xml ) ;
    imageData.loadDataFromXml( xml ) ; 
	
	image.loadImage( imageData.imagePath ) ; 
}

/*
//Unique to this skinnable object
ofxMatrixTransformImage image ;
SkinnableImageData imageData ;
*/