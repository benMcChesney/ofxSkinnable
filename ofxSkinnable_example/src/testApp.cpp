#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	hub.init( ) ;

	inputString= "JUST TYPE TO CHANGE THIS TEXT, [BACKSPACE] will delete one character" ; 

	ofDirectory dir ; 
	string dirName = "type/" ; 
	dir.listDir( dirName ) ; 
	cout << dir.size() << endl ; 

	for ( int i = 0 ; i < dir.size() ; i++ ) 
	{
		fontPaths.push_back( dirName + dir.getName( i ) ) ; 
	}

	if ( dir.size() == 0 ) 
		fontPaths.push_back( "NO FONTS LOADED" ) ; 
	

	newObjectType.push_back( "core image" ) ; 
	newObjectType.push_back( "text block" ) ; 
	newObjectType.push_back( "icon" ) ; 

	drawAlignments.push_back( "DRAW RIGHT" ) ; 
	drawAlignments.push_back( "DRAW CENTER" ) ; 
	drawAlignments.push_back( "DRAW LEFT" ) ; 

	setupGui( ) ; 
}

//--------------------------------------------------------------
void testApp::update(){
	 
	hub.update( ) ; 

	SkinnableObject * obj = hub.getSelected() ; 
	if ( lastSelectedIndex != hub.selectedIndex && hub.selectedIndex >= 0 ) 
	{
		if ( obj != NULL ) 
		{
			editData = obj->data ; 
			if ( obj->data.type == 1 )
			{
				 editTextData = ((SkinnableTextBlock*) obj)->textData ; 
				 inputString = editTextData.blockText ; 
			}
		}
	}
	else
	{
		
		if ( obj != NULL )
		{
			SkinnableData skinData = editData ; 
			skinData.name = obj->data.name ;
			skinData.type = obj->data.type  ;
			obj->data = skinData ; 
			editTextData.blockText = inputString ; 
		
			if ( obj->data.type  == 1 )
			{
				if ( editTextData.fontPath == "none" ) 
					editTextData.fontPath = fontPaths[ fontIndex ] ; 
				((SkinnableTextBlock*) obj)->textData = editTextData ; 
				((SkinnableTextBlock*) obj)->applyTextData() ; 
			}
		}
	}
	lastSelectedIndex = hub.selectedIndex ; 
}

//--------------------------------------------------------------
void testApp::draw(){

	hub.draw( ) ; 
	
	ofDrawBitmapStringHighlight( "TEXT : " + inputString , 15 , ofGetHeight() - 50 ) ; 

}

void testApp::setupGui( )
{
	fontIndex = 0 ;
	widgetTypeIndex = 0 ; 


	guiWidth = 250 ; 
	float sliderHeight = 15 ; 
	float sliderLength = 250 ; 

	 coreGui = new ofxUICanvas(0, 0 ,  guiWidth , ofGetHeight() );
	 coreGui->addLabel( "CORE GUI" ) ;
	 coreGui->addToggle( "SAVE UI SETTINGS" , false ) ; 
	 coreGui->addToggle( "LOAD UI SETTINGS" , false ) ; 
	 
	 coreGui->addToggle( "SAVE TO XML" , false ) ;
	 coreGui->addToggle( "LOAD FROM XML" , false  ) ;
	 coreGui->addToggle( "LOAD BG IMAGE" , false  ) ;

	 coreGui->addSlider( "X" , 0.0f , ofGetWidth() , &editData.x ) ; 
	 coreGui->addSlider( "Y" , 0.0f , ofGetHeight() , &editData.y ) ; 

	 coreGui->addSlider( "WIDTH" , 0.0f , ofGetWidth() , &editData.width ) ;
	 coreGui->addSlider( "HEIGHT" , 0.0f , ofGetWidth() , &editData.height ) ;
	
	 coreGui->addLabel( "NEW OBJECT TYPE " ) ; 
	 coreGui->addRadio( "NEW OBJECT TYPE", newObjectType , OFX_UI_ORIENTATION_VERTICAL,  15 , 15 ); 
	
	 coreGui->addSlider( "UNDERLAY ALPHA", 0.0f , 255.0f , &hub.underlayAlpha ) ; 
	 coreGui->addSlider( "OVERLAY ALPHA", 0.0f , 255.0f , &hub.overlayAlpha ) ;
	 coreGui->addToggle( "CREATE NEW OBJECT" , false ) ; 

	 ofAddListener(coreGui->newGUIEvent,this,&testApp::coreGuiEventHandler );	

	 textBlockGui = new ofxUICanvas(0, 0 ,  guiWidth , ofGetHeight() );
	 textBlockGui->addLabel( "TEXT BLOCK GUI" ) ; 
	 textBlockGui->addToggle( "WRAP X" , &editTextData.bWrapX ) ; 
	 textBlockGui->addToggle( "WRAP BOX" , &editTextData.bWrapBox ) ;
	 textBlockGui->addSlider( "FONT SIZE" , 6.0f , 90.0f , &editTextData.fontSize ) ; 
	 textBlockGui->addSlider( "GRAYSCALE COLOR" , 0.0f , 255.0f ,  &editTextData.grayscaleColor ) ;
	 textBlockGui->addSlider( "LINE SPACING" , 0.9f , 3.0f , &editTextData.lineSpacing ) ; 
	 textBlockGui->addLabel( "FONT CHOICE " ) ;
	 textBlockGui->addSpacer( ) ; 
	 textBlockGui->addRadio("FONTS", fontPaths , OFX_UI_ORIENTATION_VERTICAL,  15 , 15 ); 
	 textBlockGui->addLabel( "TEXT BLOCK ALIGNMENTS" ) ; 
	 textBlockGui->addSpacer( ) ; 
	 textBlockGui->addRadio("ALIGNMENTS", drawAlignments , OFX_UI_ORIENTATION_VERTICAL,  15 , 15 ); 
	
	 ofAddListener(textBlockGui->newGUIEvent,this,&testApp::textBlockGuiEventHandler );	

	 iconGui = new ofxUICanvas(0, 0 ,  guiWidth , ofGetHeight() );
	 iconGui->addLabel( "ICON GUI" ) ;
	 ofAddListener(iconGui->newGUIEvent,this,&testApp::iconGuiEventHandler );	

	 loadAllGuis() ; 
	 disableAllGui() ; 
	 coreGui->toggleVisible() ; 
}

void testApp::disableAllGui()  
{
	coreGui->disable() ; 
	textBlockGui->disable( ) ; 
	iconGui->disable() ; 
}

void testApp::saveAllGuis() 
{
	coreGui->saveSettings( "GUI/coreGUI.xml" ) ; 
	textBlockGui->saveSettings( "GUI/textBlockGUI.xml" ) ; 
	iconGui->saveSettings( "GUI/iconGUI.xml") ; 
}

void testApp::loadAllGuis() 
{
	coreGui->loadSettings( "GUI/coreGUI.xml" ) ; 
	textBlockGui->loadSettings( "GUI/textBlockGUI.xml" ) ; 
	iconGui->loadSettings( "GUI/iconGUI.xml") ; 
}

void testApp::coreGuiEventHandler( ofxUIEventArgs &e )
{
	string name = e.widget->getName(); 
	
	if ( name == "SAVE UI SETTINGS" ) 
	{
		ofxUIToggle * toggle = ( ofxUIToggle * ) e.widget ;
		if ( toggle->getValue() == true ) 
		{
			toggle->setValue( false ) ; 
			saveAllGuis() ; 
		}
	}

	
	if ( name == "LOAD UI SETTINGS" ) 
	{
		ofxUIToggle * toggle = ( ofxUIToggle * ) e.widget ;
		if ( toggle->getValue() == true ) 
		{
			loadAllGuis() ; 
			((ofxUIToggle *)coreGui->getWidget( name ))->setValue( false ) ;
		}
	}

	if ( name == "SAVE TO XML" ) 
	{
		ofxUIToggle * toggle = ( ofxUIToggle * ) e.widget ;
		if ( toggle->getValue() == true ) 
		{
			 hub.saveToXml() ;
			 ((ofxUIToggle *)coreGui->getWidget( name ))->setValue( false ) ;
		}
	}
	if ( name == "LOAD FROM XML" ) 
	{
		ofxUIToggle * toggle = ( ofxUIToggle * ) e.widget ; 
		if ( toggle->getValue() == true ) 
		{
			hub.loadFromXml( ) ;
            populateSkinnableObjects() ;
			((ofxUIToggle *)coreGui->getWidget( name ))->setValue( false ) ;
		}
	}

	if ( name == "LOAD BG IMAGE" ) 
	{
		ofxUIToggle * toggle = ( ofxUIToggle * ) e.widget ; 
		if ( toggle->getValue() == true ) 
		{
			hub.loadBackgroundImage( ) ;
			((ofxUIToggle *)coreGui->getWidget( name ))->setValue( false ) ;
		}
	}
	
	for(int i = 0; i < newObjectType.size(); i++)
	{
		if ( name == newObjectType[i] ) 
		{
			ofxUIToggle * toggle = (ofxUIToggle *)coreGui->getWidget( name ) ; 
			if ( toggle->getValue() ) 
			{
				widgetTypeIndex = i ;
				cout << "SELECTED: " <<  newObjectType[i] << endl; 
				break ;
			}
		}		
	}

	if ( name == "CREATE NEW OBJECT" ) 
	{
		ofxUIToggle * toggle = ( ofxUIToggle * ) e.widget ;
		if ( toggle->getValue() == true ) 
		{
			toggle->setValue( false ) ; 
			createNewSkinnableObject() ; 
			//((ofxUIToggle *)coreGui->getWidget( name ))->setValue( false ) ;
		}
		
	}
	/*

	Not used anymore... 
	if ( name == "APPLY CHANGES" ) 
	{
		ofxUIToggle * toggle = ( ofxUIToggle * ) e.widget ; 
		if ( toggle->getValue() == true ) 
		{
			SkinnableObject * obj = hub.getSelected() ; 
			if ( obj != NULL )
			{

				SkinnableData skinData = editData ; 
				skinData.name = obj->data.name ;
				skinData.type = obj->data.type  ;
				editTextData.blockText = inputString ; 
				//ofNotifyEvent( ofxSkinnableEvents::Instance()->HUB_UPDATE_OBJECT , skinData ) ;
				cout << "content type : " << obj->data.type << endl; 
				obj->data = skinData ; 
				
				if ( obj->data.type  == 1 )
				{
					cout << "updating TYPE content ! " << endl;; 
					((SkinnableTextBlock*) obj)->textData = editTextData ; 
					((SkinnableTextBlock*) obj)->applyTextData() ; 
				}
			}
			toggle->setValue( false ) ; 
		}
	}*/

}

void testApp::textBlockGuiEventHandler( ofxUIEventArgs &e )
{
	string name = e.widget->getName() ; 

	
	if ( name == "BLOCK TEXT" )
	{
		ofxUITextInput *textinput = (ofxUITextInput *) e.widget;    
		string output = textinput->getTextString(); 
		if ( output.size() < 2 ) 
			textinput->setTextString( "" ) ; 

		//editTextData.blockText = output ; 
		cout << "BLOCK TEXT : " << output << endl ; 
	}

	for(int i = 0; i < fontPaths.size(); i++)
	{
		if ( name == fontPaths[i] ) 
		{
			ofxUIToggle * toggle = (ofxUIToggle *)textBlockGui->getWidget( name ) ; 
			if ( toggle->getValue() ) 
			{
				fontIndex = i ;
				editTextData.fontPath = fontPaths[i] ; 
				cout << "SELECTED: " <<  fontPaths[i] << endl; 
				break ; 
			}
		}		
	}


	for(int i = 0; i < drawAlignments.size(); i++)
	{
		if ( name == drawAlignments[i] ) 
		{
			ofxUIToggle * toggle = (ofxUIToggle *)textBlockGui->getWidget( name ) ; 
			editTextData.bDrawLeft = false ; 
			editTextData.bDrawRight = false ; 
			editTextData.bDrawCenter = false ; 

			if ( toggle->getValue() ) 
			{
				if ( name == "DRAW RIGHT" ) 
					editTextData.bDrawRight = true ; 

				if ( name == "DRAW CENTER" ) 
					editTextData.bDrawCenter = true ; 

				if ( name == "DRAW LEFT" ) 
					editTextData.bDrawLeft = true ; 
				
				break ; 
			}
		}		
	}
	/*
	
	 /*

	 drawAlignments.push_back( "DRAW RIGHT" ) ; 
	drawAlignments.push_back( "DRAW CENTER" ) ; 
	drawAlignments.push_back( "DRAW LEFT" ) ;
	*/


}

void testApp::iconGuiEventHandler( ofxUIEventArgs &args )
{
	
}

void testApp::createNewSkinnableObject( )
{
    SkinnableData * data = hub.createDefaultSkinnableData( ) ;
    data->name = "test"+ofToString( hub.objects.size() ) ;

    SkinnableObject * obj = new SkinnableObject( ) ;
    obj->setup( (*data) ) ;

	/*
	int fontIndex ;
		int widgetTypeIndex ; 
		*/
    bool bResult = hub.addNewSkinnableObject( data , widgetTypeIndex ) ;
	if ( bResult == true )
	{
		if ( widgetTypeIndex == 1 ) 
			((SkinnableTextBlock*)hub.objects[ hub.objects.size() -1 ])->textData = editTextData ;  
	}
}


void testApp::populateSkinnableObjects( )
{
    //vector<SkinnableData*> skinData = hub.data ;
 
    for ( int i = 0 ; i < hub.objects.size()  ; i++ )
    {
        cout << "skinData : " << i << endl ;
        //SkinnableObject * obj = new SkinnableObject( ) ;
        //obj->setup( (*skinData[i]) ) ;
        //objects.push_back ( obj ) ;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	//cout << "keyPressed:: " << key << endl ; 
    switch ( key )
    {  
		case '0':
			disableAllGui() ; 
			break ;

		case '1':
			disableAllGui() ; 
			coreGui->toggleVisible() ; 
			break ; 

		case '2' :
			disableAllGui() ; 
			textBlockGui->toggleVisible() ; 
			break ; 

		case '3':
			disableAllGui() ; 
			iconGui->toggleVisible() ; 
			break ; 

		case 8:
			if ( inputString.size() > 0) 
				inputString.pop_back() ; 
			break ; 

		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '.':
		case ',':
		case ' ':
			inputString += key ; 
			break ; 

		default : 
			//inputString += key ; 
			break ; 
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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
