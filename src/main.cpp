#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    //for laptop

    ofSetupOpenGL(1280,720,OF_WINDOW);

    // for bigscreen
//    ofGLFWWindowSettings settings;
//    settings.windowMode = OF_FULLSCREEN;
//    settings.multiMonitorFullScreen = true;
//    ofCreateWindow(settings);
//
    ofRunApp(new ofApp());

}
