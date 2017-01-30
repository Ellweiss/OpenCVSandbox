#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdlib>

#include "FaceDetector.hpp"

/*
void Launch(const std::string& img_path, const std::string& training_path)
{
	namedWindow("Display", cv::WINDOW_AUTOSIZE);

	cv::Ptr<Sandbox::FaceRecognizer> pFr(new Sandbox::FaceRecognizer());

	pFr->SetWindow("Display");
	pFr->SetTrainingPath(training_path);

	if (pFr->LoadImg(img_path))
	{
		pFr->Run();
	}
}
*/

// Inaccessible function, safe to assume argv is size 4
void Launch(char **argv)
{
	namedWindow("Display", cv::WINDOW_AUTOSIZE);

	cv::Ptr<Sandbox::FaceDetector> pFd(new Sandbox::FaceDetector());

	pFd->SetWindow("Display");
	pFd->LoadImg(argv[1]);
	pFd->SetFaceCascadePath(argv[2]);
	pFd->SetEyesCascadePath(argv[3]);

	if (pFd->IsLoaded())
	{
		pFd->Run();
	}
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: .\\FaceRecognition <img> <face_file> <eye_file>" << std::endl;
		return EXIT_FAILURE;
	}

	Launch(argv);

	return EXIT_SUCCESS;
}