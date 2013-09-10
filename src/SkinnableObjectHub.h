#ifndef SKINNABLEOBJECTHUB_H
#define SKINNABLEOBJECTHUB_H

#include "SkinnableObject.h"
#include "SkinnableData.h"
#include "SkinnableTextBlock.h"
#include "ofxXmlSettings.h"
#include "ofxPolygonHitTest.h"

class SkinnableObjectHub
{
    public:
        SkinnableObjectHub();
        virtual ~SkinnableObjectHub();

        void init ( ) ;
		void update ( ) ; 
		void draw ( ) ; 
        void loadFromXml( string xmlPath ) ;
		void loadFromXml( ) ;
        void saveToXml( ) ;
        void mousePressed ( ofMouseEventArgs& data ) ;
        void mouseDragged ( ofMouseEventArgs& data ) ;
        void mouseReleased ( ofMouseEventArgs& data ) ;
        void mouseMoved ( ofMouseEventArgs& data ) ;


        void addNewSkinnable( SkinnableData * data , int type ) ;
        void loadBackgroundImage( string path = "" ) ; 
		SkinnableData * createDefaultSkinnableData ( ) ;
        SkinnableData * getDataByName( string name ) ;
        SkinnableData * getDataByIndex( int index ) ;
        void updateDataByName ( SkinnableData * s ) ;
		SkinnableObject * getSelected() ; 

		ofImage backgroundImage ; 
		float underlayAlpha ; 
		float overlayAlpha ; 

		vector< SkinnableObject* > objects ;

        ofxXmlSettings sceneXml ;

        int selectedIndex ;

protected : 
		string backgroundImagePath ; 

};

#endif // SKINNABLEOBJECTHUB_H
