/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#include <cvt/vision/FAST.h>

namespace cvt {

    /* calc the scores for all the corners */
	void FAST::score10( const Image & img, std::vector<Feature2Df> & corners, uint8_t threshold )
	{
        size_t stride;
        const uint8_t * p = img.map( &stride );

        int offsets[ 16 ];
        make_offsets( offsets, stride );

		for( size_t n = 0; n < corners.size(); n++ )
			corners[ n ].score = score10Pixel( p + (int)corners[ n ].pt.y * stride + (int)corners[ n ].pt.x, offsets, threshold );
        img.unmap( p );
	}

	int FAST::score10Pixel(const uint8_t* p, const int * offsets, uint8_t threshold )
	{
		int bmin = threshold;
		int bmax = 255;
		int b = (bmax + bmin)/2;

		/*Compute the score using binary search*/
		for(;;)
		{
			int cb = *p + b;
			int c_b= *p - b;


			if( p[ offsets[0] ] > cb)
				if( p[ offsets[1] ] > cb)
					if( p[ offsets[2] ] > cb)
						if( p[offsets[3]] > cb)
							if( p[offsets[4]] > cb)
								if( p[offsets[5]] > cb)
									if( p[offsets[6]] > cb)
										if( p[offsets[7]] > cb)
											if( p[offsets[8]] > cb)
												if( p[offsets[9]] > cb)
													goto is_a_corner;
												else
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else if( p[offsets[6]] < c_b)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else if( p[offsets[12]] < c_b)
											if( p[offsets[7]] < c_b)
												if( p[offsets[8]] < c_b)
													if( p[offsets[9]] < c_b)
														if( p[offsets[10]] < c_b)
															if( p[offsets[11]] < c_b)
																if( p[offsets[13]] < c_b)
																	if( p[offsets[14]] < c_b)
																		if( p[offsets[15]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
								else if( p[offsets[5]] < c_b)
									if( p[offsets[15]] > cb)
										if( p[offsets[11]] > cb)
											if( p[offsets[12]] > cb)
												if( p[offsets[13]] > cb)
													if( p[offsets[14]] > cb)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else if( p[offsets[11]] < c_b)
											if( p[offsets[6]] < c_b)
												if( p[offsets[7]] < c_b)
													if( p[offsets[8]] < c_b)
														if( p[offsets[9]] < c_b)
															if( p[offsets[10]] < c_b)
																if( p[offsets[12]] < c_b)
																	if( p[offsets[13]] < c_b)
																		if( p[offsets[14]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										if( p[offsets[6]] < c_b)
											if( p[offsets[7]] < c_b)
												if( p[offsets[8]] < c_b)
													if( p[offsets[9]] < c_b)
														if( p[offsets[10]] < c_b)
															if( p[offsets[11]] < c_b)
																if( p[offsets[12]] < c_b)
																	if( p[offsets[13]] < c_b)
																		if( p[offsets[14]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
								else
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else if( p[offsets[11]] < c_b)
										if( p[offsets[6]] < c_b)
											if( p[offsets[7]] < c_b)
												if( p[offsets[8]] < c_b)
													if( p[offsets[9]] < c_b)
														if( p[offsets[10]] < c_b)
															if( p[offsets[12]] < c_b)
																if( p[offsets[13]] < c_b)
																	if( p[offsets[14]] < c_b)
																		if( p[offsets[15]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
							else if( p[offsets[4]] < c_b)
								if( p[offsets[14]] > cb)
									if( p[offsets[10]] > cb)
										if( p[offsets[11]] > cb)
											if( p[offsets[12]] > cb)
												if( p[offsets[13]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	if( p[offsets[8]] > cb)
																		if( p[offsets[9]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else if( p[offsets[10]] < c_b)
										if( p[offsets[5]] < c_b)
											if( p[offsets[6]] < c_b)
												if( p[offsets[7]] < c_b)
													if( p[offsets[8]] < c_b)
														if( p[offsets[9]] < c_b)
															if( p[offsets[11]] < c_b)
																if( p[offsets[12]] < c_b)
																	if( p[offsets[13]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else if( p[offsets[14]] < c_b)
									if( p[offsets[6]] < c_b)
										if( p[offsets[7]] < c_b)
											if( p[offsets[8]] < c_b)
												if( p[offsets[9]] < c_b)
													if( p[offsets[10]] < c_b)
														if( p[offsets[11]] < c_b)
															if( p[offsets[12]] < c_b)
																if( p[offsets[13]] < c_b)
																	if( p[offsets[5]] < c_b)
																		goto is_a_corner;
																	else
																		if( p[offsets[15]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									if( p[offsets[5]] < c_b)
										if( p[offsets[6]] < c_b)
											if( p[offsets[7]] < c_b)
												if( p[offsets[8]] < c_b)
													if( p[offsets[9]] < c_b)
														if( p[offsets[10]] < c_b)
															if( p[offsets[11]] < c_b)
																if( p[offsets[12]] < c_b)
																	if( p[offsets[13]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
							else
								if( p[offsets[10]] > cb)
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	if( p[offsets[8]] > cb)
																		if( p[offsets[9]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else if( p[offsets[10]] < c_b)
									if( p[offsets[6]] < c_b)
										if( p[offsets[7]] < c_b)
											if( p[offsets[8]] < c_b)
												if( p[offsets[9]] < c_b)
													if( p[offsets[11]] < c_b)
														if( p[offsets[12]] < c_b)
															if( p[offsets[13]] < c_b)
																if( p[offsets[14]] < c_b)
																	if( p[offsets[5]] < c_b)
																		goto is_a_corner;
																	else
																		if( p[offsets[15]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
						else if( p[offsets[3]] < c_b)
							if( p[offsets[9]] > cb)
								if( p[offsets[10]] > cb)
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	if( p[offsets[8]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	if( p[offsets[8]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else if( p[offsets[9]] < c_b)
								if( p[offsets[6]] < c_b)
									if( p[offsets[7]] < c_b)
										if( p[offsets[8]] < c_b)
											if( p[offsets[10]] < c_b)
												if( p[offsets[11]] < c_b)
													if( p[offsets[12]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[4]] < c_b)
																goto is_a_corner;
															else
																if( p[offsets[13]] < c_b)
																	if( p[offsets[14]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
														else
															if( p[offsets[13]] < c_b)
																if( p[offsets[14]] < c_b)
																	if( p[offsets[15]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							if( p[offsets[9]] > cb)
								if( p[offsets[10]] > cb)
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	if( p[offsets[8]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	if( p[offsets[8]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else if( p[offsets[9]] < c_b)
								if( p[offsets[6]] < c_b)
									if( p[offsets[7]] < c_b)
										if( p[offsets[8]] < c_b)
											if( p[offsets[10]] < c_b)
												if( p[offsets[11]] < c_b)
													if( p[offsets[12]] < c_b)
														if( p[offsets[13]] < c_b)
															if( p[offsets[5]] < c_b)
																if( p[offsets[4]] < c_b)
																	goto is_a_corner;
																else
																	if( p[offsets[14]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
															else
																if( p[offsets[14]] < c_b)
																	if( p[offsets[15]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
					else if( p[offsets[2]] < c_b)
						if( p[offsets[8]] > cb)
							if( p[offsets[9]] > cb)
								if( p[offsets[10]] > cb)
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] > cb)
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else if( p[offsets[8]] < c_b)
							if( p[offsets[6]] < c_b)
								if( p[offsets[7]] < c_b)
									if( p[offsets[9]] < c_b)
										if( p[offsets[10]] < c_b)
											if( p[offsets[11]] < c_b)
												if( p[offsets[5]] < c_b)
													if( p[offsets[4]] < c_b)
														if( p[offsets[3]] < c_b)
															goto is_a_corner;
														else
															if( p[offsets[12]] < c_b)
																if( p[offsets[13]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
													else
														if( p[offsets[12]] < c_b)
															if( p[offsets[13]] < c_b)
																if( p[offsets[14]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[12]] < c_b)
														if( p[offsets[13]] < c_b)
															if( p[offsets[14]] < c_b)
																if( p[offsets[15]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else
						if( p[offsets[8]] > cb)
							if( p[offsets[9]] > cb)
								if( p[offsets[10]] > cb)
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] > cb)
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																if( p[offsets[7]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else if( p[offsets[8]] < c_b)
							if( p[offsets[6]] < c_b)
								if( p[offsets[7]] < c_b)
									if( p[offsets[9]] < c_b)
										if( p[offsets[10]] < c_b)
											if( p[offsets[11]] < c_b)
												if( p[offsets[12]] < c_b)
													if( p[offsets[5]] < c_b)
														if( p[offsets[4]] < c_b)
															if( p[offsets[3]] < c_b)
																goto is_a_corner;
															else
																if( p[offsets[13]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
														else
															if( p[offsets[13]] < c_b)
																if( p[offsets[14]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
													else
														if( p[offsets[13]] < c_b)
															if( p[offsets[14]] < c_b)
																if( p[offsets[15]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
				else if( p[offsets[1]] < c_b)
					if( p[offsets[7]] > cb)
						if( p[offsets[8]] > cb)
							if( p[offsets[9]] > cb)
								if( p[offsets[10]] > cb)
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] > cb)
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[2]] > cb)
												if( p[offsets[3]] > cb)
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else if( p[offsets[7]] < c_b)
						if( p[offsets[6]] < c_b)
							if( p[offsets[8]] < c_b)
								if( p[offsets[9]] < c_b)
									if( p[offsets[10]] < c_b)
										if( p[offsets[5]] < c_b)
											if( p[offsets[4]] < c_b)
												if( p[offsets[3]] < c_b)
													if( p[offsets[2]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[11]] < c_b)
															if( p[offsets[12]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[11]] < c_b)
														if( p[offsets[12]] < c_b)
															if( p[offsets[13]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[11]] < c_b)
													if( p[offsets[12]] < c_b)
														if( p[offsets[13]] < c_b)
															if( p[offsets[14]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[11]] < c_b)
												if( p[offsets[12]] < c_b)
													if( p[offsets[13]] < c_b)
														if( p[offsets[14]] < c_b)
															if( p[offsets[15]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else
						goto is_not_a_corner;
				else
					if( p[offsets[7]] > cb)
						if( p[offsets[8]] > cb)
							if( p[offsets[9]] > cb)
								if( p[offsets[10]] > cb)
									if( p[offsets[11]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[13]] > cb)
												if( p[offsets[14]] > cb)
													if( p[offsets[15]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] > cb)
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[2]] > cb)
												if( p[offsets[3]] > cb)
													if( p[offsets[4]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[6]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else if( p[offsets[7]] < c_b)
						if( p[offsets[6]] < c_b)
							if( p[offsets[8]] < c_b)
								if( p[offsets[9]] < c_b)
									if( p[offsets[10]] < c_b)
										if( p[offsets[11]] < c_b)
											if( p[offsets[5]] < c_b)
												if( p[offsets[4]] < c_b)
													if( p[offsets[3]] < c_b)
														if( p[offsets[2]] < c_b)
															goto is_a_corner;
														else
															if( p[offsets[12]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
													else
														if( p[offsets[12]] < c_b)
															if( p[offsets[13]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[12]] < c_b)
														if( p[offsets[13]] < c_b)
															if( p[offsets[14]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[12]] < c_b)
													if( p[offsets[13]] < c_b)
														if( p[offsets[14]] < c_b)
															if( p[offsets[15]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else
						goto is_not_a_corner;
			else if( p[offsets[0]] < c_b)
				if( p[offsets[1]] > cb)
					if( p[offsets[7]] > cb)
						if( p[offsets[6]] > cb)
							if( p[offsets[8]] > cb)
								if( p[offsets[9]] > cb)
									if( p[offsets[10]] > cb)
										if( p[offsets[5]] > cb)
											if( p[offsets[4]] > cb)
												if( p[offsets[3]] > cb)
													if( p[offsets[2]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[11]] > cb)
															if( p[offsets[12]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[11]] > cb)
														if( p[offsets[12]] > cb)
															if( p[offsets[13]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[11]] > cb)
													if( p[offsets[12]] > cb)
														if( p[offsets[13]] > cb)
															if( p[offsets[14]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[11]] > cb)
												if( p[offsets[12]] > cb)
													if( p[offsets[13]] > cb)
														if( p[offsets[14]] > cb)
															if( p[offsets[15]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else if( p[offsets[7]] < c_b)
						if( p[offsets[8]] < c_b)
							if( p[offsets[9]] < c_b)
								if( p[offsets[10]] < c_b)
									if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] < c_b)
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[2]] < c_b)
												if( p[offsets[3]] < c_b)
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else
						goto is_not_a_corner;
				else if( p[offsets[1]] < c_b)
					if( p[offsets[2]] > cb)
						if( p[offsets[8]] > cb)
							if( p[offsets[6]] > cb)
								if( p[offsets[7]] > cb)
									if( p[offsets[9]] > cb)
										if( p[offsets[10]] > cb)
											if( p[offsets[11]] > cb)
												if( p[offsets[5]] > cb)
													if( p[offsets[4]] > cb)
														if( p[offsets[3]] > cb)
															goto is_a_corner;
														else
															if( p[offsets[12]] > cb)
																if( p[offsets[13]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
													else
														if( p[offsets[12]] > cb)
															if( p[offsets[13]] > cb)
																if( p[offsets[14]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[12]] > cb)
														if( p[offsets[13]] > cb)
															if( p[offsets[14]] > cb)
																if( p[offsets[15]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else if( p[offsets[8]] < c_b)
							if( p[offsets[9]] < c_b)
								if( p[offsets[10]] < c_b)
									if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] < c_b)
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else if( p[offsets[2]] < c_b)
						if( p[offsets[3]] > cb)
							if( p[offsets[9]] > cb)
								if( p[offsets[6]] > cb)
									if( p[offsets[7]] > cb)
										if( p[offsets[8]] > cb)
											if( p[offsets[10]] > cb)
												if( p[offsets[11]] > cb)
													if( p[offsets[12]] > cb)
														if( p[offsets[5]] > cb)
															if( p[offsets[4]] > cb)
																goto is_a_corner;
															else
																if( p[offsets[13]] > cb)
																	if( p[offsets[14]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
														else
															if( p[offsets[13]] > cb)
																if( p[offsets[14]] > cb)
																	if( p[offsets[15]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else if( p[offsets[9]] < c_b)
								if( p[offsets[10]] < c_b)
									if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	if( p[offsets[8]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	if( p[offsets[8]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else if( p[offsets[3]] < c_b)
							if( p[offsets[4]] > cb)
								if( p[offsets[14]] > cb)
									if( p[offsets[6]] > cb)
										if( p[offsets[7]] > cb)
											if( p[offsets[8]] > cb)
												if( p[offsets[9]] > cb)
													if( p[offsets[10]] > cb)
														if( p[offsets[11]] > cb)
															if( p[offsets[12]] > cb)
																if( p[offsets[13]] > cb)
																	if( p[offsets[5]] > cb)
																		goto is_a_corner;
																	else
																		if( p[offsets[15]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else if( p[offsets[14]] < c_b)
									if( p[offsets[10]] > cb)
										if( p[offsets[5]] > cb)
											if( p[offsets[6]] > cb)
												if( p[offsets[7]] > cb)
													if( p[offsets[8]] > cb)
														if( p[offsets[9]] > cb)
															if( p[offsets[11]] > cb)
																if( p[offsets[12]] > cb)
																	if( p[offsets[13]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else if( p[offsets[10]] < c_b)
										if( p[offsets[11]] < c_b)
											if( p[offsets[12]] < c_b)
												if( p[offsets[13]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	if( p[offsets[8]] < c_b)
																		if( p[offsets[9]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									if( p[offsets[5]] > cb)
										if( p[offsets[6]] > cb)
											if( p[offsets[7]] > cb)
												if( p[offsets[8]] > cb)
													if( p[offsets[9]] > cb)
														if( p[offsets[10]] > cb)
															if( p[offsets[11]] > cb)
																if( p[offsets[12]] > cb)
																	if( p[offsets[13]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
							else if( p[offsets[4]] < c_b)
								if( p[offsets[5]] > cb)
									if( p[offsets[15]] < c_b)
										if( p[offsets[11]] > cb)
											if( p[offsets[6]] > cb)
												if( p[offsets[7]] > cb)
													if( p[offsets[8]] > cb)
														if( p[offsets[9]] > cb)
															if( p[offsets[10]] > cb)
																if( p[offsets[12]] > cb)
																	if( p[offsets[13]] > cb)
																		if( p[offsets[14]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else if( p[offsets[11]] < c_b)
											if( p[offsets[12]] < c_b)
												if( p[offsets[13]] < c_b)
													if( p[offsets[14]] < c_b)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										if( p[offsets[6]] > cb)
											if( p[offsets[7]] > cb)
												if( p[offsets[8]] > cb)
													if( p[offsets[9]] > cb)
														if( p[offsets[10]] > cb)
															if( p[offsets[11]] > cb)
																if( p[offsets[12]] > cb)
																	if( p[offsets[13]] > cb)
																		if( p[offsets[14]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
								else if( p[offsets[5]] < c_b)
									if( p[offsets[6]] > cb)
										if( p[offsets[12]] > cb)
											if( p[offsets[7]] > cb)
												if( p[offsets[8]] > cb)
													if( p[offsets[9]] > cb)
														if( p[offsets[10]] > cb)
															if( p[offsets[11]] > cb)
																if( p[offsets[13]] > cb)
																	if( p[offsets[14]] > cb)
																		if( p[offsets[15]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else if( p[offsets[6]] < c_b)
										if( p[offsets[7]] < c_b)
											if( p[offsets[8]] < c_b)
												if( p[offsets[9]] < c_b)
													goto is_a_corner;
												else
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
								else
									if( p[offsets[11]] > cb)
										if( p[offsets[6]] > cb)
											if( p[offsets[7]] > cb)
												if( p[offsets[8]] > cb)
													if( p[offsets[9]] > cb)
														if( p[offsets[10]] > cb)
															if( p[offsets[12]] > cb)
																if( p[offsets[13]] > cb)
																	if( p[offsets[14]] > cb)
																		if( p[offsets[15]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
							else
								if( p[offsets[10]] > cb)
									if( p[offsets[6]] > cb)
										if( p[offsets[7]] > cb)
											if( p[offsets[8]] > cb)
												if( p[offsets[9]] > cb)
													if( p[offsets[11]] > cb)
														if( p[offsets[12]] > cb)
															if( p[offsets[13]] > cb)
																if( p[offsets[14]] > cb)
																	if( p[offsets[5]] > cb)
																		goto is_a_corner;
																	else
																		if( p[offsets[15]] > cb)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else if( p[offsets[10]] < c_b)
									if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	if( p[offsets[8]] < c_b)
																		if( p[offsets[9]] < c_b)
																			goto is_a_corner;
																		else
																			goto is_not_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
						else
							if( p[offsets[9]] > cb)
								if( p[offsets[6]] > cb)
									if( p[offsets[7]] > cb)
										if( p[offsets[8]] > cb)
											if( p[offsets[10]] > cb)
												if( p[offsets[11]] > cb)
													if( p[offsets[12]] > cb)
														if( p[offsets[13]] > cb)
															if( p[offsets[5]] > cb)
																if( p[offsets[4]] > cb)
																	goto is_a_corner;
																else
																	if( p[offsets[14]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
															else
																if( p[offsets[14]] > cb)
																	if( p[offsets[15]] > cb)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else if( p[offsets[9]] < c_b)
								if( p[offsets[10]] < c_b)
									if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	if( p[offsets[8]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	if( p[offsets[8]] < c_b)
																		goto is_a_corner;
																	else
																		goto is_not_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
					else
						if( p[offsets[8]] > cb)
							if( p[offsets[6]] > cb)
								if( p[offsets[7]] > cb)
									if( p[offsets[9]] > cb)
										if( p[offsets[10]] > cb)
											if( p[offsets[11]] > cb)
												if( p[offsets[12]] > cb)
													if( p[offsets[5]] > cb)
														if( p[offsets[4]] > cb)
															if( p[offsets[3]] > cb)
																goto is_a_corner;
															else
																if( p[offsets[13]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
														else
															if( p[offsets[13]] > cb)
																if( p[offsets[14]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
													else
														if( p[offsets[13]] > cb)
															if( p[offsets[14]] > cb)
																if( p[offsets[15]] > cb)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else if( p[offsets[8]] < c_b)
							if( p[offsets[9]] < c_b)
								if( p[offsets[10]] < c_b)
									if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] < c_b)
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																if( p[offsets[7]] < c_b)
																	goto is_a_corner;
																else
																	goto is_not_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
				else
					if( p[offsets[7]] > cb)
						if( p[offsets[6]] > cb)
							if( p[offsets[8]] > cb)
								if( p[offsets[9]] > cb)
									if( p[offsets[10]] > cb)
										if( p[offsets[11]] > cb)
											if( p[offsets[5]] > cb)
												if( p[offsets[4]] > cb)
													if( p[offsets[3]] > cb)
														if( p[offsets[2]] > cb)
															goto is_a_corner;
														else
															if( p[offsets[12]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
													else
														if( p[offsets[12]] > cb)
															if( p[offsets[13]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[12]] > cb)
														if( p[offsets[13]] > cb)
															if( p[offsets[14]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[12]] > cb)
													if( p[offsets[13]] > cb)
														if( p[offsets[14]] > cb)
															if( p[offsets[15]] > cb)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else if( p[offsets[7]] < c_b)
						if( p[offsets[8]] < c_b)
							if( p[offsets[9]] < c_b)
								if( p[offsets[10]] < c_b)
									if( p[offsets[11]] < c_b)
										if( p[offsets[12]] < c_b)
											if( p[offsets[13]] < c_b)
												if( p[offsets[14]] < c_b)
													if( p[offsets[15]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[3]] < c_b)
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[2]] < c_b)
												if( p[offsets[3]] < c_b)
													if( p[offsets[4]] < c_b)
														if( p[offsets[5]] < c_b)
															if( p[offsets[6]] < c_b)
																goto is_a_corner;
															else
																goto is_not_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else
						goto is_not_a_corner;
			else
				if( p[offsets[6]] > cb)
					if( p[offsets[7]] > cb)
						if( p[offsets[8]] > cb)
							if( p[offsets[9]] > cb)
								if( p[offsets[10]] > cb)
									if( p[offsets[5]] > cb)
										if( p[offsets[4]] > cb)
											if( p[offsets[3]] > cb)
												if( p[offsets[2]] > cb)
													if( p[offsets[1]] > cb)
														goto is_a_corner;
													else
														if( p[offsets[11]] > cb)
															goto is_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[11]] > cb)
														if( p[offsets[12]] > cb)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[11]] > cb)
													if( p[offsets[12]] > cb)
														if( p[offsets[13]] > cb)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[11]] > cb)
												if( p[offsets[12]] > cb)
													if( p[offsets[13]] > cb)
														if( p[offsets[14]] > cb)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										if( p[offsets[11]] > cb)
											if( p[offsets[12]] > cb)
												if( p[offsets[13]] > cb)
													if( p[offsets[14]] > cb)
														if( p[offsets[15]] > cb)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else
						goto is_not_a_corner;
				else if( p[offsets[6]] < c_b)
					if( p[offsets[7]] < c_b)
						if( p[offsets[8]] < c_b)
							if( p[offsets[9]] < c_b)
								if( p[offsets[10]] < c_b)
									if( p[offsets[5]] < c_b)
										if( p[offsets[4]] < c_b)
											if( p[offsets[3]] < c_b)
												if( p[offsets[2]] < c_b)
													if( p[offsets[1]] < c_b)
														goto is_a_corner;
													else
														if( p[offsets[11]] < c_b)
															goto is_a_corner;
														else
															goto is_not_a_corner;
												else
													if( p[offsets[11]] < c_b)
														if( p[offsets[12]] < c_b)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
											else
												if( p[offsets[11]] < c_b)
													if( p[offsets[12]] < c_b)
														if( p[offsets[13]] < c_b)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
										else
											if( p[offsets[11]] < c_b)
												if( p[offsets[12]] < c_b)
													if( p[offsets[13]] < c_b)
														if( p[offsets[14]] < c_b)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
									else
										if( p[offsets[11]] < c_b)
											if( p[offsets[12]] < c_b)
												if( p[offsets[13]] < c_b)
													if( p[offsets[14]] < c_b)
														if( p[offsets[15]] < c_b)
															goto is_a_corner;
														else
															goto is_not_a_corner;
													else
														goto is_not_a_corner;
												else
													goto is_not_a_corner;
											else
												goto is_not_a_corner;
										else
											goto is_not_a_corner;
								else
									goto is_not_a_corner;
							else
								goto is_not_a_corner;
						else
							goto is_not_a_corner;
					else
						goto is_not_a_corner;
				else
					goto is_not_a_corner;

is_a_corner:
			bmin=b;
			goto end_if;

is_not_a_corner:
			bmax=b;
			goto end_if;

end_if:

			if(bmin == bmax - 1 || bmin == bmax)
				return bmin;
			b = (bmin + bmax) / 2;
		}
	}


    bool FAST::isCorner10( const uint8_t * p, const int * offsets, uint8_t threshold )
	{
		int cb = *p + threshold;
		int c_b= *p - threshold;
		if(p[offsets[0]] > cb)
			if(p[offsets[1]] > cb)
				if(p[offsets[2]] > cb)
					if(p[offsets[3]] > cb)
						if(p[offsets[4]] > cb)
							if(p[offsets[5]] > cb)
								if(p[offsets[6]] > cb)
									if(p[offsets[7]] > cb)
										if(p[offsets[8]] > cb)
											if(p[offsets[9]] > cb)
											{}
											else
												if(p[offsets[15]] > cb)
												{}
												else
													return false;
										else
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													return false;
											else
												return false;
									else
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
								else if(p[offsets[6]] < c_b)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else if(p[offsets[12]] < c_b)
										if(p[offsets[7]] < c_b)
											if(p[offsets[8]] < c_b)
												if(p[offsets[9]] < c_b)
													if(p[offsets[10]] < c_b)
														if(p[offsets[11]] < c_b)
															if(p[offsets[13]] < c_b)
																if(p[offsets[14]] < c_b)
																	if(p[offsets[15]] < c_b)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
							else if(p[offsets[5]] < c_b)
								if(p[offsets[15]] > cb)
									if(p[offsets[11]] > cb)
										if(p[offsets[12]] > cb)
											if(p[offsets[13]] > cb)
												if(p[offsets[14]] > cb)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else if(p[offsets[11]] < c_b)
										if(p[offsets[6]] < c_b)
											if(p[offsets[7]] < c_b)
												if(p[offsets[8]] < c_b)
													if(p[offsets[9]] < c_b)
														if(p[offsets[10]] < c_b)
															if(p[offsets[12]] < c_b)
																if(p[offsets[13]] < c_b)
																	if(p[offsets[14]] < c_b)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									if(p[offsets[6]] < c_b)
										if(p[offsets[7]] < c_b)
											if(p[offsets[8]] < c_b)
												if(p[offsets[9]] < c_b)
													if(p[offsets[10]] < c_b)
														if(p[offsets[11]] < c_b)
															if(p[offsets[12]] < c_b)
																if(p[offsets[13]] < c_b)
																	if(p[offsets[14]] < c_b)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
							else
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else if(p[offsets[11]] < c_b)
									if(p[offsets[6]] < c_b)
										if(p[offsets[7]] < c_b)
											if(p[offsets[8]] < c_b)
												if(p[offsets[9]] < c_b)
													if(p[offsets[10]] < c_b)
														if(p[offsets[12]] < c_b)
															if(p[offsets[13]] < c_b)
																if(p[offsets[14]] < c_b)
																	if(p[offsets[15]] < c_b)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
						else if(p[offsets[4]] < c_b)
							if(p[offsets[14]] > cb)
								if(p[offsets[10]] > cb)
									if(p[offsets[11]] > cb)
										if(p[offsets[12]] > cb)
											if(p[offsets[13]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
																if(p[offsets[8]] > cb)
																	if(p[offsets[9]] > cb)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else if(p[offsets[10]] < c_b)
									if(p[offsets[5]] < c_b)
										if(p[offsets[6]] < c_b)
											if(p[offsets[7]] < c_b)
												if(p[offsets[8]] < c_b)
													if(p[offsets[9]] < c_b)
														if(p[offsets[11]] < c_b)
															if(p[offsets[12]] < c_b)
																if(p[offsets[13]] < c_b)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else if(p[offsets[14]] < c_b)
								if(p[offsets[6]] < c_b)
									if(p[offsets[7]] < c_b)
										if(p[offsets[8]] < c_b)
											if(p[offsets[9]] < c_b)
												if(p[offsets[10]] < c_b)
													if(p[offsets[11]] < c_b)
														if(p[offsets[12]] < c_b)
															if(p[offsets[13]] < c_b)
																if(p[offsets[5]] < c_b)
																{}
																else
																	if(p[offsets[15]] < c_b)
																	{}
																	else
																		return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								if(p[offsets[5]] < c_b)
									if(p[offsets[6]] < c_b)
										if(p[offsets[7]] < c_b)
											if(p[offsets[8]] < c_b)
												if(p[offsets[9]] < c_b)
													if(p[offsets[10]] < c_b)
														if(p[offsets[11]] < c_b)
															if(p[offsets[12]] < c_b)
																if(p[offsets[13]] < c_b)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
						else
							if(p[offsets[10]] > cb)
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
																if(p[offsets[8]] > cb)
																	if(p[offsets[9]] > cb)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else if(p[offsets[10]] < c_b)
								if(p[offsets[6]] < c_b)
									if(p[offsets[7]] < c_b)
										if(p[offsets[8]] < c_b)
											if(p[offsets[9]] < c_b)
												if(p[offsets[11]] < c_b)
													if(p[offsets[12]] < c_b)
														if(p[offsets[13]] < c_b)
															if(p[offsets[14]] < c_b)
																if(p[offsets[5]] < c_b)
																{}
																else
																	if(p[offsets[15]] < c_b)
																	{}
																	else
																		return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
					else if(p[offsets[3]] < c_b)
						if(p[offsets[9]] > cb)
							if(p[offsets[10]] > cb)
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
																if(p[offsets[8]] > cb)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
																if(p[offsets[8]] > cb)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else if(p[offsets[9]] < c_b)
							if(p[offsets[6]] < c_b)
								if(p[offsets[7]] < c_b)
									if(p[offsets[8]] < c_b)
										if(p[offsets[10]] < c_b)
											if(p[offsets[11]] < c_b)
												if(p[offsets[12]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[4]] < c_b)
														{}
														else
															if(p[offsets[13]] < c_b)
																if(p[offsets[14]] < c_b)
																{}
																else
																	return false;
															else
																return false;
													else
														if(p[offsets[13]] < c_b)
															if(p[offsets[14]] < c_b)
																if(p[offsets[15]] < c_b)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						if(p[offsets[9]] > cb)
							if(p[offsets[10]] > cb)
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
																if(p[offsets[8]] > cb)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
																if(p[offsets[8]] > cb)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else if(p[offsets[9]] < c_b)
							if(p[offsets[6]] < c_b)
								if(p[offsets[7]] < c_b)
									if(p[offsets[8]] < c_b)
										if(p[offsets[10]] < c_b)
											if(p[offsets[11]] < c_b)
												if(p[offsets[12]] < c_b)
													if(p[offsets[13]] < c_b)
														if(p[offsets[5]] < c_b)
															if(p[offsets[4]] < c_b)
															{}
															else
																if(p[offsets[14]] < c_b)
																{}
																else
																	return false;
														else
															if(p[offsets[14]] < c_b)
																if(p[offsets[15]] < c_b)
																{}
																else
																	return false;
															else
																return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
				else if(p[offsets[2]] < c_b)
					if(p[offsets[8]] > cb)
						if(p[offsets[9]] > cb)
							if(p[offsets[10]] > cb)
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] > cb)
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else if(p[offsets[8]] < c_b)
						if(p[offsets[6]] < c_b)
							if(p[offsets[7]] < c_b)
								if(p[offsets[9]] < c_b)
									if(p[offsets[10]] < c_b)
										if(p[offsets[11]] < c_b)
											if(p[offsets[5]] < c_b)
												if(p[offsets[4]] < c_b)
													if(p[offsets[3]] < c_b)
													{}
													else
														if(p[offsets[12]] < c_b)
															if(p[offsets[13]] < c_b)
															{}
															else
																return false;
														else
															return false;
												else
													if(p[offsets[12]] < c_b)
														if(p[offsets[13]] < c_b)
															if(p[offsets[14]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[12]] < c_b)
													if(p[offsets[13]] < c_b)
														if(p[offsets[14]] < c_b)
															if(p[offsets[15]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else
					if(p[offsets[8]] > cb)
						if(p[offsets[9]] > cb)
							if(p[offsets[10]] > cb)
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] > cb)
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
															if(p[offsets[7]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else if(p[offsets[8]] < c_b)
						if(p[offsets[6]] < c_b)
							if(p[offsets[7]] < c_b)
								if(p[offsets[9]] < c_b)
									if(p[offsets[10]] < c_b)
										if(p[offsets[11]] < c_b)
											if(p[offsets[12]] < c_b)
												if(p[offsets[5]] < c_b)
													if(p[offsets[4]] < c_b)
														if(p[offsets[3]] < c_b)
														{}
														else
															if(p[offsets[13]] < c_b)
															{}
															else
																return false;
													else
														if(p[offsets[13]] < c_b)
															if(p[offsets[14]] < c_b)
															{}
															else
																return false;
														else
															return false;
												else
													if(p[offsets[13]] < c_b)
														if(p[offsets[14]] < c_b)
															if(p[offsets[15]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
			else if(p[offsets[1]] < c_b)
				if(p[offsets[7]] > cb)
					if(p[offsets[8]] > cb)
						if(p[offsets[9]] > cb)
							if(p[offsets[10]] > cb)
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] > cb)
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[2]] > cb)
											if(p[offsets[3]] > cb)
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else if(p[offsets[7]] < c_b)
					if(p[offsets[6]] < c_b)
						if(p[offsets[8]] < c_b)
							if(p[offsets[9]] < c_b)
								if(p[offsets[10]] < c_b)
									if(p[offsets[5]] < c_b)
										if(p[offsets[4]] < c_b)
											if(p[offsets[3]] < c_b)
												if(p[offsets[2]] < c_b)
												{}
												else
													if(p[offsets[11]] < c_b)
														if(p[offsets[12]] < c_b)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[11]] < c_b)
													if(p[offsets[12]] < c_b)
														if(p[offsets[13]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[11]] < c_b)
												if(p[offsets[12]] < c_b)
													if(p[offsets[13]] < c_b)
														if(p[offsets[14]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[11]] < c_b)
											if(p[offsets[12]] < c_b)
												if(p[offsets[13]] < c_b)
													if(p[offsets[14]] < c_b)
														if(p[offsets[15]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else
					return false;
			else
				if(p[offsets[7]] > cb)
					if(p[offsets[8]] > cb)
						if(p[offsets[9]] > cb)
							if(p[offsets[10]] > cb)
								if(p[offsets[11]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[13]] > cb)
											if(p[offsets[14]] > cb)
												if(p[offsets[15]] > cb)
												{}
												else
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] > cb)
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[2]] > cb)
											if(p[offsets[3]] > cb)
												if(p[offsets[4]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[6]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else if(p[offsets[7]] < c_b)
					if(p[offsets[6]] < c_b)
						if(p[offsets[8]] < c_b)
							if(p[offsets[9]] < c_b)
								if(p[offsets[10]] < c_b)
									if(p[offsets[11]] < c_b)
										if(p[offsets[5]] < c_b)
											if(p[offsets[4]] < c_b)
												if(p[offsets[3]] < c_b)
													if(p[offsets[2]] < c_b)
													{}
													else
														if(p[offsets[12]] < c_b)
														{}
														else
															return false;
												else
													if(p[offsets[12]] < c_b)
														if(p[offsets[13]] < c_b)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[12]] < c_b)
													if(p[offsets[13]] < c_b)
														if(p[offsets[14]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[12]] < c_b)
												if(p[offsets[13]] < c_b)
													if(p[offsets[14]] < c_b)
														if(p[offsets[15]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else
					return false;
		else if(p[offsets[0]] < c_b)
			if(p[offsets[1]] > cb)
				if(p[offsets[7]] > cb)
					if(p[offsets[6]] > cb)
						if(p[offsets[8]] > cb)
							if(p[offsets[9]] > cb)
								if(p[offsets[10]] > cb)
									if(p[offsets[5]] > cb)
										if(p[offsets[4]] > cb)
											if(p[offsets[3]] > cb)
												if(p[offsets[2]] > cb)
												{}
												else
													if(p[offsets[11]] > cb)
														if(p[offsets[12]] > cb)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[11]] > cb)
													if(p[offsets[12]] > cb)
														if(p[offsets[13]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[11]] > cb)
												if(p[offsets[12]] > cb)
													if(p[offsets[13]] > cb)
														if(p[offsets[14]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[11]] > cb)
											if(p[offsets[12]] > cb)
												if(p[offsets[13]] > cb)
													if(p[offsets[14]] > cb)
														if(p[offsets[15]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else if(p[offsets[7]] < c_b)
					if(p[offsets[8]] < c_b)
						if(p[offsets[9]] < c_b)
							if(p[offsets[10]] < c_b)
								if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] < c_b)
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[2]] < c_b)
											if(p[offsets[3]] < c_b)
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else
					return false;
			else if(p[offsets[1]] < c_b)
				if(p[offsets[2]] > cb)
					if(p[offsets[8]] > cb)
						if(p[offsets[6]] > cb)
							if(p[offsets[7]] > cb)
								if(p[offsets[9]] > cb)
									if(p[offsets[10]] > cb)
										if(p[offsets[11]] > cb)
											if(p[offsets[5]] > cb)
												if(p[offsets[4]] > cb)
													if(p[offsets[3]] > cb)
													{}
													else
														if(p[offsets[12]] > cb)
															if(p[offsets[13]] > cb)
															{}
															else
																return false;
														else
															return false;
												else
													if(p[offsets[12]] > cb)
														if(p[offsets[13]] > cb)
															if(p[offsets[14]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[12]] > cb)
													if(p[offsets[13]] > cb)
														if(p[offsets[14]] > cb)
															if(p[offsets[15]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else if(p[offsets[8]] < c_b)
						if(p[offsets[9]] < c_b)
							if(p[offsets[10]] < c_b)
								if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] < c_b)
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else if(p[offsets[2]] < c_b)
					if(p[offsets[3]] > cb)
						if(p[offsets[9]] > cb)
							if(p[offsets[6]] > cb)
								if(p[offsets[7]] > cb)
									if(p[offsets[8]] > cb)
										if(p[offsets[10]] > cb)
											if(p[offsets[11]] > cb)
												if(p[offsets[12]] > cb)
													if(p[offsets[5]] > cb)
														if(p[offsets[4]] > cb)
														{}
														else
															if(p[offsets[13]] > cb)
																if(p[offsets[14]] > cb)
																{}
																else
																	return false;
															else
																return false;
													else
														if(p[offsets[13]] > cb)
															if(p[offsets[14]] > cb)
																if(p[offsets[15]] > cb)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else if(p[offsets[9]] < c_b)
							if(p[offsets[10]] < c_b)
								if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
																if(p[offsets[8]] < c_b)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
																if(p[offsets[8]] < c_b)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else if(p[offsets[3]] < c_b)
						if(p[offsets[4]] > cb)
							if(p[offsets[14]] > cb)
								if(p[offsets[6]] > cb)
									if(p[offsets[7]] > cb)
										if(p[offsets[8]] > cb)
											if(p[offsets[9]] > cb)
												if(p[offsets[10]] > cb)
													if(p[offsets[11]] > cb)
														if(p[offsets[12]] > cb)
															if(p[offsets[13]] > cb)
																if(p[offsets[5]] > cb)
																{}
																else
																	if(p[offsets[15]] > cb)
																	{}
																	else
																		return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else if(p[offsets[14]] < c_b)
								if(p[offsets[10]] > cb)
									if(p[offsets[5]] > cb)
										if(p[offsets[6]] > cb)
											if(p[offsets[7]] > cb)
												if(p[offsets[8]] > cb)
													if(p[offsets[9]] > cb)
														if(p[offsets[11]] > cb)
															if(p[offsets[12]] > cb)
																if(p[offsets[13]] > cb)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else if(p[offsets[10]] < c_b)
									if(p[offsets[11]] < c_b)
										if(p[offsets[12]] < c_b)
											if(p[offsets[13]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
																if(p[offsets[8]] < c_b)
																	if(p[offsets[9]] < c_b)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								if(p[offsets[5]] > cb)
									if(p[offsets[6]] > cb)
										if(p[offsets[7]] > cb)
											if(p[offsets[8]] > cb)
												if(p[offsets[9]] > cb)
													if(p[offsets[10]] > cb)
														if(p[offsets[11]] > cb)
															if(p[offsets[12]] > cb)
																if(p[offsets[13]] > cb)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
						else if(p[offsets[4]] < c_b)
							if(p[offsets[5]] > cb)
								if(p[offsets[15]] < c_b)
									if(p[offsets[11]] > cb)
										if(p[offsets[6]] > cb)
											if(p[offsets[7]] > cb)
												if(p[offsets[8]] > cb)
													if(p[offsets[9]] > cb)
														if(p[offsets[10]] > cb)
															if(p[offsets[12]] > cb)
																if(p[offsets[13]] > cb)
																	if(p[offsets[14]] > cb)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else if(p[offsets[11]] < c_b)
										if(p[offsets[12]] < c_b)
											if(p[offsets[13]] < c_b)
												if(p[offsets[14]] < c_b)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									if(p[offsets[6]] > cb)
										if(p[offsets[7]] > cb)
											if(p[offsets[8]] > cb)
												if(p[offsets[9]] > cb)
													if(p[offsets[10]] > cb)
														if(p[offsets[11]] > cb)
															if(p[offsets[12]] > cb)
																if(p[offsets[13]] > cb)
																	if(p[offsets[14]] > cb)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
							else if(p[offsets[5]] < c_b)
								if(p[offsets[6]] > cb)
									if(p[offsets[12]] > cb)
										if(p[offsets[7]] > cb)
											if(p[offsets[8]] > cb)
												if(p[offsets[9]] > cb)
													if(p[offsets[10]] > cb)
														if(p[offsets[11]] > cb)
															if(p[offsets[13]] > cb)
																if(p[offsets[14]] > cb)
																	if(p[offsets[15]] > cb)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else if(p[offsets[6]] < c_b)
									if(p[offsets[7]] < c_b)
										if(p[offsets[8]] < c_b)
											if(p[offsets[9]] < c_b)
											{}
											else
												if(p[offsets[15]] < c_b)
												{}
												else
													return false;
										else
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													return false;
											else
												return false;
									else
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
								else
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
							else
								if(p[offsets[11]] > cb)
									if(p[offsets[6]] > cb)
										if(p[offsets[7]] > cb)
											if(p[offsets[8]] > cb)
												if(p[offsets[9]] > cb)
													if(p[offsets[10]] > cb)
														if(p[offsets[12]] > cb)
															if(p[offsets[13]] > cb)
																if(p[offsets[14]] > cb)
																	if(p[offsets[15]] > cb)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
						else
							if(p[offsets[10]] > cb)
								if(p[offsets[6]] > cb)
									if(p[offsets[7]] > cb)
										if(p[offsets[8]] > cb)
											if(p[offsets[9]] > cb)
												if(p[offsets[11]] > cb)
													if(p[offsets[12]] > cb)
														if(p[offsets[13]] > cb)
															if(p[offsets[14]] > cb)
																if(p[offsets[5]] > cb)
																{}
																else
																	if(p[offsets[15]] > cb)
																	{}
																	else
																		return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else if(p[offsets[10]] < c_b)
								if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
																if(p[offsets[8]] < c_b)
																	if(p[offsets[9]] < c_b)
																	{}
																	else
																		return false;
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
					else
						if(p[offsets[9]] > cb)
							if(p[offsets[6]] > cb)
								if(p[offsets[7]] > cb)
									if(p[offsets[8]] > cb)
										if(p[offsets[10]] > cb)
											if(p[offsets[11]] > cb)
												if(p[offsets[12]] > cb)
													if(p[offsets[13]] > cb)
														if(p[offsets[5]] > cb)
															if(p[offsets[4]] > cb)
															{}
															else
																if(p[offsets[14]] > cb)
																{}
																else
																	return false;
														else
															if(p[offsets[14]] > cb)
																if(p[offsets[15]] > cb)
																{}
																else
																	return false;
															else
																return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else if(p[offsets[9]] < c_b)
							if(p[offsets[10]] < c_b)
								if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
																if(p[offsets[8]] < c_b)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
																if(p[offsets[8]] < c_b)
																{}
																else
																	return false;
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
				else
					if(p[offsets[8]] > cb)
						if(p[offsets[6]] > cb)
							if(p[offsets[7]] > cb)
								if(p[offsets[9]] > cb)
									if(p[offsets[10]] > cb)
										if(p[offsets[11]] > cb)
											if(p[offsets[12]] > cb)
												if(p[offsets[5]] > cb)
													if(p[offsets[4]] > cb)
														if(p[offsets[3]] > cb)
														{}
														else
															if(p[offsets[13]] > cb)
															{}
															else
																return false;
													else
														if(p[offsets[13]] > cb)
															if(p[offsets[14]] > cb)
															{}
															else
																return false;
														else
															return false;
												else
													if(p[offsets[13]] > cb)
														if(p[offsets[14]] > cb)
															if(p[offsets[15]] > cb)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												return false;
										else
											return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else if(p[offsets[8]] < c_b)
						if(p[offsets[9]] < c_b)
							if(p[offsets[10]] < c_b)
								if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] < c_b)
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
															if(p[offsets[7]] < c_b)
															{}
															else
																return false;
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
			else
				if(p[offsets[7]] > cb)
					if(p[offsets[6]] > cb)
						if(p[offsets[8]] > cb)
							if(p[offsets[9]] > cb)
								if(p[offsets[10]] > cb)
									if(p[offsets[11]] > cb)
										if(p[offsets[5]] > cb)
											if(p[offsets[4]] > cb)
												if(p[offsets[3]] > cb)
													if(p[offsets[2]] > cb)
													{}
													else
														if(p[offsets[12]] > cb)
														{}
														else
															return false;
												else
													if(p[offsets[12]] > cb)
														if(p[offsets[13]] > cb)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[12]] > cb)
													if(p[offsets[13]] > cb)
														if(p[offsets[14]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[12]] > cb)
												if(p[offsets[13]] > cb)
													if(p[offsets[14]] > cb)
														if(p[offsets[15]] > cb)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else if(p[offsets[7]] < c_b)
					if(p[offsets[8]] < c_b)
						if(p[offsets[9]] < c_b)
							if(p[offsets[10]] < c_b)
								if(p[offsets[11]] < c_b)
									if(p[offsets[12]] < c_b)
										if(p[offsets[13]] < c_b)
											if(p[offsets[14]] < c_b)
												if(p[offsets[15]] < c_b)
												{}
												else
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
											else
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
										else
											if(p[offsets[3]] < c_b)
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[2]] < c_b)
											if(p[offsets[3]] < c_b)
												if(p[offsets[4]] < c_b)
													if(p[offsets[5]] < c_b)
														if(p[offsets[6]] < c_b)
														{}
														else
															return false;
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else
					return false;
		else
			if(p[offsets[6]] > cb)
				if(p[offsets[7]] > cb)
					if(p[offsets[8]] > cb)
						if(p[offsets[9]] > cb)
							if(p[offsets[10]] > cb)
								if(p[offsets[5]] > cb)
									if(p[offsets[4]] > cb)
										if(p[offsets[3]] > cb)
											if(p[offsets[2]] > cb)
												if(p[offsets[1]] > cb)
												{}
												else
													if(p[offsets[11]] > cb)
													{}
													else
														return false;
											else
												if(p[offsets[11]] > cb)
													if(p[offsets[12]] > cb)
													{}
													else
														return false;
												else
													return false;
										else
											if(p[offsets[11]] > cb)
												if(p[offsets[12]] > cb)
													if(p[offsets[13]] > cb)
													{}
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[11]] > cb)
											if(p[offsets[12]] > cb)
												if(p[offsets[13]] > cb)
													if(p[offsets[14]] > cb)
													{}
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									if(p[offsets[11]] > cb)
										if(p[offsets[12]] > cb)
											if(p[offsets[13]] > cb)
												if(p[offsets[14]] > cb)
													if(p[offsets[15]] > cb)
													{}
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else
					return false;
			else if(p[offsets[6]] < c_b)
				if(p[offsets[7]] < c_b)
					if(p[offsets[8]] < c_b)
						if(p[offsets[9]] < c_b)
							if(p[offsets[10]] < c_b)
								if(p[offsets[5]] < c_b)
									if(p[offsets[4]] < c_b)
										if(p[offsets[3]] < c_b)
											if(p[offsets[2]] < c_b)
												if(p[offsets[1]] < c_b)
												{}
												else
													if(p[offsets[11]] < c_b)
													{}
													else
														return false;
											else
												if(p[offsets[11]] < c_b)
													if(p[offsets[12]] < c_b)
													{}
													else
														return false;
												else
													return false;
										else
											if(p[offsets[11]] < c_b)
												if(p[offsets[12]] < c_b)
													if(p[offsets[13]] < c_b)
													{}
													else
														return false;
												else
													return false;
											else
												return false;
									else
										if(p[offsets[11]] < c_b)
											if(p[offsets[12]] < c_b)
												if(p[offsets[13]] < c_b)
													if(p[offsets[14]] < c_b)
													{}
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
								else
									if(p[offsets[11]] < c_b)
										if(p[offsets[12]] < c_b)
											if(p[offsets[13]] < c_b)
												if(p[offsets[14]] < c_b)
													if(p[offsets[15]] < c_b)
													{}
													else
														return false;
												else
													return false;
											else
												return false;
										else
											return false;
									else
										return false;
							else
								return false;
						else
							return false;
					else
						return false;
				else
					return false;
			else
				return false;
		return true;
	}

}
