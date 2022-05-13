#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class Classifier {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        uint8_t votes[4] = { 0 };
                        // tree #1
                        if (x[4] <= 11.994999885559082) {
                            if (x[4] <= 8.795000076293945) {
                                if (x[0] <= 7.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[5] <= 0.6119794249534607) {
                                        if (x[1] <= 9.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.5086653232574463) {
                                                if (x[6] <= 66.0) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }
                            }

                            else {
                                if (x[5] <= 0.5727948248386383) {
                                    if (x[1] <= 10.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[5] <= 0.18327320367097855) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[6] <= 83.0) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                if (x[7] <= 11.5) {
                                                    if (x[4] <= 11.434999942779541) {
                                                        votes[2] += 1;
                                                    }

                                                    else {
                                                        votes[1] += 1;
                                                    }
                                                }

                                                else {
                                                    if (x[5] <= 0.45520082116127014) {
                                                        if (x[4] <= 11.380000114440918) {
                                                            votes[2] += 1;
                                                        }

                                                        else {
                                                            votes[1] += 1;
                                                        }
                                                    }

                                                    else {
                                                        votes[1] += 1;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[1] <= 11.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[0] <= 9.5) {
                                            if (x[0] <= 8.5) {
                                                if (x[5] <= 1.4572231769561768) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    if (x[6] <= 68.5) {
                                                        votes[1] += 1;
                                                    }

                                                    else {
                                                        votes[2] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[7] <= 22.5) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    if (x[4] <= 11.100000381469727) {
                                                        votes[2] += 1;
                                                    }

                                                    else {
                                                        votes[1] += 1;
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[7] <= 99.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #2
                        if (x[2] <= 11.5) {
                            if (x[3] <= 10.5) {
                                if (x[4] <= 8.860000133514404) {
                                    if (x[0] <= 7.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[1] <= 9.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.6119794249534607) {
                                                if (x[6] <= 63.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    if (x[6] <= 65.5) {
                                                        votes[1] += 1;
                                                    }

                                                    else {
                                                        votes[3] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 0.5550726801156998) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 9.5) {
                                    if (x[4] <= 8.700000286102295) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[0] <= 8.5) {
                                            if (x[7] <= 47.0) {
                                                if (x[6] <= 55.0) {
                                                    if (x[4] <= 10.160000324249268) {
                                                        votes[2] += 1;
                                                    }

                                                    else {
                                                        votes[1] += 1;
                                                    }
                                                }

                                                else {
                                                    if (x[4] <= 10.71500015258789) {
                                                        if (x[1] <= 11.5) {
                                                            votes[1] += 1;
                                                        }

                                                        else {
                                                            if (x[7] <= 34.5) {
                                                                votes[1] += 1;
                                                            }

                                                            else {
                                                                votes[1] += 1;
                                                            }
                                                        }
                                                    }

                                                    else {
                                                        votes[1] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }

                                        else {
                                            if (x[4] <= 11.070000171661377) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[2] <= 10.5) {
                                        if (x[6] <= 84.5) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            if (x[7] <= 14.5) {
                                                if (x[3] <= 11.5) {
                                                    votes[2] += 1;
                                                }

                                                else {
                                                    if (x[7] <= 8.5) {
                                                        votes[1] += 1;
                                                    }

                                                    else {
                                                        votes[2] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[6] <= 75.0) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[3] <= 12.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #3
                        if (x[0] <= 11.5) {
                            if (x[7] <= 22.5) {
                                if (x[4] <= 11.269999980926514) {
                                    if (x[2] <= 9.0) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                if (x[3] <= 10.5) {
                                    if (x[2] <= 7.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[7] <= 38.5) {
                                            if (x[4] <= 8.760000228881836) {
                                                if (x[6] <= 65.5) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }

                                        else {
                                            if (x[7] <= 39.5) {
                                                if (x[4] <= 8.625) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 0.5659959018230438) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        if (x[2] <= 7.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[6] <= 53.0) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[4] <= 10.71500015258789) {
                                                    if (x[4] <= 9.460000038146973) {
                                                        votes[1] += 1;
                                                    }

                                                    else {
                                                        if (x[4] <= 10.195000171661377) {
                                                            votes[2] += 1;
                                                        }

                                                        else {
                                                            if (x[7] <= 34.5) {
                                                                votes[2] += 1;
                                                            }

                                                            else {
                                                                votes[1] += 1;
                                                            }
                                                        }
                                                    }
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[6] <= 0.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #4
                        if (x[0] <= 11.5) {
                            if (x[3] <= 10.5) {
                                if (x[0] <= 7.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[3] <= 9.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[5] <= 0.5818491578102112) {
                                            if (x[6] <= 64.0) {
                                                if (x[6] <= 61.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 9.5) {
                                    if (x[7] <= 44.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[1] <= 11.5) {
                                            if (x[6] <= 29.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }

                                        else {
                                            if (x[5] <= 1.2412534952163696) {
                                                if (x[7] <= 52.0) {
                                                    votes[2] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[4] <= 11.769999980926514) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 12.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #5
                        if (x[7] <= 95.5) {
                            if (x[3] <= 10.5) {
                                if (x[4] <= 8.614999771118164) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[6] <= 60.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[6] <= 63.0) {
                                            if (x[5] <= 0.5140793323516846) {
                                                if (x[4] <= 8.625) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }

                                            else {
                                                if (x[5] <= 0.6105702519416809) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[7] <= 28.0) {
                                                if (x[6] <= 79.5) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 9.5) {
                                    if (x[0] <= 7.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[6] <= 75.0) {
                                            if (x[7] <= 47.0) {
                                                if (x[7] <= 45.0) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    if (x[5] <= 1.2412534952163696) {
                                                        votes[2] += 1;
                                                    }

                                                    else {
                                                        votes[1] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }

                                        else {
                                            if (x[6] <= 76.5) {
                                                if (x[0] <= 8.5) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[2] += 1;
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[7] <= 15.5) {
                                        if (x[0] <= 10.5) {
                                            if (x[1] <= 11.5) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                if (x[4] <= 11.37999963760376) {
                                                    votes[2] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            if (x[7] <= 99.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #6
                        if (x[3] <= 10.5) {
                            if (x[4] <= 8.619999885559082) {
                                votes[3] += 1;
                            }

                            else {
                                if (x[5] <= 0.6523035168647766) {
                                    if (x[4] <= 8.71500015258789) {
                                        if (x[6] <= 60.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[4] <= 8.65500020980835) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[7] <= 26.5) {
                                            if (x[7] <= 20.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }
                        }

                        else {
                            if (x[4] <= 11.994999885559082) {
                                if (x[0] <= 9.5) {
                                    if (x[3] <= 11.5) {
                                        if (x[0] <= 7.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[4] <= 9.900000095367432) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[2] <= 8.5) {
                                                if (x[4] <= 9.940000057220459) {
                                                    votes[2] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }

                                            else {
                                                if (x[4] <= 11.100000381469727) {
                                                    votes[2] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[0] <= 10.5) {
                                        if (x[4] <= 11.539999961853027) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[4] <= 11.764999866485596) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[3] <= 12.5) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }
                        }

                        // tree #7
                        if (x[0] <= 11.5) {
                            if (x[4] <= 8.795000076293945) {
                                if (x[1] <= 10.5) {
                                    if (x[4] <= 8.619999885559082) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[7] <= 38.5) {
                                            if (x[4] <= 8.675000190734863) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }

                                        else {
                                            if (x[7] <= 39.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                if (x[2] <= 9.5) {
                                    if (x[6] <= 15.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[3] <= 10.5) {
                                            if (x[4] <= 8.954999923706055) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[6] <= 81.5) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[7] <= 30.5) {
                                                if (x[5] <= 1.3819207549095154) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[2] += 1;
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[4] <= 11.71999979019165) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            if (x[5] <= 0.04974937066435814) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #8
                        if (x[0] <= 11.5) {
                            if (x[7] <= 22.5) {
                                if (x[2] <= 10.5) {
                                    if (x[2] <= 9.5) {
                                        if (x[4] <= 10.269999980926514) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[7] <= 8.5) {
                                            if (x[4] <= 11.434999942779541) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }

                                        else {
                                            if (x[4] <= 11.37999963760376) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                if (x[2] <= 8.5) {
                                    if (x[4] <= 8.795000076293945) {
                                        if (x[4] <= 8.614999771118164) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[4] <= 8.760000228881836) {
                                                if (x[7] <= 32.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    if (x[5] <= 0.5554576218128204) {
                                                        if (x[7] <= 36.5) {
                                                            votes[1] += 1;
                                                        }

                                                        else {
                                                            if (x[4] <= 8.625) {
                                                                votes[1] += 1;
                                                            }

                                                            else {
                                                                votes[1] += 1;
                                                            }
                                                        }
                                                    }

                                                    else {
                                                        if (x[4] <= 8.690000057220459) {
                                                            votes[3] += 1;
                                                        }

                                                        else {
                                                            if (x[5] <= 0.6448564827442169) {
                                                                votes[1] += 1;
                                                            }

                                                            else {
                                                                votes[1] += 1;
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[5] <= 0.5316037982702255) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[6] <= 69.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[5] <= 1.3819207549095154) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[2] += 1;
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[0] <= 9.5) {
                                        if (x[6] <= 74.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            if (x[7] <= 99.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #9
                        if (x[7] <= 96.0) {
                            if (x[4] <= 8.619999885559082) {
                                votes[3] += 1;
                            }

                            else {
                                if (x[2] <= 9.5) {
                                    if (x[3] <= 10.5) {
                                        if (x[5] <= 0.6119794249534607) {
                                            if (x[6] <= 67.0) {
                                                if (x[5] <= 0.4806194454431534) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    if (x[5] <= 0.5568667948246002) {
                                                        votes[1] += 1;
                                                    }

                                                    else {
                                                        votes[3] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[5] <= 0.5818491578102112) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[7] <= 30.5) {
                                            if (x[5] <= 1.3819207549095154) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[2] += 1;
                                            }
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 0.19426608830690384) {
                                        if (x[3] <= 11.5) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[6] <= 84.5) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            if (x[2] <= 10.5) {
                                                if (x[3] <= 11.5) {
                                                    votes[2] += 1;
                                                }

                                                else {
                                                    if (x[5] <= 0.4910019189119339) {
                                                        if (x[6] <= 91.5) {
                                                            votes[2] += 1;
                                                        }

                                                        else {
                                                            votes[1] += 1;
                                                        }
                                                    }

                                                    else {
                                                        votes[1] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[3] <= 12.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #10
                        if (x[0] <= 9.5) {
                            if (x[3] <= 11.5) {
                                if (x[3] <= 9.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[7] <= 38.5) {
                                        if (x[4] <= 8.860000133514404) {
                                            if (x[0] <= 7.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[3] <= 10.5) {
                                                    if (x[6] <= 65.5) {
                                                        if (x[7] <= 36.5) {
                                                            votes[1] += 1;
                                                        }

                                                        else {
                                                            votes[1] += 1;
                                                        }
                                                    }

                                                    else {
                                                        votes[3] += 1;
                                                    }
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[7] <= 17.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[3] <= 10.5) {
                                            if (x[7] <= 39.5) {
                                                if (x[4] <= 8.690000057220459) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[6] <= 69.5) {
                                    if (x[5] <= 1.2404513955116272) {
                                        if (x[4] <= 9.74500036239624) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[7] <= 39.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[2] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    if (x[6] <= 71.5) {
                                        if (x[5] <= 1.2745506167411804) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[2] += 1;
                                        }
                                    }

                                    else {
                                        if (x[7] <= 23.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[7] <= 25.0) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[3] <= 11.5) {
                                votes[2] += 1;
                            }

                            else {
                                if (x[4] <= 11.769999980926514) {
                                    votes[2] += 1;
                                }

                                else {
                                    if (x[4] <= 11.994999885559082) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[3] <= 12.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }
                            }
                        }

                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < 4; i++) {
                            if (votes[i] > maxVotes) {
                                classIdx = i;
                                maxVotes = votes[i];
                            }
                        }

                        return classIdx;
                    }

                    /**
                    * Predict readable class name
                    */
                    const char* predictLabel(float *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "default";
                            case 1:
                            return "pat";
                            case 2:
                            return "tickle";
                            case 3:
                            return "constantTouch";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                };
            }
        }
    }