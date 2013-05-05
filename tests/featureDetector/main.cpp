#include <cvt/io/Camera.h>
#include <cvt/io/VideoReader.h>
#include <cvt/io/ImageSequence.h>
#include <cvt/util/String.h>
#include <cvt/util/Exception.h>

#include <cvt/gui/Application.h>
#include "FeatureApp.h"

using namespace cvt;

Camera* initCamera()
{
    Camera::updateInfo();
	size_t numCams = Camera::count();

	std::cout << "Overall number of Cameras: " << numCams << std::endl;
	if( numCams == 0 ){
		std::cout << "Please connect a camera!" << std::endl;
		return 0;
	}

	for( size_t i = 0; i < numCams; i++ ){
		const CameraInfo & info = Camera::info( i );
		std::cout << "Camera " << i << ": " << info << std::endl;
	}

	size_t selection = numCams;
    if( numCams == 1 ){
        selection = 0;
    } else {
        std::cout << "Select camera: ";
        std::cin >> selection;
        while ( selection >= numCams ){
            std::cout << "Index out of bounds -> select camera in Range:";
            std::cin >> selection;
        }
    }

    Camera * cam = 0;
    cam = Camera::get( selection, 640, 480, 60, IFormat::RGBA_UINT8 );
    cam->startCapture();

    return cam;
}

int main( int argc, char* argv[] )
{
    VideoInput * input = 0;
	if( argc == 1 ){
        input = initCamera();
    }

//	try {
		FeatureApp app( *input );
		Application::run();
//	} catch( cvt::Exception e ) {
//		std::cout << e.what() << std::endl;
//	}

    if( input )
		delete input;

	return 0;
}