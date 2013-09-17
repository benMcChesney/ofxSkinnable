#ifndef SKINNABLEDATA_H
#define SKINNABLEDATA_H

#include "ofxXmlSettings.h"

class SkinnableData
{
    public:
        SkinnableData()
        {
            x = 0 ;
            y = 0 ;
			anchorX = 0 ;
			anchorY = 0 ; 
            rotation = 0 ;
            width = 0 ;
            height = 0 ;
            name = "noName" ;
            index = -2 ;
			type = 0  ; 
        }
        virtual ~SkinnableData() {}

	
        //Assmuing that it's pushed into the right tag.
        void writeDataToXml( ofxXmlSettings *xml  , float scale )
        {
			xml->setValue( "type" , type ) ; 
            xml->setValue( "x" , x * scale ) ;
            xml->setValue( "y" , y * scale ) ;
			xml->setValue( "anchorX" , anchorX * scale ) ; 
			xml->setValue( "anchorY" , anchorY * scale ) ; 
            xml->setValue( "rotation" , rotation ) ;
            xml->setValue( "width" , width * scale ) ;
            xml->setValue( "height" , height * scale ) ;
            xml->setValue( "name" , name ) ;
            xml->setValue( "index" , index ) ;
        }

        //Assmuing that it's pushed into the right tag.
        void loadDataFromXml( ofxXmlSettings *xml )
        {
			int _type = xml->getValue( "type" , -1 ) ; 

			type = _type ; 
            x = xml->getValue( "x" , x ) ;
            y = xml->getValue( "y" , y ) ;
			anchorX = xml->getValue( "anchorX" , 0 ) ;
            anchorY = xml->getValue( "anchorY" , 0 ) ;
            rotation = xml->getValue( "rotation" , rotation ) ;
            width = xml->getValue( "width" , width ) ;
            height = xml->getValue( "height" , height ) ;
            name = xml->getValue( "name" , name ) ;
            index = xml->getValue( "index" , index ) ;
        }

        float x , y ;				//Global Position
		float anchorX , anchorY ;	//"local" coordinate start

        float rotation ;

        float width ;
        float height ;

        string name ;
        int index ;
   
		int type ; 
};

#endif // SKINNABLEDATA_H
