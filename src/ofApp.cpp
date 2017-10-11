#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    isConnected = false;
    address = "http://127.0.0.1:9999";
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
    
    
    r = 255;
    g = 0;
    b = 64;
}

void ofApp::onConnection () {
    isConnected = true;
    bindEvents();
}

void ofApp::bindEvents () {
    std::string serverEventName = "server-event";
    socketIO.bindEvent(serverEvent, serverEventName);
    ofAddListener(serverEvent, this, &ofApp::onServerEvent);
    
    std::string pingEventName = "pingy";
    socketIO.bindEvent(pingEvent, pingEventName);
    ofAddListener(pingEvent, this, &ofApp::onPingEvent);
    
    std::string nspingEventName = "nsping";
    socketIO.bindEvent(nspingEvent, nspingEventName, "nsp");
    ofAddListener(nspingEvent, this, &ofApp::onNSPingEvent);
}

//--------------------------------------------------------------
void ofApp::update(){
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(r, g, b);
    ofDrawBitmapStringHighlight(ofApp::status, 20, 20);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
        r = data.getIntValue("number");
        g = data.getIntValue("number");
        b = data.getIntValue("number");
      ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("number")));
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

