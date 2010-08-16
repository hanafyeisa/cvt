#include "gfx/Image.h"
#include "math/Math.h"
#include "util/SIMD.h"
#include "util/CVTException.h"

namespace cvt {

    static size_t _type_size[] = {
			    sizeof( uint8_t ), /* CVT_UBYTE */
			    sizeof( float )    /* CVT_FLOAT */
			  };

    static size_t _order_channels[ ] = {
				    1, /* CVT_GRAY */
				    2, /* CVT_GRAYALPHA */
				    4, /* CVT_RGBA */
				    4  /* CVT_BGRA */
				};

    Image::Image( size_t w, size_t h, ImageChannelOrder order, ImageChannelType type ) :  _order( order ), _type( type ), _width( w ), _height( h ), _data( 0 ), _iplimage( 0 )
    {

	_stride = Math::pad16( _width ) * _order_channels[ _order ] * _type_size[ _type ];
	posix_memalign( ( void** ) &_data, 16, _stride * _height );
	upateIpl();
    }


    Image::Image( const Image& img ) : _order( CVT_BGRA ), _type( CVT_UBYTE ), _width( 0 ), _height( 0 ), _data( 0 ), _iplimage( 0 )
    {
	copy( img );
    }


    void Image::reallocate( size_t w, size_t h, ImageChannelOrder order, ImageChannelType type )
    {
	if( _width == w && _height == h && _order == order && _type == type )
	    return;

	free( _data );
	_order = order;
	_type = type;
	_width = w;
	_height = h;
	_stride = Math::pad16( _width ) * _order_channels[ _order ] * _type_size[ _type ];
	posix_memalign( ( void** ) &_data, 16, _stride * _height );
	upateIpl();
    }

    void Image::copy( const Image& img )
    {
	reallocate( img._width, img._height, img._order, img._type );

	size_t cw = _width * _order_channels[ _order ] * _type_size[ _type ];
	size_t h = _height;
	uint8_t* dst = _data;
	uint8_t* src = img._data;

	while( h-- ) {
	    memcpy( dst, src, cw );
	    dst += _stride;
	    src += img._stride;
	}
    }


    void Image::upateIpl()
    {
	/* FIXME: only update data, do not reallocate header */
	if( _iplimage )
	    cvReleaseImageHeader( &_iplimage );
	_iplimage = cvCreateImageHeader( cvSize( ( int ) _width, ( int ) _height ),
					_type == CVT_UBYTE ? IPL_DEPTH_8U : IPL_DEPTH_32F, ( int ) _order_channels[ _order ] );
	cvSetData( _iplimage, _data, ( int ) _stride );
    }


    void Image::convert( Image& img, ImageChannelOrder order, ImageChannelType type ) const
    {
	SIMD* simd = SIMD::get();
	img.reallocate( _width, _height, order, type );

	if( order != _order )
	    throw CVTException( "Unimplemented" );
	/* same order - different type */
	if( _type == CVT_UBYTE && type == CVT_FLOAT ) {
	    uint8_t* src = _data;
	    uint8_t* dst = img._data;
	    size_t h = _height;

	    while( h-- ) {
		simd->conv_u8_to_f( ( float* ) dst, src, _width * _order_channels[ _order ] );
		src += _stride;
		dst += img._stride;
	    }
	} else if( _type == CVT_FLOAT && type == CVT_UBYTE ) {
	    uint8_t* src = _data;
	    uint8_t* dst = img._data;

	    size_t h = _height;
	    while( h-- ) {
		simd->conv_f_to_u8( dst, ( float* ) src, _width * _order_channels[ _order ] );
		src += _stride;
		dst += img._stride;
	    }
	}
    }

    Image::~Image()
    {
	if( _iplimage )
	    cvReleaseImageHeader( &_iplimage );
	free( _data );
    }

    void Image::fill( const Color& c )
    {
	size_t h;
	uint8_t* dst;
	SIMD* simd = SIMD::get();

	if( _type == CVT_UBYTE ) {
	    switch( _order ) {
		case CVT_GRAY:
		    {
			uint8_t v = ( uint8_t ) ( 255.0f * c.gray() );
			h = _height;
			dst = _data;
			while( h-- ) {
			    simd->set_value_u8( dst, _width, v );
			    dst += _stride;
			}
		    }
		    break;
		case CVT_GRAYALPHA:
		    {
			uint16_t v = ( ( uint16_t ) ( 255.0f * c.alpha() ) ) << 8;
			v |= ( ( uint16_t ) ( 255.0f * c.gray() ));
			h = _height;
			dst = _data;
			while( h-- ) {
			    simd->set_value_u16( ( uint16_t* ) dst, _width, v );
			    dst += _stride;
			}
		    }
		    break;
		case CVT_RGBA:
		    {
			uint32_t v = ( ( uint32_t ) ( 255.0f * c.gray() ) ) << 24;
			v |= ( ( uint32_t ) ( 255.0f * c.blue() ) ) << 16;
			v |= ( ( uint32_t ) ( 255.0f * c.green() ) ) << 8;
			v |= ( ( uint32_t ) ( 255.0f * c.red() ) );

			h = _height;
			dst = _data;
			while( h-- ) {
			    simd->set_value_u32( ( uint32_t* ) dst, _width, v );
			    dst += _stride;
			}
		    }
		    break;
		case CVT_BGRA:
		    {
			uint32_t v = ( ( uint32_t ) ( 255.0f * c.gray() ) ) << 24;
			v |= ( ( uint32_t ) ( 255.0f * c.red() ) ) << 16;
			v |= ( ( uint32_t ) ( 255.0f * c.green() ) ) << 8;
			v |= ( ( uint32_t ) ( 255.0f * c.blue() ) );

			h = _height;
			dst = _data;
			while( h-- ) {
			    simd->set_value_u32( ( uint32_t* ) dst, _width, v );
			    dst += _stride;
			}
		    }
		    break;
	    }
	} else
	    throw CVTException("Unimplemented");
    }

    Image& Image::operator=( const Color& c )
    {
	fill( c );
	return *this;
    }

    void Image::mul( float alpha )
    {
	SIMD* simd = SIMD::get();
	switch( _type ) {
	    case CVT_FLOAT:
		{
		    uint8_t* dst = _data;

		    size_t h = _height;
		    while( h-- ) {
			simd->mul_valuef( ( float* ) dst, ( float* ) dst, _width * _order_channels[ _order ], alpha );
			dst += _stride;
		    }
		}
		break;
	    default:
		throw CVTException("Unimplemented");

	}
    }
    void Image::mad( const Image& i, float alpha )
    {
	if( _width != i._width || _height != i._height ||
	   _type != i._type || _order != i._order )
	    throw CVTException("Image mismatch");

	SIMD* simd = SIMD::get();
	switch( _type ) {
	    case CVT_FLOAT:
		{
		    uint8_t* src = i._data;
		    uint8_t* dst = _data;

		    size_t h = _height;
		    while( h-- ) {
			simd->mul_valuef_add( ( float* ) dst, ( float* ) src, _width * _order_channels[ _order ], alpha );
			src += i._stride;
			dst += _stride;
		    }
		}
		break;
	    default:
		throw CVTException("Unimplemented");

	}
    }

    void Image::ddx( Image& dx, bool forward ) const
    {
	SIMD* simd = SIMD::get();

	dx.reallocate( *this );

	switch( _type ) {
	    case CVT_FLOAT:
		{
		    size_t h = _height;
		    uint8_t* dst = dx._data;
		    float* fdst;
		    uint8_t* src1 = _data;
		    uint8_t* src2 = _data + sizeof( float ) * _order_channels[ _order ];
		    size_t c = _order_channels[ _order ];
		    size_t i;
		    while( h-- ) {
			i = c;
			fdst = ( float* ) dst;
			if( !forward ) {
			    while( i-- )
				*fdst++ = 0.0f;
			}
			simd->sub( fdst, ( float* ) src1, ( float* ) src2, ( _width - 1 ) * _order_channels[ _order ] );
			if( forward ) {
			    fdst += ( _width - 1 ) * _order_channels[ _order ];
			    while( i-- )
				*fdst++ = 0.0f;
			}
			dst += dx._stride;
			src1 += _stride;
			src2 += _stride;
		    }
		}
		break;
	    default:
		throw CVTException("Unimplemented");
	}
    }

    void Image::ddy( Image& dy, bool forward ) const
    {
	SIMD* simd = SIMD::get();

	dy.reallocate( *this );

	switch( _type ) {
	    case CVT_FLOAT:
		{
		    size_t h = _height - 1;
		    uint8_t* dst = dy._data;
		    uint8_t* src1 = _data;
		    uint8_t* src2 = _data + _stride;
		    if( !forward ) {
			simd->set_value_f( ( float* ) dst, _width * _order_channels[ dy._order ], 0.0f );
			dst += dy._stride;
		    }
		    while( h-- ) {
			simd->sub( ( float* ) dst, ( float* ) src1, ( float* ) src2, _width * _order_channels[ dy._order ] );
			dst += dy._stride;
			src1 += _stride;
			src2 += _stride;
		    }
		    if( forward )
			simd->set_value_f( ( float* ) dst, _width * _order_channels[ dy._order ], 0.0f );
		}
		break;
	    default:
		throw CVTException("Unimplemented");
	}
    }


    std::ostream& operator<<(std::ostream &out, const Image &f)
    {
	out << "Size: " << f.width() << " x " << f.height() << " Channels: " << _order_channels[ f._order ] << " Stride: " << f.stride() << std::endl;
	return out;
    }

}
