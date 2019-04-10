#pragma once

#include "Graph.h"
#include "ofRectangle.h"
#include "ofxTrueTypeFontUC.h"

class ofVec2f;

class ofxGraph : public Graph
{
public:
	void setup(ofRectangle boundRect);
	void update();
	void draw();

	void deleteEdge(unsigned from, unsigned to) override;
	void setSpeed(ofVec2f from, ofVec2f to);

	void showNodeCapture();
	void hideNodeCapture();

	void showEdgeCapture();
	void hideEdgeCapture();

	// TODO: Methods
	// Количество вершин
	int getNodesCount();
	// Количество всего возможных рёбер
	int getMaxEdgesCount();
	// Количество наблюдаемых рёбер (в данный момент)
	int getCurrEdgesCount();
	// Подсчет сетевой плотности
	float getNetworkDensity();

private:
	void createNodeInstance(unsigned id) override;
	void createEdgeInstance(unsigned from, unsigned to, int weight) override;

	bool nodeCaptureShowed_ = true;
	bool edgeCaptureShowed_ = false;

	std::shared_ptr<ofRectangle> boundRect_;
	std::shared_ptr<ofxTrueTypeFontUC> nodeCaptureFont_;
	std::shared_ptr<ofxTrueTypeFontUC> edgeCaptureFont_;
};
