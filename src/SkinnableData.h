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
            rotation = 0 ;
            imagePath = "" ;
            width = 0 ;
            height = 0 ;
            originalHeight = 0 ;
            originalWidth = 0 ;
            name = "noName" ;
            index = -2 ;
        }
        virtual ~SkinnableData() {}

        //Assmuing that it's pushed into the right tag.
        void writeDataToXml( ofxXmlSettings *xml )
        {
            xml->setValue( "x" , x ) ;
            xml->setValue( "y" , y ) ;
            xml->setValue( "rotation" , rotation ) ;
            xml->setValue( "originalHeight" , originalHeight ) ;
            xml->setValue( "originalWidth" , originalWidth ) ;
            xml->setValue( "width" , width ) ;
            xml->setValue( "height" , height ) ;
            xml->setValue( "imagePath" , imagePath ) ;
            xml->setValue( "name" , name ) ;
            xml->setValue( "index" , index ) ;
            xml->setValue( "pivotX" , pivot.x ) ;
            xml->setValue( "pivotY" , pivot.y ) ;
            xml->setValue( "anchorPointX" , anchorPoint.x ) ;
            xml->setValue( "anchorPointY" , anchorPoint.y ) ;
        }

        //Assmuing that it's pushed into the right tag.
        void loadDataFromXml( ofxXmlSettings *xml )
        {
            x = xml->getValue( "x" , x ) ;
            y = xml->getValue( "y" , y ) ;
            rotation = xml->getValue( "rotation" , rotation ) ;
            originalHeight = xml->getValue( "originalHeight" , originalHeight ) ;
            originalWidth = xml->getValue( "originalWidth" , originalWidth ) ;
            width = xml->getValue( "width" , width ) ;
            height = xml->getValue( "height" , height ) ;
            imagePath = xml->getValue( "imagePath" , imagePath ) ;
            name = xml->getValue( "name" , name ) ;
            index = xml->getValue( "index" , index ) ;
            pivot.x = xml->getValue( "pivotX" , pivot.x ) ;
            pivot.y = xml->getValue( "pivotY" , pivot.y ) ;
            anchorPoint.x = xml->getValue( "anchorPointX" , anchorPoint.x ) ;
            anchorPoint.y = xml->getValue( "anchorPointY" , anchorPoint.y ) ;
        }

        float x , y ;
        float rotation ;

        float originalHeight ;
        float originalWidth ;

        float width ;
        float height ;

        string imagePath ;
        ofPoint anchorPoint ;
        ofPoint pivot ;
        string name ;
        int index ;
        vector<ofVec2f> pts ;

};

#endif // SKINNABLEDATA_H
