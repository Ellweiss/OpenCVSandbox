#pragma once

#include <opencv2/core/core.hpp>

#include <string>
#include <vector>

namespace Sandbox
{

class FaceRecognizer
{
public:
	FaceRecognizer();
	FaceRecognizer(const std::string& window_name);

	~FaceRecognizer();

	void SetWindow(const std::string& window_name);

	// Path to CSV file containing list of training images
	void SetTrainingPath(const std::string& training_path);

	bool LoadImg(const std::string& img_path);
	bool GetTrainingSet(std::vector<cv::Mat>& images,
						std::vector<int>& labels);
	bool Train();
	void Run();

private:
	std::string training_path_;
	std::string window_name_;

	cv::Mat mat_;

	bool is_loaded_;
	bool is_trained_;
};

}