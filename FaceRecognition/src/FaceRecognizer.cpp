#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <fstream>
#include <vector>

#include "Error.hpp"
#include "FaceRecognizer.hpp"

namespace Sandbox
{

FaceRecognizer::FaceRecognizer() :
	is_loaded_(false),
	is_trained_(false)
{}

FaceRecognizer::FaceRecognizer(const std::string& window_name) :
	is_loaded_(false),
	is_trained_(false),
	window_name_(window_name)
{}

FaceRecognizer::~FaceRecognizer()
{}

void FaceRecognizer::Run()
{
	if (!is_loaded_)
	{ return; }

	if (!is_trained_)
	{
		this->Train();
	}

	cv::imshow(this->window_name_, this->mat_);

	cv::waitKey(0);
}

bool FaceRecognizer::GetTrainingSet(std::vector<cv::Mat>& images,
									std::vector<int>& labels)
{
	// TODO

	std::ifstream file(this->training_path_, std::ifstream::in);
	if (!file)
	{ return Sandbox::Error("Invalid training file path."); }

//	while (std::getline())

	if (images.size() < 2)
	{ return Sandbox::Error("Training set too small."); }

	return true;
}

bool FaceRecognizer::Train()
{
	// TODO
	std::vector<cv::Mat> images;
	std::vector<int> labels;

	if (GetTrainingSet(images, labels))
	{
		is_trained_ = true;
	}

	return false;
}

void FaceRecognizer::SetWindow(const std::string& window_name)
{
	this->window_name_ = window_name;
}

void FaceRecognizer::SetTrainingPath(const std::string& training_path)
{
	training_path_ = training_path_;
}

bool FaceRecognizer::LoadImg(const std::string& img_path)
{
	cv::Mat image;
	image = cv::imread(img_path, cv::IMREAD_COLOR);

	if (!image.data)
	{
		return Sandbox::Error("Invalid file path.");
	}

	this->mat_ = image;
	this->is_loaded_ = true;

	return true;
}

}