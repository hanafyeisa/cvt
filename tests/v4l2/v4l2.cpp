#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <cvt/gfx/Image.h>
#include <cvt/io/V4L2Camera.h>
#include <cvt/util/Timer.h>

using namespace cvt;

int main(int argc, char* argv[])
{
	const Image* frame;
	V4L2Camera cam( 0, 640, 480, 30.0, CVT_GRAY );
	int key;
	size_t frames = 0;
	Timer timer;
	bool doprocess = true;
	Image x, y;
	Image kernel( 3, 1, CVT_GRAY, CVT_FLOAT );

	{
	    float* data;
	    data = ( float* ) kernel.data();
	    *data++ = 1.0f;
	    *data++ = 0.0f;
	    *data++ = -1.0f;
	}

	cam.open();
	cam.init();
	cam.captureStart();

	timer.reset();
	while( 1 ) {
	    cam.captureNext();
	    frame = cam.image();

	    if( doprocess ) {
		frame->convert( x, frame->order(), CVT_FLOAT );
		x.convolve( y, kernel );
		y = ( y + 1.0f ) * 0.5f;
	        cvShowImage( "V4L2", y.iplimage() );
	    } else
	        cvShowImage( "V4L2", frame->iplimage() );

	    key = cvWaitKey( 10 ) & 0xff;
	    if( key == 27 )
		break;
	    else if( key == ' ')
		doprocess = !doprocess;

	    frames++;
	    if( timer.elapsedSeconds() > 5.0f ) {
		std::cout << "FPS: " << ( double ) frames / timer.elapsedSeconds() << std::endl;
		frames = 0;
		timer.reset();
	    }
	}

	return 0;
}