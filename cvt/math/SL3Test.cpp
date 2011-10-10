//
//  SL3Test.cpp
//  CVTools
//
//  Created by Sebastian Klose on 08.02.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SL3Test.h"

#include <cvt/math/SL3.h>
#include <cvt/math/Math.h>
#include <cvt/math/Matrix.h>
#include <cvt/util/CVTTest.h>

#include <Eigen/Core>

namespace cvt {
    
	static bool testJacobian()
	{
		Eigen::Matrix<double, 8, 1> delta = Eigen::Matrix<double, 8, 1>::Zero();
		Eigen::Matrix<double, 3, 8> jNumeric, jAnalytic, jDiff;
		Eigen::Matrix<double, 2, 8> sJN, sJA, sJDiff;

		SL3<double> pose;
		pose.set( Math::deg2Rad( 10 ), Math::deg2Rad( -25 ), 0.76, 0.89, 10, -10, 0.0001, 0.0002 );

		Eigen::Matrix<double, 3, 1> point;
		Eigen::Matrix<double, 3, 1> p, pp;
		Eigen::Matrix<double, 2, 1> sp, spp;
		point[ 0 ] = 13; point[ 1 ] = 8; point[ 2 ] = 12;;

		pose.transform( p, point );
		pose.project( sp, point );

		double h = 0.000000001;
		for( size_t i = 0; i < 8; i++ ){
			delta[ i ] = h;

			pose.apply( delta );

			pose.transform( pp, point );
			jNumeric.col( i ) = ( pp - p ) / h;

			pose.project( spp, point );
			sJN.col( i ) = ( spp - sp ) / h;

			delta[ i ] = -h;
			pose.apply( delta );
			delta[ i ] = 0;
		}

		pose.jacobian( jAnalytic, point );
		pose.project( spp, sJA, point );

		bool b, ret = true;
		jDiff = jAnalytic - jNumeric;
		b = ( jDiff.array().abs().sum() / 24.0 ) < 0.00001;

		CVTTEST_PRINT( "Pose Jacobian", b );
		if( !b ){
			std::cout << "Analytic:\n" << jAnalytic << std::endl;
			std::cout << "Numeric:\n" << jNumeric << std::endl;
			std::cout << "Difference:\n" << jDiff << std::endl;
		}
		ret &= b;

		sJDiff = sJA - sJN;
		b = ( sJDiff.array().abs().sum() / 16.0 ) < 0.0001;
		CVTTEST_PRINT( "Screen Jacobian", b );
		if( !b ){
			std::cout << "Analytic:\n" << sJA << std::endl;
			std::cout << "Numeric:\n" << sJN << std::endl;
			std::cout << "Difference:\n" << sJDiff << std::endl;
			std::cout << "Avg. Diff: " << sJDiff.array().abs().sum() / 16.0 << std::endl;
		}
		ret &= b;

		return ret;
	}
    
    static bool testScreenHessian()
    {        
        Eigen::Matrix<double, 8, 1> delta = Eigen::Matrix<double, 8, 1>::Zero();        
		Eigen::Matrix<double, 8, 8> shNumericX, shNumericY, shX, shY;
        
		SL3<double> pose;
		pose.set( Math::deg2Rad( 10 ), Math::deg2Rad( -25 ), 0.76, 0.89, 10, -10, 0.0001, 0.0002 );
        
		Eigen::Matrix<double, 3, 1> point;
		Eigen::Matrix<double, 2, 1> sp, ff, fb, bf, bb, xxf, xxb, hess;
		point[ 0 ] = 13; point[ 1 ] = 8; point[ 2 ] = 13;
        
        // project the point with current parameters
		pose.project( sp, point );
        
		double h = 0.001;
		for( size_t i = 0; i < 8; i++ ){
            for( size_t j = 0; j < 8; j++ ){

				if( i == j ){
					// +
					delta[ j ] = h;
					pose.apply( delta );
					pose.project( xxf, point );
					delta[ j ] = -2 * h;
					pose.apply( delta );
					pose.project( xxb, point );

					hess = ( xxb - 2 * sp + xxf ) / ( h*h );
					
					// back to start
					delta[ j ] = h;
					pose.apply( delta );
					delta[ j ] = 0;
				} else {
					delta[ i ] = h;
					delta[ j ] = h;
					pose.apply( delta );
					pose.project( ff, point );
					pose.apply( -delta );

					delta[ i ] = h;
					delta[ j ] = -h;
					pose.apply( delta );
					pose.project( fb, point );
					pose.apply( -delta );

					delta[ i ] = -h;
					delta[ j ] =  h;
					pose.apply( delta );
					pose.project( bf, point );
					pose.apply( -delta );
					
					delta[ i ] = -h;
					delta[ j ] = -h;
					pose.apply( delta );
					pose.project( bb, point );
					pose.apply( -delta );

					hess = ( ff - bf - fb + bb ) / ( 4 * h * h );
					delta.setZero();
				}

                shNumericX( i, j ) = hess[ 0 ];
                shNumericY( i, j ) = hess[ 1 ];
                
            }
		}
        
		pose.screenHessian( shX, shY, sp );
        
		bool b, ret = true;
        Eigen::Matrix<double, 8, 8> jDiff;
        jDiff = shNumericX - shX;
		b = ( jDiff.array().abs().sum() / 64.0 ) < 0.00001;
        
		CVTTEST_PRINT( "Pose ScreenHessian X", b );
		if( !b ){
			std::cout << "Analytic:\n" << shX << std::endl;
			std::cout << "Numeric:\n" << shNumericX << std::endl;
			std::cout << "Difference:\n" << jDiff << std::endl;
		}
		ret &= b;
        
        jDiff = shNumericY - shY;
		b = ( jDiff.array().abs().sum() / 64.0 ) < 0.00001;
        
		CVTTEST_PRINT( "Pose ScreenHessian Y", b );
		if( !b ){
			std::cout << "Analytic:\n" << shY << std::endl;
			std::cout << "Numeric:\n" << shNumericY << std::endl;
			std::cout << "Difference:\n" << jDiff << std::endl;
		}
		ret &= b;
        
        return ret;
    }

    static bool testMatrices( const Eigen::Matrix3d & m1, const Matrix3d & m2 )
    {
        for ( size_t i = 0; i < 3; i++ ) {
            for ( size_t k = 0; k < 3; k++ ) {
                if ( Math::abs( m1( i, k ) - m2[ i ][ k ] ) > 0.00001 ) {
                    return false;
                }
            }
        }
        return true;
    }

    static bool testSet()
    {
        bool result = true;

        SL3<double> pose;
        Matrix3d H;

        pose.set( 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 );
        H.setHomography( 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 );

        result &= testMatrices( pose.transformation(), H );

        return result;
    }

BEGIN_CVTTEST( SL3 )
	bool ret = true;

	SL3<double> pose;
	bool b = true;
	b = ( pose.transformation() == Eigen::Matrix<double, 3, 3>::Identity() );

	CVTTEST_PRINT( "Initialization", b );
	ret &= b;

    b = testSet();
    CVTTEST_PRINT( "SL3::set( ... )", b );
	ret &= b;

	ret &= testJacobian();
    ret &= testScreenHessian();

	return ret;
END_CVTTEST

}
