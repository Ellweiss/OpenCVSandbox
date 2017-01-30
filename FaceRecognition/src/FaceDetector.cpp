#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <cmath>
#include <string>
#include <vector>

#include "Error.hpp"
#include "FaceDetector.hpp"

namespace Sandbox
{

FaceDetector::FaceDetector() :
	face_classifier_(new cv::CascadeClassifier()),
	eyes_classifier_(new cv::CascadeClassifier())
{}

FaceDetector::FaceDetector(const std::string& name) :
	window_name_(name),
	face_classifier_(new cv::CascadeClassifier()),
	eyes_classifier_(new cv::CascadeClassifier())
{}

FaceDetector::~FaceDetector()
{}

void FaceDetector::SetWindow(const std::string& name)
{
	this->window_name_ = name;
}

bool FaceDetector::IsLoaded() const
{
	return this->loaded_.all();
}

void FaceDetector::DetectFaces(bool should_draw)
{
	this->face_classifier_->detectMultiScale(this->gray_img_, this->faces_, 1.1, 2,
											 0 | cv::CASCADE_SCALE_IMAGE,
											 cv::Size(30, 30));

	if (should_draw)
	{
		for (cv::Rect f : this->faces_)
		{
			cv::Point center(f.x + f.width / 2, f.y + f.height / 2);
			cv::ellipse(this->img_, center,
						cv::Size(f.width / 2, f.height / 2),
						0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
		}
	}
}

void FaceDetector::DetectEyes(bool should_draw)
{
	for (cv::Rect f : this->faces_)
	{
		cv::Mat faceROI = this->gray_img_(f);
		std::vector<cv::Rect> eyes;

		this->eyes_classifier_->detectMultiScale(faceROI, eyes, 1.1, 2,
												 0 | cv::CASCADE_SCALE_IMAGE,
												 cv::Size(30, 30));

		if (should_draw)
		{
			for (cv::Rect e : eyes)
			{
				cv::Point center(f.x + e.x + e.width / 2, f.y + e.y + e.height / 2);
				int radius = static_cast<int>( round((e.width + e.height) * 0.25) );
				cv::circle(this->img_, center, radius,
						   cv::Scalar(255, 0, 0), 4, 8, 0);
			}
		}
	}
}

bool FaceDetector::Run()
{
	if (this->IsLoaded())
	{
		this->DetectFaces(true);
		this->DetectEyes(true);

		cv::imshow(this->window_name_, this->img_);
		cv::waitKey(0);

		return true;
	}

	return Sandbox::Error("Face Detector was not properly loaded. Verify Image and Classifiers.");
}

bool FaceDetector::SetFaceCascadePath(const std::string& path)
{
	try
	{
		if (face_classifier_->load(path))
		{
			this->loaded_[EBits::FACE] = true;
			
		}
	}
	catch (cv::Exception& e)
	{
		Sandbox::Error("Could not load Face Classifier. Check path.");
		this->loaded_[EBits::FACE] = false;
		return false;
	}

	return true;
}

bool FaceDetector::SetEyesCascadePath(const std::string& path)
{
	try
	{
		if (this->eyes_classifier_->load(path))
		{
			this->loaded_[EBits::EYES] = true;
		}
	}
	catch (cv::Exception& e)
	{
		Sandbox::Error("Could not load Eyes Classifier. Check path.");
		loaded_[EBits::EYES] = false;
		return false;
	}

	return true;
}

bool FaceDetector::LoadImg(const std::string& img_path)
{
	cv::Mat img;
	img = cv::imread(img_path, cv::IMREAD_COLOR);

	if (!img.data)
	{
		return Sandbox::Error("Invalid file path.");
	}

	this->img_ = img;
	cv::cvtColor(img, this->gray_img_, cv::COLOR_BGR2GRAY);
	cv::equalizeHist(this->gray_img_, this->gray_img_);

	this->loaded_[EBits::IMG] = true;

	return true;
}

}