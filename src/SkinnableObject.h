#pragma once

#include "ofMain.h"
#include "BasePolyObject.h"
#include "SkinnableObjectHub.h"
#include "AlphaStackItem.h"
#include "SkinnableData.h"

class SkinnableObject : public BasePolyObject , public AlphaStackItem
{
    public:
        SkinnableObject();
        virtual ~SkinnableObject();

        //If you already have the data you need
        void setup ( SkinnableData _data ) ;
        //If you need to load the data from the hub
        void setup ( string _name ) ;

        void draw ( )  ;
        void update ( ) ;

        void updateSyncData ( ) ;
        void loadImage ( string path , bool addPoints = true ) ;
        void addRectPoints ( ) ;
        void updatePivot ( float _x , float _y , bool bUpdateRect = true ) ;

        SkinnableData getData( ) ;
        ofImage image ;

        float x , y ;
        float rotation ;
        int index ;

        float originalHeight ;
        float originalWidth ;

        float width ;
        float height ;

        string imagePath ;
        ofPoint anchorPoint ;

        string name ;

        void activateEventHandler ( string &args ) ;
        void deactivateEventHandler( string &args ) ;
        void hubUpdateHandler ( SkinnableData &args ) ;
        void setData ( SkinnableData skinData ) ;

        bool bSelected ;

    protected:
      //  SkinnableData data ;

    private:
};

