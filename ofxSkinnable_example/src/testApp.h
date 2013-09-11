#pragma once

#include "ofMain.h"
#include "ofxSkinnable.h"
#include "ofxUI.h"
#include "SkinnableTextData.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void createNewSkinnableObject ( ) ;
        void populateSkinnableObjects( ) ;
	
		
		SkinnableObjectHub hub ; 

		/* Gui Stuff */
		void disableAllGui() ; 
		void saveAllGuis() ; 
		void loadAllGuis() ; 
		ofxUICanvas * coreGui ; 
		ofxUICanvas * textBlockGui ; 
		ofxUICanvas * iconGui ;

		vector< string > fontPaths ; 
		vector< string > newObjectType ;
		vector< string > drawAlignments ; 

		int fontIndex ;
		int widgetTypeIndex ; 

		void coreGuiEventHandler ( ofxUIEventArgs &args ) ; 
		void textBlockGuiEventHandler ( ofxUIEventArgs &args ) ; 
		void iconGuiEventHandler ( ofxUIEventArgs &args ) ; 

		SkinnableData editData ;
		SkinnableTextData editTextData ; 

		void setupGui( ) ; 
		int guiWidth ; 

		string inputString ; 
		int lastSelectedIndex ; 
};
