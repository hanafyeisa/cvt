/*
   The MIT License (MIT)

   Copyright (c) 2011 - 2013, Philipp Heise and Sebastian Klose

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

/*
 * File:   SampleConsensusModel.h
 * Author: sebi, heise
 *
 * Created on July 19, 2011, 1:40 PM
 */

#ifndef CVT_SAMPLECONSENSUSMODEL_H
#define	CVT_SAMPLECONSENSUSMODEL_H

#include <vector>

namespace cvt
{
    /**
     * SampleConsensusModelTraits:
     * -> typedefs on ResultType and DistanceType
     */
    template<class T>
    struct SACModelTraits;

    template <typename Derived>
    class SampleConsensusModel
    {
      public:
        typedef typename SACModelTraits<Derived>::ResultType    ResultType;
        typedef typename SACModelTraits<Derived>::DistanceType  DistanceType;

        size_t size() const
        {
            return ( ( Derived *)this )->size();
        }

        size_t minSampleSize() const
        {
            return ( ( Derived *)this )->minSampleSize();
        }

        ResultType estimate( const std::vector<size_t> & sampleIndices ) const
        {
            return ( ( Derived *)this )->estimate( sampleIndices );
        }

        ResultType refine( const ResultType& res, const std::vector<size_t> & inliers  ) const
        {
            return ( ( Derived *)this )->refine( res, inliers );
        }

        void inliers( std::vector<size_t> & sampleIndices,
                      const ResultType & estimate,
                      const DistanceType maxDistance ) const
        {
            sampleIndices.clear();
            ( ( Derived *)this )->inliers( sampleIndices, estimate, maxDistance );
        }
    };
}

#endif

