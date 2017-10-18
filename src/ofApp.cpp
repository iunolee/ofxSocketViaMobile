#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // socketIO part
    isConnected = false;
    address = "http://67.205.153.66:9999";
    status = "not connected";
    socketIO.setup(address);
    /*
     * You can also pass a query parameter at connection if needed.
     */
    // std::map<std::string,std::string> query;
    // query["token"] = "hello";
    // socketIO.setup(address, query);
    ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);
    ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
    
    
    // webcam part
    ofSetFrameRate(8);
    ofBackground(0,0,0);
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();

    vidGrabber.setVerbose(true);
    vidGrabber.setup(camWidth,camHeight);
    ofEnableAlphaBlending();
    
    // set color list
    colors = new ofColor[9];
    
    // initial value
    colors[0].r = 255;
    colors[0].g = 255;
    colors[0].b = 255;
    colors[0].a = 150;

    
    // joy
    colors[1].r = 255;
    colors[1].g = 238;
    colors[1].b = 51;
    
    // trust
    colors[2].r = 153;
    colors[2].g = 255;
    colors[2].b = 51;
    
    // fear
    colors[3].r = 55;
    colors[3].g = 255;
    colors[3].b = 187;
    
    // surprise
    colors[4].r = 51;
    colors[4].g = 221;
    colors[4].b = 255;
    
    // sadness
    colors[5].r = 85;
    colors[5].g = 51;
    colors[5].b = 255;
    
    // disgust
    colors[6].r = 221;
    colors[6].g = 51;
    colors[6].b = 255;
    
    // anger
    colors[7].r = 255;
    colors[7].g = 51;
    colors[7].b = 85;
    
    // anticipation
    colors[8].r = 255;
    colors[8].g = 152;
    colors[8].b = 51;
    
    emotionLists.resize(1);
    }

void ofApp::onConnection () {
    isConnected = true;
    bindEvents();
}

void ofApp::bindEvents () {
    std::string serverEventName = "server-event";
    socketIO.bindEvent(serverEvent, serverEventName);
    ofAddListener(serverEvent, this, &ofApp::onServerEvent);
    //
    //    std::string pingEventName = "pingy";
    //    socketIO.bindEvent(pingEvent, pingEventName);
    //    ofAddListener(pingEvent, this, &ofApp::onPingEvent);
    //
    //    std::string nspingEventName = "nsping";
    //    socketIO.bindEvent(nspingEvent, nspingEventName, "nsp");
    //    ofAddListener(nspingEvent, this, &ofApp::onNSPingEvent);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //     draw pixels from webcam
    
    ofPixelsRef pixelsRef = vidGrabber.getPixels();
    for (int i = 0; i < camWidth; i+= 8){
        for (int j = 0; j < camHeight; j+= 8){
            // get the pixel and its lightness (lightness is the average of its RGB values)
            float lightness = pixelsRef.getColor(i,j).getLightness();
            float dim = ofMap(lightness, 0, 255, 0.1, 4);
            selectedEmotion = emotionLists[int(ofRandom(emotionLists.size()))];
            ofSetColor(colors[selectedEmotion]);
            ofDrawCircle(i, j, dim);
            //ofDrawRectangle(i, j, dim, dim);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f' :
            ofToggleFullscreen();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::gotEvent(string& name) {
    status = name;
}

//--------------------------------------------------------------
void ofApp::onServerEvent (ofxSocketIOData& data) {
    
    int gotData = data.getIntValue("intData");
    emotionLists.push_back(gotData);
    cout << "how many input?" << emotionLists.size() << endl;
    
    
    //    ofLogNotice("ofxSocketIO", data.getStringValue("stringData"));
    //    ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("intData")));
    //    ofLogNotice("ofxSocketIO", ofToString(data.getFloatValue("floatData")));
    //    ofLogNotice("ofxSocketIO", ofToString(data.getBoolValue("boolData")));
    //
    //    ofxSocketIOData nested = data.getNestedValue("nested");
    //    ofLogNotice("ofxSocketIO", ofToString(nested.getStringValue("hello")));
}

void ofApp::onPingEvent (ofxSocketIOData& data) {
    ofLogNotice("got ping");
    
    //    std::string pong = "pongy";
    //    std::string param = "foo";
    //    socketIO.emit(pong, param);
    /*
     * You can also emit without param
     */
    // socketIO.emit(pong);
}

void ofApp::onNSPingEvent (ofxSocketIOData& data) {
    //    ofLogNotice("ofxSocketIO", "nsping");
    //    std::string pong = "nspong";
    //    std::string param = "foo";
    //    std::string nsp = "nsp";
    //    socketIO.emit(pong, param, nsp);
}
