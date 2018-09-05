#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <string>
#include<iostream>
#include<fstream>
#include <opencv/cv.h>
#include<opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include "face_detection.h"
#include "face_alignment.h"
#include "face_identification.h"

using std::string;
using namespace cv;

class FaceRecognition{
public:

	FaceRecognition();
	float* NewFeatureBuffer();
	float FeatureCompare(float* feat1, float* feat2);
	int GetFeatureDims();
	bool GetFeature(Mat frame, float* feat);
	bool hasFaceDetected(Mat frame);
	bool hasFaceDetected(Mat frame, std::vector<seeta::FaceInfo> faces);
	bool SaveFeature(string filename, float* feat);
	void showFace(Mat &frame);
	~FaceRecognition();
public:
	seeta::FaceDetection* detector;
	seeta::FaceAlignment* point_detector;
	seeta::FaceIdentification* face_recognizer;

};

#endif FACERECOGNITION_H