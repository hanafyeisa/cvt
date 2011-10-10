/*
 *  SL3Transform.h
 *  CVTools
 *
 *  Created by Sebastian Klose on 08.10.10.
 *  Copyright 2010. All rights reserved.
 *
 */

#ifndef CVT_SL3_H
#define CVT_SL3_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cvt/math/Math.h>
#include <vector>

namespace cvt {
	template <typename T>
	class SL3
	{
		typedef Eigen::Matrix<T, 3, 3> MatrixType;
		typedef Eigen::Matrix<T, 3, 8> JacMatType;
		typedef Eigen::Matrix<T, 2, 8> ScreenJacType;
		typedef Eigen::Matrix<T, 8, 8> ScreenHessType;
		typedef Eigen::Matrix<T, 8, 1> ParameterVectorType;
		typedef Eigen::Matrix<T, 3, 1> PointType;

		public:
			SL3();
			~SL3(){};

			/* set: angles in radians! */
			void set( T alpha, T phi, T sx, T sy, T tx, T ty, T v0, T v1 );

			/**
			 *	\brief apply delta parameters 
			 *	\param	delta	the delta to apply
			 *	\desc	forward update of pose: T( delta ) * T( current )
			 */
			void apply( const ParameterVectorType & delta );

			/**
			 *	\brief	apply delta parameters in inverse compositional way 
			 *	\param	delta	the delta to apply
			 *	\desc	This is meant for usage in inverse compositional approaches,
			 *			where the current pose represents the transformation from the
			 *			model to the object, but the delta parameters have been estimated
			 *			in the model coords:
			 *			T(delta) * p_model = inv(T(current)) * p_current
			 *			To update T(current), we need the following:
			 *			p_model = inv( T( delta ) ) * inv(T( current ))
			 *			so the update becomes T(current) = T(current) * T(delta)
			 */
			void applyInverse( const ParameterVectorType & delta );

			/* transform the point */
			void transform( PointType & warped, const PointType & p ) const;

			/* get the jacobian at a certain point */
			void jacobian( JacMatType & J, const PointType & p ) const;

			/* sp = proj( transform( p ) ) */
			void project( Eigen::Matrix<T, 2, 1> & sp, const PointType & p ) const;

			/* sp = proj( transform( p ) ), J = d proj( transform( p ) ) / d params */
			void project( Eigen::Matrix<T, 2, 1> & sp, ScreenJacType & J, const PointType & p ) const;

			/* p is already transformed with the current T in this case, but not yet projected! */
			void jacobianAroundT( JacMatType & J, const PointType & p ) const;

			/* sp is a screen point (transformed with current) */
			void screenJacobian( ScreenJacType & J, const Eigen::Matrix<T, 2, 1> & sp ) const;

			void screenHessian( ScreenHessType & wx, 
								ScreenHessType & wy,
							    const Eigen::Matrix<T, 2, 1> & sp ) const;

			/* get back the currently stored transformation matrix */
			const MatrixType & transformation() const { return _current; }

		private:
			MatrixType		_current;
	};

	template < typename T >
	inline SL3<T>::SL3() : _current( MatrixType::Identity() )
	{
	}

	template < typename T>
	inline void SL3<T>::set( T alpha, T phi, T sx, T sy, T tx, T ty, T v0, T v1 )
	{
        Eigen::Transform<T, 2, Eigen::Affine> transform;
        Eigen::Matrix<T, 2, 1> s( sx, sy );

        transform.setIdentity();

        transform.rotate( alpha ).rotate( -phi ).scale( s ).rotate( phi );

        const Eigen::Matrix<T, 3, 3> & affine = transform.matrix();

		_current( 0, 0 ) = affine( 0, 0 ); _current( 0, 1 ) = affine( 0, 1 ); _current( 0, 2 ) = tx;
		_current( 1, 0 ) = affine( 1, 0 ); _current( 1, 1 ) = affine( 1, 1 ); _current( 1, 2 ) = ty;
		_current( 2, 0 ) = v0; _current( 2, 1 ) = v1; _current( 2, 2 ) = 1.0f;
	}

	template < typename T >
	inline void SL3<T>::apply( const ParameterVectorType & delta )
	{
		MatrixType m;

		m( 0, 0 ) = delta[ 4 ];
		m( 0, 1 ) = delta[ 2 ];
		m( 0, 2 ) = delta[ 0 ];

		m( 1, 0 ) = delta[ 3 ];
		m( 1, 1 ) = -delta[ 4 ] - delta[5];
		m( 1, 2 ) = delta[ 1 ];

		m( 2, 0 ) = delta[ 6 ];
		m( 2, 1 ) = delta[ 7 ];
		m( 2, 2 ) = delta[ 5 ];

		/* m = exp( m ) */
		cvt::Math::exponential( m, m );

		/* update the current transformation */
		_current = m * _current;
		//_current *= m;
	}

	template <typename T>
	inline void SL3<T>::applyInverse( const ParameterVectorType & delta )
	{
		MatrixType m;

		m( 0, 0 ) = delta[ 4 ];
		m( 0, 1 ) = delta[ 2 ];
		m( 0, 2 ) = delta[ 0 ];

		m( 1, 0 ) = delta[ 3 ];
		m( 1, 1 ) = -delta[ 4 ] - delta[5];
		m( 1, 2 ) = delta[ 1 ];

		m( 2, 0 ) = delta[ 6 ];
		m( 2, 1 ) = delta[ 7 ];
		m( 2, 2 ) = delta[ 5 ];

		/* m = exp( m ) */
		cvt::Math::exponential( m, m );

		/* update current in the inverse fashion */
		_current *= m;
	}

	template < typename T >
	inline void SL3<T>::transform( PointType & warped, const PointType & p ) const
	{
		warped = _current * p;
	}

	template < typename T >
	inline void SL3<T>::jacobianAroundT( JacMatType & J, const PointType & p ) const
	{
		J( 0, 0 ) = p[ 2 ];
		J( 1, 0 ) =    0  ;
		J( 2, 0 ) =    0  ;

		J( 0, 1 ) =	   0  ;
		J( 1, 1 ) = p[ 2 ];
		J( 2, 1 ) =    0  ;

		J( 0, 2 ) =	p[ 1 ];
		J( 1, 2 ) =    0  ;
		J( 2, 2 ) =    0  ;

		J( 0, 3 ) =	   0  ;
		J( 1, 3 ) = p[ 0 ];
		J( 2, 3 ) =    0  ;

		J( 0, 4 ) =	 p[ 0 ];
		J( 1, 4 ) = -p[ 1 ];
		J( 2, 4 ) =     0  ;

		J( 0, 5 ) =	    0  ;
		J( 1, 5 ) = -p[ 1 ];
		J( 2, 5 ) =  p[ 2 ];

		J( 0, 6 ) =	   0  ;
		J( 1, 6 ) =    0  ;
		J( 2, 6 ) = p[ 0 ];

		J( 0, 7 ) =	   0  ;
		J( 1, 7 ) =    0  ;
		J( 2, 7 ) = p[ 1 ];
	}

	template < typename T >
	inline void SL3<T>::jacobian( JacMatType & J, const PointType & p ) const
	{
		PointType pp = _current * p;
		jacobianAroundT( J, pp );
	}

	template < typename T >
	inline void SL3<T>::project( Eigen::Matrix<T, 2, 1> & sp, const PointType & p ) const
	{
		PointType pp = _current * p;

		sp[ 0 ] = pp[ 0 ] / pp[ 2 ];
		sp[ 1 ] = pp[ 1 ] / pp[ 2 ];
	}

	template < typename T >
	inline void SL3<T>::project( Eigen::Matrix<T, 2, 1> & sp, ScreenJacType & J, const PointType & p ) const
	{
		project( sp, p );
		screenJacobian( J, sp );
	}

	template < typename T >
	inline void SL3<T>::screenJacobian( ScreenJacType & J, const Eigen::Matrix<T, 2, 1> & sp ) const
	{
		J( 0, 0 ) = 1; J( 0, 1 ) = 0; J( 0, 2 ) = sp[ 1 ]; J( 0, 3 ) = 0; J( 0, 4 ) = sp[ 0 ]; J( 0, 5 ) = -sp[ 0 ]; J( 0, 6 ) = -sp[ 0 ] * sp[ 0 ];J( 0, 7 ) = -sp[ 0 ] * sp[ 1 ];

		J( 1, 0 ) = 0;
		J( 1, 1 ) = 1;
		J( 1, 2 ) = 0;
		J( 1, 3 ) = sp[ 0 ];
		J( 1, 4 ) = -sp[ 1 ];
		J( 1, 5 ) = -2 * sp[ 1 ];
		J( 1, 6 ) = -sp[ 0 ] * sp[ 1 ];
		J( 1, 7 ) = -sp[ 1 ] * sp[ 1 ];
	}

	template <typename T>
	inline void SL3<T>::screenHessian( ScreenHessType & wx, 
									   ScreenHessType & wy,
									   const Eigen::Matrix<T, 2, 1> & sp ) const
	{
		T x = sp[ 0 ];
		T y = sp[ 1 ];

		T xx = x * x;
		T xxx = xx * x;
		T xxy = xx * y;
		T xy = x * y;
		T yy = y * y;
		T yyy = yy * y;
		T yyx = yy * x;

		wx <<
		0,0,0,0,1,-1,-2*x,-y
		,0,0,1,0,0,0,0,-x
		,0,0,0,0,y,-y,-2*xy,-yy
		,0,0,x,0,0,0,0,-xx
		,0,0,-y,0,x,-x,-2*xx,0
		,0,0,-2*y,0,-x,x,2*xx,3*xy
		,0,0,-xy,0,-xx,xx,2*xxx,2*xxy
		,0,0,-yy,0,-xy,xy,2*xxy,2*yyx;

		wy <<
		0,0,0,1,0,0,-y,0
		,0,0,0,0,-1,-2,-x,-2*y
		,0,0,0,y,0,0,-yy,0
		,0,0,0,0,-x,-2*x,-xx,-2*xy
		,0,0,0,x,y,2*y,0,2*yy
		,0,0,0,-x,2*y,4*y,3*xy,4*yy
		,0,0,0,-xx,xy,2*xy,2*xxy,2*yyx
		,0,0,0,-xy,yy,2*yy,2*yyx,2*yyy;
	}
}

#endif

