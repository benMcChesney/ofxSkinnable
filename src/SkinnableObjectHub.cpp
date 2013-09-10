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

    ofAddListener(ofEvents().mouseReleased, this, &SkinnableObjectHub::mouseReleased );
    ofAddListener(ofEvents().mousePressed, this, &SkinnableObjectHub::mousePressed );
    ofAddListener(ofEvents().mouseMoved, this, &SkinnableObjectHub::mouseMoved );
    ofAddListener(ofEvents().mouseDragged, this, &SkinnableObjectHub::mouseDragged );

    selectedIndex = -2 ;
}


void SkinnableObjectHub::update ( ) 
{
	if ( objects.size() > 0 ) 
	{
		for ( int i = 0 ; i < objects.size() ; i++ ) 
		{
			objects[ i ]->update() ; 
		}
	}
}

void SkinnableObjectHub::draw ( ) 
{
	ofSetColor( 255 , underlayAlpha ) ; 
	if ( backgroundImage.bAllocated() ) 
		backgroundImage.draw( 0 , 0 ) ; 

	ofSetColor( 255 ) ; 
	if ( objects.size() > 0 ) 
	{
		for ( int i = 0 ; i < objects.size() ; i++ ) 
		{
			objects[ i ]->draw() ; 
		}
	}

	ofSetColor( 255 , overlayAlpha ) ; 
	if ( backgroundImage.bAllocated() ) 
		backgroundImage.draw( 0 , 0 ) ; 
}


void SkinnableObjectHub::loadFromXml( ) 
{

	//Open the Open File Dialog
	ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png"); 
		
	//Check if the user opened a file
	if (openFileResult.bSuccess){
			
		ofLogVerbose("User selected a file@" + openFileResult.getPath() );
		loadFromXml( openFileResult.getPath() ) ; 
			
	}else {
		ofLogVerbose("User hit cancel");
	}
}

void SkinnableObjectHub::loadFromXml( string xmlPath )
{
    cout << "loading " << xmlPath << endl ;
    bool bResult = sceneXml.loadFile( xmlPath ) ;
    cout << "result of loading file : " << bResult << endl ;
    int numObjects = sceneXml.getNumTags( "sceneObject" ) ;
    cout << "num of sceneObjects : " << numObjects << endl ;
    objects.clear( ) ;

	backgroundImagePath = sceneXml.getValue( "BG_Image_path" , "none" ) ; 
	if ( backgroundImagePath != "none" ) 
	{
		backgroundImage.loadImage( backgroundImagePath ) ; 
	}

	cout << "Background Image Path " << backgroundImagePath << endl ; 
    for ( int i = 0 ; i < numObjects ; i++ )
    {
        sceneXml.pushTag( "sceneObject" , i ) ;
            SkinnableData * s = createDefaultSkinnableData() ;
            s->loadDataFromXml( &sceneXml ) ;
			/*
			 datum->index = objects.size() ; */
			int prevIndex = objects.size() ; 
			addNewSkinnable( s , s->type ) ;
			int nowIndex = objects.size() ; 

			if ( nowIndex > prevIndex ) 
			{
				cout << "successfully added an item." << endl ; 
				objects[ nowIndex -1 ]->loadDataFromXml( &sceneXml ) ;
			}

        sceneXml.popTag( ) ;
    }
}

void SkinnableObjectHub::loadBackgroundImage( string path ) 
{
	cout << "load BG Image " << endl ; 
	//if ( path != "" ) 
	//{
		//Open the Open File Dialog
		ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png"); 
		
		//Check if the user opened a file
		if (openFileResult.bSuccess)
		{
			ofLogVerbose("User selected a file@" + openFileResult.getPath() );
			backgroundImagePath = openFileResult.getPath() ; 
			backgroundImage.loadImage( backgroundImagePath ) ; 
			
		}
		else
		{
			ofLogVerbose("User hit cancel");
		}
	//}
}

void SkinnableObjectHub::saveToXml( )
{
	string xmlPath ; 
	ofFileDialogResult saveFileResult = ofSystemSaveDialog(".xml", "Save your file");
	if (saveFileResult.bSuccess)
	{
		string path = saveFileResult.filePath ; 
		int index = path.find( ".xml" ) ; 
		if ( index < 0 ) 
		{
			cout << "no .xml ! perfecto "<< endl ; 
			xmlPath = path ; 
		}
		else
		{
			xmlPath = path.substr( 0 , index ) ; 
		}

		cout << "xmlPath : " << xmlPath << endl ; 
		
		//sceneXmlPath = path ;
	}
	else
	{
		ofLogVerbose( "user cancelled saving action" ) ; 
		return ; 
	}

	//First Export 1080p
	sceneXml.clear( ) ;

	sceneXml.setValue( "BG_Image_path" , backgroundImagePath ) ; 
    for ( int i = 0 ; i < objects.size() ; i++ )
    {
        int tagNum = sceneXml.addTag( "sceneObject" ) ;
        sceneXml.pushTag( "sceneObject" , tagNum ) ;
			objects[i]->writeDataToXml( &sceneXml ,1.0f ) ; 
        sceneXml.popTag( ) ;
    }


    sceneXml.saveFile( xmlPath + "1080p.xml" ) ;

	//Now Export 4K
	sceneXml.clear( ) ;

	sceneXml.setValue( "BG_Image_path" , backgroundImagePath ) ; 
    for ( int i = 0 ; i < objects.size() ; i++ )
    {
        int tagNum = sceneXml.addTag( "sceneObject" ) ;
        sceneXml.pushTag( "sceneObject" , tagNum ) ;
			objects[i]->writeDataToXml( &sceneXml , 2.0f ) ; 
        sceneXml.popTag( ) ;
    }


    sceneXml.saveFile( xmlPath + "4k.xml" ) ;

}
void SkinnableObjectHub::addNewSkinnable ( SkinnableData * datum , int type )
{

    for ( int i = 0 ; i < objects.size() ; i++ )
    {
        if ( datum->name == objects[i]->data.name )
        {
            cout << "ERROR!! attempting to add in duplicate '" << datum->name << "'" << endl ;
            cout << "Not adding it as each name NEEDS to be unique." << endl ;
        }
        datum->index = objects.size() ;

    }

	SkinnableObject * object = NULL ; 
	if ( type == 0 ) 
	{
		object = new SkinnableObject() ; 
		datum->type = 0 ; 
	}

	if ( type == 1 ) 
	{
		object = new SkinnableTextBlock( ) ; 
		datum->type = 1 ; 
	}
	
	if ( type == 2 ) 
	{

	}
	
	if ( object != NULL ) 
	{
		object->setup( (*datum) ) ; 
		objects.push_back ( object ) ; 
	}
}

SkinnableData * SkinnableObjectHub::createDefaultSkinnableData ( )
{
    SkinnableData * skinData ;
	skinData = new SkinnableData( ) ; 
    skinData->width = ofRandom ( 100, 200 ) ; 
	skinData->height =	 ofRandom( 100 , 200 ) ; 
	skinData->x = ofGetWidth() / 2 ; 
	skinData->y = ofGetHeight() / 2 ; 
    cout << "index being set to : " << objects.size() << endl ;

    skinData->index = objects.size() ;
    return skinData ;
}
SkinnableData * SkinnableObjectHub::getDataByIndex( int index )
{
    if( objects.size() < 1 )
    {
        cout << "NO SKINNABLE ITEMS LOADED" << endl ;
    }
    else
    {
        if ( index < objects.size() )
            return &objects[index]->data ;
    }
}

SkinnableObject * SkinnableObjectHub::getSelected() 
{
	for ( int i = 0 ; i < objects.size() ; i++ )
    {
        if ( objects[i]->bSelected == true )
		{
			return objects[ i ] ; 
        }
    }

	return NULL ; 
}

SkinnableData * SkinnableObjectHub::getDataByName( string name )
{
    if( objects.size() < 1 )
    {
        cout << "NO SKINNABLE ITEMS LOADED" << endl ;
    }
    else
    {
        for ( int i = 0 ; i < objects.size() ; i++ )
        {
            if ( name == objects[i]->data.name )
            {
                return &objects[i]->data ;
            }
        }
    }

    cout << "getDataByName() NO MATCH WAS FOUND for"<< name << endl ;
    return new SkinnableData( ) ;
}

void SkinnableObjectHub::updateDataByName ( SkinnableData * s )
{
    if( objects.size() < 1 )
    {
        cout << "NO SKINNABLE ITEMS LOADED" << endl ;
    }
    else
    {
        string name = s->name ;
        if ( name == "" || name == "noName" )
        {
            cout << "attempting to update a data with DEFAULT name" << endl ;
            return ;
        }


        for ( int i = 0 ; i < objects.size() ; i++ )
        {
            if ( name == objects[i]->data.name )
            {
                objects[i]->data = (*s) ;
                return ;
            }
        }
    }
    cout << "updateDataByName() NO MATCH WAS FOUND " << s->name << endl ;
}


void SkinnableObjectHub::mousePressed ( ofMouseEventArgs& mouseData )
{
    //cout << "mouseData .button " <<  mouseData.button << endl ;
    if ( mouseData.button == 2 )
    {
        for ( int i = 0 ; i < objects.size() ; i++ )
        {

			//if (  ofxPolygonHitTest::Instance()->pointInPoly( objects[i]->data.generateBoundPoints() , mouseData.x , mouseData.y ) == true )
			if ( objects[ i ]->checkHitTest( mouseData.x , mouseData.y )  == true )  
			{
                cout << "HIT !" << endl ;
                string args = objects[i]->data.name ;
                cout << "data NAME: " << args << endl ;
                ofNotifyEvent( ofxSkinnableEvents::Instance()->ACTIVATE_SKINNABLE_OBJECT , args ) ;
                //Deactivate old , currently limit it to 1 active perl
                if ( selectedIndex >= 0 && selectedIndex != i )
                {
                    string args = objects[ selectedIndex ]->data.name ;
                    ofNotifyEvent( ofxSkinnableEvents::Instance()->DEACTIVATE_SKINNABLE_OBJECT , args ) ;
                }
                selectedIndex = i ;
                return ;
            }
        }

        if ( selectedIndex >= 0 )
        {
            string args = objects[selectedIndex]->data.name ;
            ofNotifyEvent( ofxSkinnableEvents::Instance()->DEACTIVATE_SKINNABLE_OBJECT , args ) ;
        }

        selectedIndex = -2 ;
        //cout << "nothing found !" << endl ;
    }
}

void SkinnableObjectHub::mouseDragged ( ofMouseEventArgs& mouseData )
{

}


void SkinnableObjectHub::mouseReleased ( ofMouseEventArgs& mouseData )
{

}

void SkinnableObjectHub::mouseMoved ( ofMouseEventArgs& mouseData )
{


}


