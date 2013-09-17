#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"

class SkinnableImageData
{
public : 
	SkinnableImageData( ) 
	{
	
	}

    string imagePath ;
    float anchorX ;
    float anchorY ;
    float imageScale ;
    
    
    void writeDataToXml( ofxXmlSettings *xml , float scale )
    {
        xml->setValue( "imagePath" , imagePath ) ;
        xml->setValue( "anchorX" , 0.0f ) ;
        xml->setValue( "anchorY" , 0.0f ) ;
        xml->setValue( "imageScale" , imageScale * scale ); 
    }
    
    void loadDataFromXml( ofxXmlSettings *xml  )
    {
        imagePath = xml->getValue( "imagePath" , "none"  ) ;
        anchorY = xml->getValue( "anchorX" , 0.0f ) ;
        anchorX = xml->getValue( "anchorY" , 0.0f ) ;
        imageScale = xml->getValue( "imageScale" ,  1.0f );
    }
    
    string toString()
    {
        stringstream ss ;
        ss << "imagePath : " << imagePath << endl;
        ss << "anchorX : " << anchorX << endl ;
        ss << "anchorY : " << anchorY << endl ;
        ss << "imageScale ; " << imageScale << endl ;
        return ss.str() ; 
    }
};