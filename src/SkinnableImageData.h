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
	string localImagePath ; 
    float anchorX ;
    float anchorY ;
    float imageScale ;
    
    

    void writeDataToXml( ofxXmlSettings *xml , float scale )
    {
        xml->setValue( "imagePath" , imagePath ) ;
    
		string localPath = imagePath ; 

		cout << endl ;
		cout << "imagePath : " << imagePath << endl ; 
		int binIndex = localPath.find_last_of( "\\" ) ; 
		cout << "binIndex : " << binIndex << endl ; 
		if ( binIndex > -1 ) 
		{
		
		
		localPath = imagePath.substr( binIndex+1  ) ; 

		cout << "localPath : " << localPath << endl ; 
		/*

		*/}
		xml->setValue( "localPath" , localPath ) ; 
	
		xml->setValue( "anchorX" , 0.0f ) ;
        xml->setValue( "anchorY" , 0.0f ) ;
        xml->setValue( "imageScale" , imageScale * scale ); 
    }
    
    void loadDataFromXml( ofxXmlSettings *xml  )
    {
        imagePath = xml->getValue( "imagePath" , "none"  ) ;
		string localPath = xml->getValue( "localPath" , "none" ) ; 
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