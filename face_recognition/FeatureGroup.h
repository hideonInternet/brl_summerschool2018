#ifndef FEATUREGROUP_H
#define FEATUREGROUP_H

#include <fstream>
#include<iostream>
#include <io.h>
#include <queue>
#include <string>
#include "FaceRecognition.h"
struct Feature
{
	std::string name;
	std::string id;
	std::string sno;
	float* data;
	
};

class FeatureGroup
{
public:
	FeatureGroup(int feat_dims, FaceRecognition* fr);
	FeatureGroup(string model_file, FaceRecognition* fr);
	bool AddFeature(float* feat, string name,string id,string sno);
	bool SaveModel(string model_file);
	int GetFeatureDims();
	bool recognition(float* feat, Feature& f,float threshlod);
	bool getStatus();
	~FeatureGroup();

public:
	std::vector<Feature> features;

private:
	int feat_dims;
	bool status = false;
	FaceRecognition* fr;
};



#endif //FEATUREGROUP_H