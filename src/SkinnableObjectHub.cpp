#include "SkinnableObjectHub.h"

SkinnableObjectHub::SkinnableObjectHub()
{
    //ctor
}

SkinnableObjectHub::~SkinnableObjectHub()
{
    //dtor
}

void SkinnableObjectHub::init ( )
{
    //activeObject = NULL ;
    defaultImagePath = "ofxSkinnable/defaultImage.png" ;
    defaultImage.loadImage( defaultImagePath ) ;
    sceneXmlPath = "ofxSkinnable/defaultScene.xml" ;

    ofAddListener(ofEvents().mouseReleased, this, &SkinnableObjectHub::mouseReleased );
    ofAddListener(ofEvents().mousePressed, this, &SkinnableObjectHub::mousePressed );
    ofAddListener(ofEvents().mouseMoved, this, &SkinnableObjectHub::mouseMoved );
    ofAddListener(ofEvents().mouseDragged, this, &SkinnableObjectHub::mouseDragged );

    //curIndex = 0 ;
   // maxObjects = 200  ;
   // data = new SkinnableData[ maxObjects ] ;
    selectedIndex = -2 ;
}

void SkinnableObjectHub::loadFromXml( string xmlPath )
{
    cout << "loading " << xmlPath << endl ;
    sceneXmlPath = xmlPath ;
    bool bResult = sceneXml.loadFile( xmlPath ) ;
    cout << "result of loading file : " << bResult << endl ;
    int numObjects = sceneXml.getNumTags( "sceneObject" ) ;
    cout << "num of sceneObjects : " << numObjects << endl ;
    data.clear( ) ;
  //  curIndex = 0 ;
    for ( int i = 0 ; i < numObjects ; i++ )
    {
        sceneXml.pushTag( "sceneObject" , i ) ;
            SkinnableData s = createDefaultSkinnableData() ;
            s.loadDataFromXml( &sceneXml ) ;
            addNewSkinnableData( s ) ;
        sceneXml.popTag( ) ;
    }
}

void SkinnableObjectHub::saveToXml( )
{
    sceneXml.clear( ) ;

    //cout << "data.size() :" << data.size() << endl ;
    for ( int i = 0 ; i < data.size() ; i++ )
    {
        int tagNum = sceneXml.addTag( "sceneObject" ) ;
        sceneXml.pushTag( "sceneObject" , tagNum ) ;
            SkinnableData s = data[i] ;
            s.writeDataToXml( &sceneXml ) ;
        sceneXml.popTag( ) ;
    }

    cout << "saved to XML : " << sceneXmlPath <<  endl ;
    sceneXml.saveFile( sceneXmlPath ) ;

}

void SkinnableObjectHub::mousePressed ( ofMouseEventArgs& mouseData )
{
    cout << "mouseData .button " <<  mouseData.button << endl ;
    if ( mouseData.button == 0 )
    {
        for ( int i = 0 ; i < data.size() ; i++ )
        {
            if (  ofxPolygonHitTest::Instance()->pointInPoly( data[i].pts , mouseData.x , mouseData.y ) == true )
            {
                cout << "HIT !" << endl ;
                string args = data[i].name ;
                cout << "data NAME: " << args << endl ;
                ofNotifyEvent( SkinnableObjectHub::Instance()->ACTIVATE_SKINNABLE_OBJECT , args ) ;
                //Deactivate old , currently limit it to 1 active perl
                if ( selectedIndex >= 0 && selectedIndex != i )
                {
                    string args = data[selectedIndex].name ;
                    ofNotifyEvent( SkinnableObjectHub::Instance()->DEACTIVATE_SKINNABLE_OBJECT , args ) ;
                }
                selectedIndex = i ;
                return ;
            }
        }

        if ( selectedIndex >= 0 )
        {
            string args = data[selectedIndex].name ;
            ofNotifyEvent( SkinnableObjectHub::Instance()->DEACTIVATE_SKINNABLE_OBJECT , args ) ;
        }

        selectedIndex = -2 ;
        //cout << "nothing found !" << endl ;
    }
    if ( mouseData.button == 2 )
    {
        cout << "mouse is definately 2! data.size() " << data.size( ) <<  endl ;
        for ( int d = 0 ; d < data.size() ; d++ )
        {
            if (  ofxPolygonHitTest::Instance()->pointInPoly( data[d].pts , mouseData.x , mouseData.y ) == true )
            {
                cout << "hit something!" << endl ;
                ofFileDialogResult result = ofSystemLoadDialog( "Pick your new image skin" ) ;
                cout << "after the ofFileDialogueResult" << endl ;
                if ( result.bSuccess == true )
                {
                    string path = result.getPath( ) ;
                    SkinnableData skinData = data[ d ] ;
                    cout << "path was : " << skinData.imagePath << " , now : " << path << endl ;
                    skinData.imagePath = path ;
                    ofNotifyEvent( SkinnableObjectHub::Instance()->HUB_UPDATE_OBJECT , skinData ) ;
                }
            }
        }
    }
}

void SkinnableObjectHub::mouseDragged ( ofMouseEventArgs& mouseData )
{
    if ( selectedIndex >= 0 )
    {
        SkinnableData skinData = getDataByIndex( selectedIndex ) ;
        skinData.x = mouseData.x ;
        skinData.y = mouseData.y ;
        skinData.pivot.x = mouseData.x ;
        skinData.pivot.y = mouseData.y ;
        ofNotifyEvent( SkinnableObjectHub::Instance()->HUB_UPDATE_OBJECT , skinData ) ;
    }
}


void SkinnableObjectHub::mouseReleased ( ofMouseEventArgs& mouseData )
{

}

void SkinnableObjectHub::mouseMoved ( ofMouseEventArgs& mouseData )
{


}

void SkinnableObjectHub::addNewSkinnableData ( SkinnableData datum )
{

    for ( int i = 0 ; i < data.size() ; i++ )
    {
        if ( datum.name == data[i].name )
        {
            cout << "ERROR!! attempting to add in duplicate '" << datum.name << "'" << endl ;
            cout << "Not adding it as each name NEEDS to be unique." << endl ;
        }
        datum.index = data.size() ;

    }
    cout << "adding a new DATA" << endl ;
    data.push_back( datum ) ;
}

SkinnableData SkinnableObjectHub::createDefaultSkinnableData ( )
{
    SkinnableData skinData ;
    skinData.imagePath = defaultImagePath ;
    skinData.width = defaultImage.width ;
    skinData.height = defaultImage.height ;
    skinData.originalWidth = defaultImage.width ;
    skinData.originalHeight = defaultImage.height ;
    cout << "index being set to : " << data.size() << endl ;
    skinData.index = data.size() ;
    return skinData ;
}
SkinnableData SkinnableObjectHub::getDataByIndex( int index )
{
    if( data.size() < 1 )
    {
        cout << "NO SKINNABLE ITEMS LOADED" << endl ;
    }
    else
    {
        if ( index < data.size() )
            return data[index] ;
    }
}

SkinnableData SkinnableObjectHub::getDataByName( string name )
{
    if( data.size() < 1 )
    {
        cout << "NO SKINNABLE ITEMS LOADED" << endl ;
    }
    else
    {
        for ( int i = 0 ; i < data.size() ; i++ )
        {
            if ( name == data[i].name )
            {
                return data[i] ;
            }
        }
    }

    cout << "getDataByName() NO MATCH WAS FOUND for"<< name << endl ;
    return SkinnableData( ) ;
}

void SkinnableObjectHub::updateDataByName ( SkinnableData s )
{
     if( data.size() < 1 )
    {
        cout << "NO SKINNABLE ITEMS LOADED" << endl ;
    }
    else
    {
        string name = s.name ;
        if ( name == "" || name == "noName" )
        {
            cout << "attempting to update a data with DEFAULT name" << endl ;
            return ;
        }


        for ( int i = 0 ; i < data.size() ; i++ )
        {
            if ( name == data[i].name )
            {
                data[i] = s ;
                return ;
            }
        }
    }
    cout << "updateDataByName() NO MATCH WAS FOUND " << s.name << endl ;
}

