#pragma once
#include "SkinnableData.h"

class SkinnableTextData
{
public : 

	SkinnableTextData( ) 
	{
		bWrapX = false  ; 
		bWrapBox = false ; 

		lineSpacing = 1.5f ; 
		fontSize = 12.0f ; 
		fontPath = "none" ;  
		blockText = "no text" ; 

		bDrawRight = false ; 
		bDrawCenter = false ; 
		bDrawLeft = false ; 
		grayscaleColor = 128 ; 
	}
	//Assmuing that it's pushed into the right tag.
    void writeDataToXml( ofxXmlSettings *xml , float scale )
    {
		xml->setValue( "bWrapX" , bWrapX ) ; 
        //xml->setValue( "bWrapY" , bWrapY ) ;
        xml->setValue( "bWrapBox" , bWrapBox ) ;
        xml->setValue( "lineSpacing" , lineSpacing * scale ) ;
        xml->setValue( "fontSize" , fontSize * scale ) ;
        xml->setValue( "fontPath" , fontPath ) ;
		xml->setValue( "blockText" , blockText ) ; 
		xml->setValue( "bDrawRight" , bDrawRight ) ;
		xml->setValue( "bDrawCenter" , bDrawCenter ) ;
		xml->setValue( "bDrawLeft" , bDrawLeft ) ;
		xml->setValue( "grayscaleColor" , grayscaleColor ) ; 

		
    }

    //Assmuing that it's pushed into the right tag.
    void loadDataFromXml( ofxXmlSettings *xml  )
    {
		bWrapX = xml->getValue( "bWrapX" , false ) ; 
        //bWrapY = xml->getValue( "bWrapY" , false ) ;
        bWrapBox = xml->getValue( "bWrapBox" , false ) ;
        lineSpacing = xml->getValue( "lineSpacing" , 1.0f ) ;
        fontSize = xml->getValue( "fontSize" , 14 ) ;
        fontPath = xml->getValue( "fontPath" , "noFont.otf"  ) ;
		blockText = xml->getValue( "blockText" , "no text at all"  ) ;
		bDrawRight = xml->getValue( "bDrawRight" , false ) ;
		bDrawCenter = xml->getValue( "bDrawCenter" , false ) ;
		bDrawLeft = xml->getValue( "bDrawLeft" , false ) ;
		grayscaleColor = xml->getValue( "grayscaleColor" , 128 ) ; 
    }

	string toString() 
	{
		stringstream ss ; 
		ss << "bWrapX : " << bWrapX << endl;
		ss << "bWrapBox : " << bWrapBox << endl;
		ss << "lineSpacing : " << lineSpacing << endl;
		ss << "fontSize : " << fontSize << endl;
		ss << "fontPath : " << fontPath << endl;
		ss << "blockText : " << blockText << endl;
		ss << "bDrawRight : " << bDrawRight << endl ; 
		ss << "bDrawCenter : " << bDrawCenter << endl ; 
		ss << "bDrawLeft : " << bDrawLeft << endl ; 
		ss << "grayscaleColor : " << grayscaleColor << endl; 

		return ss.str() ; 
	}

	bool bWrapX ; 
	bool bWrapBox ; 

	float lineSpacing ; 
	float fontSize ; 
	string fontPath ; 
	string blockText ; 

	bool bDrawRight ; 
	bool bDrawCenter ; 
	bool bDrawLeft ; 

	float grayscaleColor ; 

};