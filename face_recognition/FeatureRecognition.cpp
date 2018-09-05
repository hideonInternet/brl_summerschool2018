
#include "FaceRecognition.h"

using namespace cv;

FaceRecognition::FaceRecognition()
{
	this->detector = new seeta::FaceDetection("model/detectmodel/seeta_fd_frontal_v1.0.bin");
	this->detector->SetMinFaceSize(40);
	this->detector->SetScoreThresh(2.f);
	this->detector->SetImagePyramidScaleFactor(0.8f);
	this->detector->SetWindowStep(4, 4);
	this->point_detector = new seeta::FaceAlignment("model/alignmodel/seeta_fa_v1.1.bin");
	this->face_recognizer = new seeta::FaceIdentification("model/identifymodel/seeta_fr_v1.0.bin");
}

float* FaceRecognition::NewFeatureBuffer()
{
	return new float[this->face_recognizer->feature_size()];
}

int FaceRecognition::GetFeatureDims()
{
	return this->face_recognizer->feature_size();
}

float FaceRecognition::FeatureCompare(float* feat1, float* feat2)
{
	return this->face_recognizer->CalcSimilarity(feat1, feat2);
}

void FaceRecognition::showFace(Mat& frame){
	

	Rect face_rect;
	std::vector<seeta::FaceInfo> faces;
	if (hasFaceDetected(frame,faces))
		for (int32_t i = 0; i < 1; i++) {
			face_rect.x = faces[i].bbox.x;
			face_rect.y = faces[i].bbox.y;
			face_rect.width = faces[i].bbox.width;
			face_rect.height = faces[i].bbox.height;

			cv::rectangle(frame, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);
		}
}

bool FaceRecognition::hasFaceDetected(Mat frame ){
	Mat img_gray;
	std::vector<seeta::FaceInfo> faces;
	if (frame.channels() != 1)
		cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);
	else
		img_gray = frame;
	seeta::ImageData src_img_data_gray(img_gray.cols, img_gray.rows, img_gray.channels());
	src_img_data_gray.data = img_gray.data;
	faces = this->detector->Detect(src_img_data_gray);
	return faces.size() == 0 ? false : true;
}
bool FaceRecognition::hasFaceDetected(Mat frame, std::vector<seeta::FaceInfo> faces){
	Mat img_gray;
	if (frame.channels() != 1)
		cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);
	else
		img_gray = frame;
	seeta::ImageData src_img_data_gray(img_gray.cols, img_gray.rows, img_gray.channels());
	src_img_data_gray.data = img_gray.data;
	faces = this->detector->Detect(src_img_data_gray);
	return faces.size() == 0 ? false : true;
}
bool FaceRecognition::GetFeature(Mat frame, float* feat)
{
	//load image and convert to gray
	//cv::Mat src_img_color = cv::imread(filename, cv::IMREAD_UNCHANGED);
	Mat src_img_color = frame.clone();
	cv::Mat src_img_gray;
	if (src_img_color.channels() != 1)
		cv::cvtColor(src_img_color, src_img_gray, CV_BGR2GRAY);
	else
		src_img_gray = src_img_color;

	seeta::ImageData src_img_data_color(src_img_color.cols, src_img_color.rows, src_img_color.channels());
	src_img_data_color.data = src_img_color.data;

	seeta::ImageData src_img_data_gray(src_img_gray.cols, src_img_gray.rows, src_img_gray.channels());
	src_img_data_gray.data = src_img_gray.data;
	
	//Detect faces
	
	std::vector<seeta::FaceInfo> faces = this->detector->Detect(src_img_data_gray);
	int32_t face_num = static_cast<int32_t>(faces.size());
	if (face_num == 0)
	{
		std::cout << "Faces are not detected." << std::endl;
		return false;
	}

	//Detect 5 facial landmarks
	seeta::FacialLandmark points[5];
	this->point_detector->PointDetectLandmarks(src_img_data_gray, faces[0], points);

	//Extract face identity feature

	this->face_recognizer->ExtractFeatureWithCrop(src_img_data_color, points, feat);

	return true;

}

FaceRecognition::~FaceRecognition()
{
	if (detector)
		delete detector;
	if (point_detector)
		delete point_detector;
	if (face_recognizer)
		delete face_recognizer;
}