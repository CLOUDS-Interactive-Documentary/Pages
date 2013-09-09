//
//  PagesVisualSystem.cpp
//

#include "PagesVisualSystem.h"
#include "CloudsRGBDVideoPlayer.h"

//#include "CloudsRGBDVideoPlayer.h"
//#ifdef AVF_PLAYER
//#include "ofxAVFVideoPlayer.h"
//#endif

//These methods let us add custom GUI parameters and respond to their events
void PagesVisualSystem::selfSetupGui()
{
	customGui = new ofxUISuperCanvas("PAGE", gui);
	customGui->copyCanvasStyle(gui);
	customGui->copyCanvasProperties(gui);
	customGui->setName("Page");
	customGui->setWidgetFontSize(OFX_UI_FONT_SMALL);
    
    customGui->addSpacer();
    
    numPages = 1;
    customGui->addSlider("Num Pages", 0, 20, numPages);
	   
    customGui->addSpacer();
    
	customGui->addSlider("Fill Alpha", 0, 1, &fillAlpha);
	customGui->addSlider("Mesh Alpha", 0, 1, &meshAlpha);

    customGui->addSpacer();

    customGui->addSlider("Offset", 0, 1, &offsetAmount);
	customGui->addSlider("Align", 0, 1, &alignAmount);
    
    customGui->addSpacer();
    
    customGui->addSlider("Twirl", 0, 1, &twirlAmount);
	customGui->addSlider("Tilt", 0, 1, &tiltAmount);
    customGui->addSlider("Flip", 0, 1, &flipAmount);
	customGui->addSlider("Sway", 0, 1, &swayAmount);
    
    customGui->addSpacer();
    
	customGui->addToggle("Bend Tail", &bendTail);
    customGui->addToggle("Bend Wings", &bendWings);
	customGui->addToggle("Bend Fresh", &bendFresh);
    customGui->addSlider("Top Bend", 0, 1, &topBendAmount);
	customGui->addSlider("Bottom Bend", 0, 1, &bottomBendAmount);
    
    customGui->addSpacer();

    customGui->addSlider("Tornado", 0, 1, &tornadoAmount);
	customGui->addSlider("Speed", 0, 1, &speedAmount);
    customGui->addSlider("Expand", 0, 1, &expandAmount);
    customGui->addSlider("Lift", 0, 1, &liftAmount);
	
	ofAddListener(customGui->newGUIEvent, this, &PagesVisualSystem::selfGuiEvent);
	
	guis.push_back(customGui);
	guimap[customGui->getName()] = customGui;
}

void PagesVisualSystem::selfGuiEvent(ofxUIEventArgs &e)
{
	if (e.widget->getName().compare("Num Pages") == 0) {
        numPages = ((ofxUISlider *)e.widget)->getScaledValue();
	}
}

//Use system gui for global or logical settings, for exmpl
void PagesVisualSystem::selfSetupSystemGui(){
	
}

void PagesVisualSystem::guiSystemEvent(ofxUIEventArgs &e){
	
}
//use render gui for display settings, like changing colors
void PagesVisualSystem::selfSetupRenderGui(){

}

void PagesVisualSystem::guiRenderEvent(ofxUIEventArgs &e){
	
}

// selfSetup is called when the visual system is first instantiated
// This will be called during a "loading" screen, so any big images or
// geometry should be loaded here
void PagesVisualSystem::selfSetup()
{

}

// selfPresetLoaded is called whenever a new preset is triggered
// it'll be called right before selfBegin() and you may wish to
// refresh anything that a preset may offset, such as stored colors or particles
void PagesVisualSystem::selfPresetLoaded(string presetPath){
	
}

// selfBegin is called when the system is ready to be shown
// this is a good time to prepare for transitions
// but try to keep it light weight as to not cause stuttering
void PagesVisualSystem::selfBegin(){
	
}

//do things like ofRotate/ofTranslate here
//any type of transformation that doesn't have to do with the camera
void PagesVisualSystem::selfSceneTransformation(){
	
}

//normal update call
void PagesVisualSystem::selfUpdate()
{
    // add pages
    while (pages.size() < numPages) {
        Page * page = new Page();
        page->rainSpeed.set(ofRandom(-2, -5), -1 * ofRandom(2, 10), ofRandom(10));
        pages.push_back(page);
    }

    // remove pages
    while (pages.size() > numPages) {
        delete pages.back();
        pages.pop_back();
    }
    
    for (int i = 0; i < pages.size(); i++) {
        pages[i]->update();
    }
}

// selfDraw draws in 3D using the default ofEasyCamera
// you can change the camera by returning getCameraRef()
void PagesVisualSystem::selfDraw()
{	
//	ofPushMatrix();
//	setupRGBDTransforms();
//	pointcloudShader.begin();
//	getRGBDVideoPlayer().setupProjectionUniforms(pointcloudShader);
//	simplePointcloud.drawVertices();
//	pointcloudShader.end();
//	ofPopMatrix();
	
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    for (int i = 0; i < pages.size(); i++) {
        pages[i]->preDraw();
        ofEnableLighting();
        mat->begin();
        pages[i]->fillDraw();
        mat->end();
        ofDisableLighting();
        pages[i]->meshDraw();
        pages[i]->postDraw();
    }
}

// draw any debug stuff here
void PagesVisualSystem::selfDrawDebug()
{
    for (auto& it : lights) {
        ofSetColor((it.second)->lightAmbient);
        ofSphere((it.second)->lightPos, 10);
        ofLine((it.second)->lightPos, (it.second)->lightPos + ((it.second)->lightOrientation * 20));
    }
}

// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
void PagesVisualSystem::selfDrawBackground(){

	//turn the background refresh off
	//bClearBackground = false;
	
}

// this is called when your system is no longer drawing.
// Right after this selfUpdate() and selfDraw() won't be called any more
void PagesVisualSystem::selfEnd()
{
    for (int i = 0; i <  pages.size(); i++) {
        delete pages[i];
    }
    pages.clear();
}

// this is called when you should clear all the memory and delet anything you made in setup
void PagesVisualSystem::selfExit(){
	
}

//events are called when the system is active
//Feel free to make things interactive for you, and for the user!
void PagesVisualSystem::selfKeyPressed(ofKeyEventArgs & args){
	
}
void PagesVisualSystem::selfKeyReleased(ofKeyEventArgs & args){
	
}

void PagesVisualSystem::selfMouseDragged(ofMouseEventArgs& data){
	
}

void PagesVisualSystem::selfMouseMoved(ofMouseEventArgs& data){
	
}

void PagesVisualSystem::selfMousePressed(ofMouseEventArgs& data){
	
}

void PagesVisualSystem::selfMouseReleased(ofMouseEventArgs& data){
	
}
