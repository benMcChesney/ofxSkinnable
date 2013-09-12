#include "SkinnableObject.h"

SkinnableObject::SkinnableObject()
{
    data.index = ofRandom ( -4 , -10 ) ;
	rotation = 0.0f ; 
	
}

SkinnableObject::~SkinnableObject()
{
    //dtor
}

 void SkinnableObject::setup ( SkinnableData _data )
 {
     cout << "SkinnableObject :: setup " << endl ;
    data = _data ; 
    bSelected = false ;
    ofAddListener( ofxSkinnableEvents::Instance()->ACTIVATE_SKINNABLE_OBJECT , this , &SkinnableObject::activateEventHandler ) ;
    ofAddListener( ofxSkinnableEvents::Instance()->DEACTIVATE_SKINNABLE_OBJECT , this , &SkinnableObject::deactivateEventHandler ) ;
    ofAddListener( ofxSkinnableEvents::Instance()->HUB_UPDATE_OBJECT , this , &SkinnableObject::hubUpdateHandler ) ;
 }

 void SkinnableObject::setup ( )
 {
	//Not much !

 }


void SkinnableObject::activateEventHandler ( string &args )
{
	stringstream ss ; 
    ss << "Is ( objectIndex ) " << data.index << " == ( event index )" << args << " ? " << endl ;
    ss << "args : " << args << "name : " << data.name << endl ;

    if ( data.name == args )
    {
        ss << "ACTIVATE!" << endl ;
        ss << "NAME : " << data.name << " should be activating! " << endl ;
		ofLog( OF_LOG_VERBOSE , ss.str() ); 
        bSelected = true ;
    }
}

void SkinnableObject::deactivateEventHandler( string &args )
{
   // cout << "DEACTIVATE!" << endl ;
    if ( data.name == args )
    {
		stringstream ss ; 
        ss << "DEACTIVATE!" << endl ;
        ss << "NAME : " << data.name << " should be activating! " << endl ;
		ofLog( OF_LOG_VERBOSE , ss.str() ); 
        bSelected = false ;
    }
}


void SkinnableObject::hubUpdateHandler ( SkinnableData &args )
{
    if ( args.name.compare( data.name ) == 0 )
    {
       // cout << "hubUpdateHandler!!" << endl ;
		//cout << "args .data .x : " << args.x << " , y : " << args.y << endl ; 
		data = args ; 
    }
}

 void SkinnableObject::draw ( )
 {
    ofPushMatrix( ) ;
	ofPushStyle() ; 
		ofTranslate( data.x , data.y ) ; 
        ofRotateZ( rotation ) ;
		ofSetColor( 128 , 180 ) ; 
		
		ofSetLineWidth( 3 ) ; 
		

        if ( bSelected == true )
        {
            ofSetColor ( 0 , 255 , 0  , 180 ) ;

        }

		
		ofSetLineWidth ( 5 ) ; 
		ofNoFill( ) ; 
		float padding = 10  ;
		
        ofRect( -padding , -padding , data.width + padding * 2 , data.height + padding * 2 ) ;
		ofFill() ; 
    ofPopMatrix( ) ;

	if ( bSelected == true ) 
	{
		ofSetColor( 0 , 255 , 255 , 180 ) ; 
		ofNoFill() ;
		ofCircle( data.anchorX , data.anchorY , 10 ) ; 
		ofFill( ) ; 
	}
	else
	{
		ofSetColor( 0 , 255 , 255 , 180 ) ; 
		ofFill() ; 
		ofCircle( data.anchorX , data.anchorY , 10 ) ; 
	}

	ofPopStyle( ) ; 
    //baseDraw( ) ;
 }

 void SkinnableObject::update ( )
 {

 }

void SkinnableObject::writeDataToXml( ofxXmlSettings *xml , float scale )
{
	data.writeDataToXml( xml , scale ) ; 
}

void SkinnableObject::loadDataFromXml( ofxXmlSettings * xml ) 
{
	data.loadDataFromXml( xml ) ; 
}

bool SkinnableObject::checkHitTest( float x , float y ) 
{
	bool xCheck = ( x >= data.x ) && ( x <= ( data.x + data.width )) ; 
	bool yCheck = ( y >= data.y ) && ( y <= ( data.y + data.height )) ;

	//cout << "( " << x << " , " << y << " ) : " << data.x << " , " << data.y << " , " << data.width << " , " << data.height << endl ;  
	
	if ( xCheck == true && yCheck == true ) 
	{
		return true ; 
	}

	return false ; 
}