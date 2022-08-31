#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetColor(0);
	ofNoFill();
	ofSetLineWidth(2);
	ofSetCircleResolution(72);
	this->random_seed = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 60 < 5) {

		this->random_seed = ofRandom(1000);
	}
	
	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofPushMatrix();
	ofTranslate(ofGetWindowSize() * 0.5);

	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(255, 0, 0));
	color_palette.push_back(ofColor(0, 255, 0));
	color_palette.push_back(ofColor(0, 0, 255));
	color_palette.push_back(ofColor(255, 255, 0));
	color_palette.push_back(ofColor(255, 0, 255));
	color_palette.push_back(ofColor(0, 255, 255));

	auto number_of_sphere = 150;
	vector<glm::vec2> location_list;
	vector<float> radius_list;

	while (location_list.size() < number_of_sphere) {

		auto location = glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300));
		auto radius = ofRandom(8, 70);
		bool flag = true;
		for (int i = 0; i < location_list.size(); i++) {

			if (glm::distance(location, location_list[i]) < (radius + radius_list[i])) {

				flag = false;
				break;
			}
		}

		if (flag) {

			location_list.push_back(location);
			radius_list.push_back(radius);
		}
	}

	int count = 0;
	while (true) {

		auto all = true;

		for (int i = 0; i < location_list.size(); i++) {

			auto flag = true;
			for (int k = 0; k < location_list.size(); k++) {

				if (i == k) { continue; }
				                
				if (glm::distance(location_list[i], location_list[k]) < (radius_list[i] + radius_list[k])) {

					flag = false;
				}
			}

			if (flag) {

				radius_list[i] += 1;
				all = false;
				break;
			}
		}

		if (all) {

			break;
		}

		count++;
	}

	for (int i = 0; i < location_list.size(); i++) {
	
		auto param = ofGetFrameNum() % 60 < 5 ? 0.2 : ofGetFrameNum() % 60 < 15 ? ofMap(ofGetFrameNum() % 60, 5, 15, 0.2, 1) : 1;

		ofDrawCircle(location_list[i], radius_list[i] * param);
	}

	ofPopMatrix();

}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}