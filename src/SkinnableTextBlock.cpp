#include "SkinnableTextBlock.h"

void SkinnableTextBlock::setup ( string _name ) 
{
	data.type = 1 ; 
	SkinnableObject::setup( ) ;

	lastFontSize = 4.0f ; 
	lastFontPath = "" ; 
	lastTextBlock = "" ; 
}
	
void SkinnableTextBlock::update ( ) 
{

}

void SkinnableTextBlock::draw ( ) 
{
	SkinnableObject::draw( ) ; 
	ofPushMatrix( ) ;

		ofTranslate( data.x , data.y ) ; 
        ofRotateZ( rotation ) ;
		ofSetColor( 255 , 212 , 128 , 25) ; 
      
		ofSetColor( textData.grayscaleColor ) ; 
		if ( textData.bDrawRight ) 
			textBlock.drawRight( 0 , 0 ) ; 
		else if ( textData.bDrawCenter ) 
			textBlock.drawCenter( 0, 0 ) ; 
		else if ( textData.bDrawLeft ) 
			textBlock.drawLeft( 0 , 0 ) ;
		else 
			textBlock.draw ( 0 , 0 ) ; 
		ofPopMatrix( ) ;
}

void SkinnableTextBlock::writeDataToXml( ofxXmlSettings *xml , float scale ) 
{
	data.writeDataToXml( xml , scale  ) ; 
	textData.writeDataToXml( xml , scale ) ; 
}

void SkinnableTextBlock::loadDataFromXml( ofxXmlSettings *xml ) 
{
	cout << "skinnableTextBlock:: loadDataFromXML " << endl ; 
	data.loadDataFromXml( xml ) ; 
	textData.loadDataFromXml( xml ) ; 
	applyTextData() ; 
}

void SkinnableTextBlock::applyTextData ( ) 
{
	//cout << "applying text data... " << endl ; 
	//cout << textData.toString() << endl ; 

	if ( lastFontSize != textData.fontSize || lastFontPath != textData.fontPath )
	{
		textBlock.init( textData.fontPath , textData.fontSize ) ; 
	}
	textBlock.setText( "" ) ; 
	textBlock.setText( textData.blockText ) ; 

	if ( textData.bWrapX ) 
		textBlock.wrapTextX( data.width ) ; 
	if ( textData.bWrapBox ) 
		textBlock.wrapTextArea( data.width , data.height ) ; 
	textBlock.setLineHeight( textData.lineSpacing ) ; 

	lastFontSize = textData.fontSize ; 
	lastFontPath = textData.fontPath ; 
	lastTextBlock = textData.blockText ; 

}