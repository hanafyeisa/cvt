/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef IFILTERPARAMETERINFO_H
#define IFILTERPARAMETERINFO_H
#include <string>

namespace cvt {

	enum IFilterParameterType {
		IFILTERPARAMETER_SCALAR = 1,
		IFILTERPARAMETER_COLOR,
		IFILTERPARAMETER_IMAGE,
		IFILTERPARAMETER_VECTOR2,
		IFILTERPARAMETER_VECTOR4,
		IFILTERPARAMETER_VECTOR8,
		IFILTERPARAMETER_VECTOR16,
	};

	enum IFilterParameterDirection {
		IFILTERPARAMETER_IN = ( 1 << 0 ),
		IFILTERPARAMETER_OUT = ( 1 << 1 )
	};

	class IFilterParameterInfo
	{
		public:
			IFilterParameterInfo( const char* n, IFilterParameterType t, IFilterParameterDirection d = IFILTERPARAMETER_IN ) : name( n ), type( t ), dir( d ) {};

			IFilterParameterType getType( ) const { return type; };
			IFilterParameterDirection getDirection( ) const	{ return dir; };
			const char* getName( ) const { return name; };

		private:
			const char* name;
			IFilterParameterType type;
			IFilterParameterDirection dir;
	};

}
#endif
