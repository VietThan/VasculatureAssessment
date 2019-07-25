// File name: WhiteHatThreshold.cpp
// Author: Viet Than
// Email: viet.than@vanderbilt.edu (thanhoangviet@gmail.com)
// Lab: Medical Imaging Lab under Ipek Oguz
// Description: Implementing white top hat for a 3d image, extracting local maxima



#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkExtractImageFilter.h"

#include "itkWhiteTopHatImageFilter.h"
#include "itkBinaryBallStructuringElement.h"

#include <string>
#include <iostream>
#include <chrono>
#include <iomanip> //set precision
#include <sstream> //stringstream

using namespace itk;

//helper functions
std::string makeInputFileName (const std::string &filename, const std::string &filetype);
std::string makeOutputFileName (const std::string &filename, const std::string &filetype, 
				const unsigned int &algorithm);



// 5 arguments:
// 1 - filename
// 2 - filetype
// 3 - algorithm
// 4 - radius
int main(int argc, char * argv []){
	std::cout << "Starting White Top Hat thresholding" << std::endl;

	if (argc > 5){
		std::cout << "too many arguments" << std::endl;
		return EXIT_FAILURE;
	}

	// setting up arguments
	std::string filename, filetype;
	unsigned int algorithm;
	double radius;
	
	// constexpr, computation at compile time
	constexpr unsigned int Dimension = 3;
	constexpr float desiredMinimum = 0.0;
	constexpr float desiredMaximum = 255.0;
	
	if (argc == 5){
		filename = argv[1];
		filetype = argv[2];
		algorithm = std::atoi(argv[3]);
		radius = std::stof(argv[4]);
	} else {
		std::cout << "Not enough arguments, went with default" << std::endl;
		filename = "volume_norm_tif"; //filename in data/
		filetype = ".nii";
		algorithm = 0;
		radius = 8;
	}

	//timing
	auto start = std::chrono::high_resolution_clock::now();	

	std::string inputFileName = makeInputFileName(filename, filetype);
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " milliseconds for reading in the file and creating constants"<<std::endl;


  	
	std::string outputFileName = makeOutputFileName(filename, filetype, radius);


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
	
	using SizeType = ImageType::SizeType;
	using SpacingType = ImageType::SpacingType;
	using SizeValueType = SizeType::SizeValueType;
	using StructuringElementType = itk::BinaryBallStructuringElement<PixelType, Dimension>;
	using WhiteHatFilterType = itk::WhiteTopHatImageFilter<ImageType, ImageType, StructuringElementType >;

	ImageType::Pointer image = reader->GetOutput();
	ImageType::RegionType region = image->GetLargestPossibleRegion();
	ImageType::SizeType size = region.GetSize();
	SpacingType spacing = image->GetSpacing();

	SizeType m_radius;
	for (unsigned int i = 0; i < Dimension; ++i){
		m_radius[i] = static_cast<SizeValueType>( radius/spacing[i] );
	}
	std::cout << "m_radius: " << m_radius << "\n";

	WhiteHatFilterType::Pointer hatFilter = WhiteHatFilterType::New();
	hatFilter->SetInput( reader->GetOutput() );
	hatFilter->SetRadius( m_radius );
	hatFilter->SetAlgorithm( algorithm );
	// hatFilter->ForceAlgorithmOn();
	// hatFilter->SafeBorderOn();
	hatFilter->Update();

	///////////////////////////////////////////

	//Setting up the output writer
  	using WriterType = itk::ImageFileWriter< ImageType >;//setting up type for writer
  	WriterType::Pointer writer = WriterType::New();//initialize new writer pointer
  	writer->SetFileName( outputFileName );//set filename for writer
  	writer->SetInput( hatFilter->GetOutput() );//
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
				const unsigned int &algorithm){
	std::string OutputFileName = "../output/";
	OutputFileName.append(filename);
	OutputFileName.append("_WhiteHat").append("_");
	OutputFileName.append(std::to_string(algorithm));
	OutputFileName.append(filetype);
	return OutputFileName;
}



