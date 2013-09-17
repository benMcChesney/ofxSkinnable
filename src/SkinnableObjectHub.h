#ifndef SKINNABLEOBJECTHUB_H
#define SKINNABLEOBJECTHUB_H

#include "SkinnableObject.h"
#include "SkinnableData.h"
#include "SkinnableTextBlock.h"
#include "SkinnableImage.h"
#include "SkinnableImageData.h"
#include "ofxXmlSettings.h"

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


        bool addNewSkinnableObject( SkinnableData * data , int type ) ;
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
		void setSelected( int _index ) ; 
		bool isValidObjectIndex( int index ) ; 

protected : 
		string backgroundImagePath ; 

};

#endif // SKINNABLEOBJECTHUB_H
