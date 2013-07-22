#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    SkinnableObjectHub::Instance()->init( ) ;
}

//--------------------------------------------------------------
void testApp::update(){

    if ( objects.size() > 0 )
    {
      for ( int i = 0 ; i < objects.size() ; i++ )
      {
          objects[i]->update ( ) ;
      }
    }

}

//--------------------------------------------------------------
void testApp::draw(){
     if ( objects.size() > 0 )
    {
    for ( int i = 0 ; i < objects.size() ; i++ )
    {
        objects[i]->draw( ) ;
    }
    }
}

void testApp::createNewSkinnableObject( )
{
    SkinnableData data = SkinnableObjectHub::Instance()->createDefaultSkinnableData( ) ;
    data.name = "test"+ofToString( objects.size() ) ;

    SkinnableObject * obj = new SkinnableObject( ) ;
    obj->setup( data ) ;
    SkinnableObjectHub::Instance()->addNewSkinnableData( data ) ;

    //objects[ curNumObjects ] = obj ;
    //curNumObjects++ ;

    objects.push_back( obj ) ;

}


void testApp::populateSkinnableObjects( )
{
    vector<SkinnableData> skinData = SkinnableObjectHub::Instance()->data ;
 //   curNumObjects = 0 ;
    objects.clear ( ) ;
    for ( int i = 0 ; i < skinData.size()  ; i++ )
    {
        cout << "skinData : " << i << endl ;
        //SkinnableData data = skinData[i] ;
        SkinnableObject * obj = new SkinnableObject( ) ;
        obj->setup( skinData[i] ) ;
        objects.push_back ( obj ) ;
       // objects[ curNumObjects ] = obj ;
       // curNumObjects++ ;
        //SkinnableObjectHub::Instance()->updateDataByName( data ) ;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch ( key )
    {
        case 'n':
        case 'N':
            createNewSkinnableObject() ;
            break ;

        case 'l':
        case 'L':
            cout << "loading from XML!" << endl ;
            SkinnableObjectHub::Instance()->loadFromXml(  SkinnableObjectHub::Instance()->sceneXmlPath ) ;
            populateSkinnableObjects() ;
            break ;

        case 's':
        case 'S':
            SkinnableObjectHub::Instance()->saveToXml() ;
            break ;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
