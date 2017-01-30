#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect.hpp>

#include <bitset>

namespace Sandbox
{

class FaceDetector
{
public:
	FaceDetector();
	FaceDetector(const std::string& name);

	~FaceDetector();

	void SetWindow(const std::string& name);

	// Path to CSV file containing list of training images
	bool SetFaceCascadePath(const std::string& path);
	bool SetEyesCascadePath(const std::string& path);
	bool LoadImg(const std::string& path);

	bool IsLoaded() const;
	bool Run();

private:
	void DetectFaces(bool should_draw);
	void DetectEyes(bool should_draw);

	std::vector<cv::Rect> faces_;

	cv::Mat gray_img_;
	cv::Mat img_;

	enum EBits
	{
		IMG = 0,
		FACE = 1,
		EYES = 2,
		SIZE = 3,
	};

	std::bitset<EBits::SIZE> loaded_;

	std::string window_name_;

	cv::Ptr<cv::CascadeClassifier> face_classifier_;
	cv::Ptr<cv::CascadeClassifier> eyes_classifier_;
};

}