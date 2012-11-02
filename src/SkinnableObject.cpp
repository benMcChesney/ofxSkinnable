#include "SkinnableObject.h"

SkinnableObject::SkinnableObject()
{
    index = ofRandom ( -4 , -10 ) ;
}

SkinnableObject::~SkinnableObject()
{
    //dtor
}

 void SkinnableObject::setup ( SkinnableData data )
 {
     cout << "SkinnableObject :: setup " << endl ;
    setData( data ) ;
    bSelected = false ;
    loadImage( imagePath ) ;
    cout << "name is : " << name << endl ;
    ofAddListener( SkinnableObjectHub::Instance()->ACTIVATE_SKINNABLE_OBJECT , this , &SkinnableObject::activateEventHandler ) ;
    ofAddListener( SkinnableObjectHub::Instance()->DEACTIVATE_SKINNABLE_OBJECT , this , &SkinnableObject::deactivateEventHandler ) ;
    ofAddListener( SkinnableObjectHub::Instance()->HUB_UPDATE_OBJECT , this , &SkinnableObject::hubUpdateHandler ) ;
 }

 void SkinnableObject::setData ( SkinnableData skinData )
 {
    x = skinData.x ;
    y = skinData.y ;
    pivot.x = x ;
    pivot.y = y ;

    rotation = skinData.rotation ;

    originalHeight = skinData.originalHeight ;
    originalWidth = skinData.originalWidth ;

    width = skinData.width ;
    height = skinData.height ;
    imagePath = skinData.imagePath ;
    anchorPoint = skinData.anchorPoint ;
    name = skinData.name ;
    index = skinData.index ;
    cout << "index is now!: " << index << endl ;
 }

 void SkinnableObject::setup ( string _name )
 {
    setup ( SkinnableObjectHub::Instance()->getDataByName( _name ) ) ;
 }

void SkinnableObject::addRectPoints ( )
{
    pts.clear( ) ;
    addPoint( 0 , 0 ) ;
    addPoint( image.width , 0 ) ;
    addPoint( image.width , image.height ) ;
    addPoint( 0 , image.height) ;
}

void SkinnableObject::activateEventHandler ( string &args )
{
    cout << "Is ( objectIndex ) " << index << " == ( event index )" << args << " ? " << endl ;
    cout << "args : " << args << "name : " << name << endl ;

    if ( name == args )
    {
        cout << "ACTIVATE!" << endl ;
        cout << "NAME : " << name << " should be activating! " << endl ;
        bSelected = true ;
    }
}

void SkinnableObject::deactivateEventHandler( string &args )
{
   // cout << "DEACTIVATE!" << endl ;
    if ( name == args )
    {
        cout << "DEACTIVATE!" << endl ;
        cout << "NAME : " << name << " should be activating! " << endl ;
        bSelected = false ;
    }
}


void SkinnableObject::hubUpdateHandler ( SkinnableData &args )
{
    if ( args.name == name )
    {
        cout << "hubUpdateHandler!!" << endl ;
        bool newImage = ( args.imagePath == imagePath ) ;

        if ( newImage == true )
        {
            cout << "new image path! " << args.imagePath << endl ;
            loadImage( args.imagePath ) ;
        }
        setData( args ) ;
        updatePivot( args.x , args.y , true ) ;
    }
   // if ( strcmp( (args.name).c_str() , name.c_str() ) == 1 )
   // {
   //     setData ( args ) ;
   // }
}

void SkinnableObject::updatePivot ( float _x , float _y , bool bUpdateRect )
{
    x = _x ;
    y = _y ;
    pivot.x = x ;
    pivot.y = y ;
    if ( bUpdateRect == true )
        addRectPoints( ) ;
}


 void SkinnableObject::draw ( )
 {
    ofPushMatrix( ) ;


        ofTranslate( pivot.x , pivot.y , 0 ) ;

        ofRotateZ( rotation ) ;
        if ( bSelected == true )
        {
            ofSetColor ( 0 , 255 , 0 ) ;
            float padding = 10  ;
            ofRect( -padding , -padding , width + padding * 2 , height + padding * 2 ) ;
        }
         ofSetColor( 255 , 255 , 255 ) ;
        image.draw( 0 ,0 , width , height ) ;
    ofPopMatrix( ) ;

    //baseDraw( ) ;
 }

 void SkinnableObject::update ( )
 {
    SkinnableObjectHub::Instance()->updateDataByName( getData() ) ;
 }

 void SkinnableObject::updateSyncData( )
 {
    //SkinnableObjectHub::Instance()->updateDataByName( getData() ) ;
 }

void SkinnableObject::loadImage( string path , bool addPoints )
{
    imagePath = path ;
    bool bResult = image.loadImage( imagePath ) ;

    if ( bResult == true && addPoints == true )
    {
        //cout << "points WERE added !" << endl ;
        addRectPoints( ) ;
        //outputPtsToConsole( ) ;
    }
    else
    {
        //cout << "points were not added!" << endl ;
    }

    updateSyncData( ) ;
}

SkinnableData SkinnableObject::getData( )
{
    SkinnableData data ;
    data.x = x ;
    data.y = y ;
    data.pivot.x = pivot.x ;
    data.pivot.y = pivot.y ;
    data.rotation = rotation ;

    data.originalHeight = originalHeight ;
    data.originalWidth = originalWidth ;

    data.width = width ;
    data.height = height ;
    data.imagePath = imagePath ;
    data.anchorPoint = anchorPoint ;
    data.pts = pts ;
    data.name = name ;
   // cout << "index : " << index << endl ;
    data.index = index ;

    //cout <<" name : " << name << endl ;

    return data ;

}
