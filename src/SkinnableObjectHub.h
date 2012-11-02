#ifndef SKINNABLEOBJECTHUB_H
#define SKINNABLEOBJECTHUB_H

#include "SkinnableObject.h"
#include "SkinnableData.h"
#include "ofxXmlSettings.h"
#include "ofxPolygonHitTest.h"

class SkinnableObjectHub
{
    public:
        SkinnableObjectHub();
        virtual ~SkinnableObjectHub();

        static SkinnableObjectHub* Instance()
        {
            static SkinnableObjectHub inst ;
            return &inst ;
        }

        void init ( ) ;
        void loadFromXml( string xmlPath ) ;
        void saveToXml( ) ;
        void mousePressed ( ofMouseEventArgs& data ) ;
        void mouseDragged ( ofMouseEventArgs& data ) ;
        void mouseReleased ( ofMouseEventArgs& data ) ;
        void mouseMoved ( ofMouseEventArgs& data ) ;

        void addNewSkinnableData ( SkinnableData data ) ;
        SkinnableData createDefaultSkinnableData ( ) ;
        SkinnableData getDataByName( string name ) ;
        SkinnableData getDataByIndex( int index ) ;
        void updateDataByName ( SkinnableData s ) ;

        string defaultImagePath ;
        ofImage defaultImage ;

        vector<SkinnableData> data ;

        ofxXmlSettings sceneXml ;
        string sceneXmlPath ;

        int selectedIndex ;

        ofEvent<string> ACTIVATE_SKINNABLE_OBJECT ;
        ofEvent<string> DEACTIVATE_SKINNABLE_OBJECT ;
        ofEvent<SkinnableData> HUB_UPDATE_OBJECT ;

    protected:
    private:
};

#endif // SKINNABLEOBJECTHUB_H
