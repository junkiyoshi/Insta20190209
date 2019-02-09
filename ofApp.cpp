#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> locations;
	vector<ofColor> colors;
	for (int i = 0; i < 7; i++) {

		auto location = glm::vec2(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003), 0, 1, 0, ofGetWidth()), 
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003), 0, 1, 0, ofGetHeight()));
		locations.push_back(location);

		ofColor color;
		color.setHsb(ofMap(i, 0, 7, 0, 255), 255, 255);
		colors.push_back(color);
	}

	auto radius = 30.f;
	for (int i = 0; i < locations.size(); i++) {

		ofSetColor(colors[i]);
		ofNoFill();
		ofDrawCircle(locations[i], radius);

		ofFill();
		ofDrawCircle(locations[i], radius * 0.5);

		for (int k = 0; k < locations.size(); k++) {

			if (i == k) { continue; }

			auto angle_i = std::atan2(locations[k].y - locations[i].y, locations[k].x - locations[i].x);
			auto satellite_point_i = locations[i] + glm::vec2(radius * cos(angle_i), radius * sin(angle_i));
			auto angle_k = std::atan2(locations[i].y - locations[k].y, locations[i].x - locations[k].x);
			auto satellite_point_k = locations[k] + glm::vec2(radius * cos(angle_k), radius * sin(angle_k));
			
			auto distance = glm::distance(satellite_point_i, satellite_point_k);
			ofSetColor(colors[i], ofMap(distance, 0, 300, 255, 0));
			ofDrawLine(satellite_point_i, satellite_point_k);

			ofSetColor(colors[k]);
			ofDrawCircle(satellite_point_i, radius * 0.2);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}