#ifndef IFILTER_H
#define IFILTER_H

#include <stdint.h>
#include <string>
#include <cvt/util/ParamSet.h>

namespace cvt {
	enum IFilterType {
					   IFILTER_CPU = ( 1 << 0 ),
					   IFILTER_OPENGL = ( 1 << 1 ),
					   IFILTER_OPENCL = ( 1 << 2 )
					 };

	class IFilter {
		public:
			virtual ParamSet* parameterSet() const { return new ParamSet( _pinfo, _pinfosize ); };
			virtual void apply( const ParamSet* attribs, IFilterType iftype = IFILTER_CPU ) const = 0;
			uint32_t getIFilterType() const { return _iftype; };

		protected:
			IFilter( std::string name, ParamInfo** pinfo, size_t pinfosize, uint32_t ifiltertype ) : _iftype( ifiltertype ), _name( name ), _pinfo( pinfo ), _pinfosize( pinfosize ) {};
			virtual ~IFilter() {};

		private:
			IFilter( const IFilter& ifilter );
			IFilter& operator=( const IFilter& ifilter );

			uint32_t _iftype;
			std::string _name;
			ParamInfo** _pinfo;
			size_t _pinfosize;
	};

}

#endif
