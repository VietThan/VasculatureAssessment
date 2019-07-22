// File name: AdaptiveThreshold.cpp
// Author: Viet Than
// Email: viet.than@vanderbilt.edu (thanhoangviet@gmail.com)
// Lab: Medical Imaging Lab under Ipek Oguz
// Description: Implementing adaptive thresholding for a 3d image



#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkExtractImageFilter.h"

#include "include/itkAdaptiveOtsuThresholdImageFilter.h"


#include <string>
#include <iostream>
#include <chrono>
#include <iomanip> //set precision
#include <sstream> //stringstream

using namespace itk;

//helper functions
std::string makeInputFileName (const std::string &filename, const std::string &filetype);
std::string makeOutputFileName (const std::string &filename, const std::string &filetype, 
				const double &radius, const unsigned int &numOfSamples, 
				const unsigned int & numOfLevels, const unsigned int &numOfControlPts);


template <typename T> std::string returnPointString(const T &number);

// 7 arguments:
// 1 - filename
// 2 - filetype
// 3 - radius
// 4 - numOfSamples
// 5 - numOfLevels
// 6 - numOfControlPts
int main(int argc, char * argv []){
	std::cout << "Starting Hessian filter" << std::endl;

	if (argc > 7){
		std::cout << "too many arguments" << std::endl;
		return EXIT_FAILURE;
	}

	// setting up arguments
	std::string filename, filetype;
	double radius;
	unsigned int numOfSamples, numOfLevels, numOfControlPts;
	
	// constexpr, computation at compile time
	constexpr unsigned int Dimension = 3;
	constexpr float desiredMinimum = 0.0;
	constexpr float desiredMaximum = 255.0;
	
	if (argc == 7){
		filename = argv[1];
		filetype = argv[2];
		radius = std::stof(argv[3]);
		numOfSamples = std::atoi(argv[4]);
		numOfLevels = std::atoi(argv[5]);
		numOfControlPts = std::atoi(argv[6]);
	} else {
		std::cout << "Not enough arguments, went with default" << std::endl;
		filename = "volume"; //filename in data/
		filetype = ".nii";
		radius = 20;
		numOfSamples = 1000;
		numOfLevels = 3;
		numOfControlPts = 30;
	}

	//timing
	auto start = std::chrono::high_resolution_clock::now();	

	std::string inputFileName = makeInputFileName(filename, filetype);
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for reading in the file and creating constants"<<std::endl;


  	
	std::string outputFileName = makeOutputFileName(filename, filetype, radius, numOfSamples, numOfLevels, numOfControlPts);


	//Setting up the image reader of the particular type
	using PixelType = float;
  	using ImageType = itk::Image< PixelType, Dimension >;
  	using ReaderType = itk::ImageFileReader< ImageType >;

	//Setting up the reader
  	ReaderType::Pointer reader = ReaderType::New();
  	reader->SetFileName( inputFileName );
  	try {
    	reader->Update();
    	} catch ( itk::ExceptionObject & error ){
    	std::cerr << "Error: " << error << std::endl;
    	return EXIT_FAILURE;
    	}

 	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for setting image and reader"<<std::endl;


	///////////////////////////////////////////
	//           SET FILTER HERE             //
	
	typedef ImageType::SizeType SizeType;
	typedef ImageType::SpacingType SpacingType;
	typedef SizeType::SizeValueType SizeValueType;
	typedef itk::AdaptiveOtsuThresholdImageFilter<ImageType, ImageType> AdaptFilterType;
	
	ImageType::Pointer image = reader->GetOutput();
	ImageType::RegionType region = image->GetLargestPossibleRegion();
	ImageType::SizeType size = region.GetSize();
	SpacingType spacing = image->GetSpacing();

	SizeType m_radius;
	for (unsigned int i = 0; i < Dimension; ++i){
		m_radius[i] = static_cast<SizeValueType>( radius/spacing[i] );
	}

	AdaptFilterType::Pointer adaptFilter = AdaptFilterType::New();
	adaptFilter->SetInput( reader->GetOutput() );
	adaptFilter->SetInsideValue( desiredMaximum );
	adaptFilter->SetOutsideValue( desiredMinimum );
	adaptFilter->SetNumberOfHistogramBins( 256 );
	adaptFilter->SetNumberOfControlPoints( numOfControlPts );
	adaptFilter->SetNumberOfLevels( numOfLevels );
	adaptFilter->SetNumberOfSamples( numOfSamples );
	adaptFilter->SetRadius( m_radius );
	adaptFilter->Update();

	///////////////////////////////////////////

	//Setting up the output writer
  	using WriterType = itk::ImageFileWriter< ImageType >;//setting up type for writer
  	WriterType::Pointer writer = WriterType::New();//initialize new writer pointer
  	writer->SetFileName( outputFileName );//set filename for writer
  	writer->SetInput( adaptFilter->GetOutput() );//
	//writer->SetUseCompression( true );
	
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for setting up writer" << std::endl;


	//Write to file
  	try {
    	writer->Update();
    	} catch ( itk::ExceptionObject & error ){
    	std::cerr << "Error: " << error << std::endl;
    	return EXIT_FAILURE;
    	}
	
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds when file written out succesfully" << std::endl;
  	return EXIT_SUCCESS;
	

}

//Creating the input file name for a nifti
std::string makeInputFileName (const std::string &filename, const std::string &filetype){
	std::string inputFileName = "../data/";
	inputFileName.append(filename);
	inputFileName.append(filetype);
	return inputFileName;
}

//Creating the output filename for a nifti
std::string makeOutputFileName   (const std::string &filename, const std::string &filetype, 
				const double &radius, const unsigned int &numOfSamples, 
				const unsigned int & numOfLevels, const unsigned int &numOfControlPts){
	std::string OutputFileName = "../output/";
	OutputFileName.append(filename);
	OutputFileName.append("_AdapThresh").append("_");
	OutputFileName.append(returnPointString(radius));
	OutputFileName.append("_");
	OutputFileName.append(std::to_string(numOfSamples));
	OutputFileName.append("_");
	OutputFileName.append(std::to_string(numOfLevels));
	OutputFileName.append("_");
	OutputFileName.append(std::to_string(numOfControlPts));
	OutputFileName.append(filetype);
	return OutputFileName;
}

template <typename T> std::string returnPointString(const T &number){
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << number;
    std::string s = stream.str();

    s.replace(s.find('.'), 1, "p");
    return s;
}


