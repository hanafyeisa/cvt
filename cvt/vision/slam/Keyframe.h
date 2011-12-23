#ifndef CVT_KEYFRAME_H
#define CVT_KEYFRAME_H

#include <Eigen/Core>
#include <map>

#include <cvt/math/SE3.h>
#include <cvt/vision/slam/MapMeasurement.h>
#include <cvt/util/String.h>

namespace cvt
{
	class Keyframe
	{
		public:
			typedef std::pair<size_t, MapMeasurement> MapPairType;
			typedef std::map<size_t, MapMeasurement, std::less<size_t>, Eigen::aligned_allocator<MapPairType> > MapType;
			typedef MapType::const_iterator MeasurementIterator;

			Keyframe( const Eigen::Matrix4d& pose );

			void					addFeature( const MapMeasurement & f, size_t id );

			size_t					numMeasurements()				const	{ return _featMeas.size(); }
			const MapMeasurement&	measurementForId( size_t id  )  const; 

			const SE3<double>&		pose()							const	{ return _pose; }	
			void					setPose( const Eigen::Matrix4d & pose ) { _pose.set( pose ); }
			void					updatePose( const Eigen::Matrix<double, 6, 1> & deltaCam ) { _pose.apply( deltaCam ); }

			// distance measure of this keyframe to a given transform
			double					distance( const Eigen::Matrix4d & transform ) const;

			MeasurementIterator		measurementsBegin() const { return _featMeas.begin(); }
			MeasurementIterator		measurementsEnd()   const { return _featMeas.end(); }

		private:
			SE3<double>	_pose;

			// 2d meas of 3d feat with id
			MapType		_featMeas;
	};

	inline void Keyframe::addFeature( const MapMeasurement & f, size_t id )
	{
		_featMeas.insert( std::pair<size_t, MapMeasurement>( id, f ) );
	}

	inline const MapMeasurement& Keyframe::measurementForId( size_t id  )  const
   	{ 
		MeasurementIterator iter = _featMeas.find( id );
		/*if( iter == _featMeas.end() ){
			cvt::String msg( "No measurement with id " );
			msg += id;

			throw CVTException( msg.c_str() );
		}*/
		return iter->second;
	}
}

#endif