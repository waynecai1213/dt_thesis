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
                        if (x[4] <= 15.008333206176758) {
                            if (x[4] <= 12.866666793823242) {
                                if (x[0] <= 9.5) {
                                    if (x[5] <= 1.0299981236457825) {
                                        if (x[1] <= 11.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[6] <= 18.0) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[6] <= 32.0) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    if (x[5] <= 0.8015349805355072) {
                                                        votes[1] += 1;
                                                    }

                                                    else {
                                                        votes[3] += 1;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    if (x[1] <= 14.5) {
                                        if (x[5] <= 0.7404013872146606) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[6] <= 39.0) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[7] <= 32.0) {
                                            if (x[5] <= 1.7198814153671265) {
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
                            }

                            else {
                                if (x[7] <= 27.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[4] <= 13.891666889190674) {
                                        if (x[5] <= 1.419586420059204) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[0] <= 14.5) {
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
                            if (x[7] <= 50.0) {
                                votes[2] += 1;
                            }

                            else {
                                if (x[6] <= 4.5) {
                                    if (x[5] <= 0.233694389462471) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }

                                else {
                                    if (x[6] <= 8.5) {
                                        if (x[6] <= 7.5) {
                                            if (x[7] <= 53.5) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                if (x[4] <= 15.09166669845581) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }
                            }
                        }

                        // tree #2
                        if (x[3] <= 15.5) {
                            if (x[3] <= 14.5) {
                                if (x[0] <= 9.5) {
                                    if (x[0] <= 8.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[1] <= 11.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[5] <= 1.0299981236457825) {
                                                if (x[4] <= 10.091666221618652) {
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
                                    }
                                }

                                else {
                                    if (x[6] <= 39.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[0] <= 10.5) {
                                            if (x[3] <= 12.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[6] <= 41.5) {
                                                    votes[1] += 1;
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
                            }

                            else {
                                if (x[5] <= 0.7699804604053497) {
                                    if (x[7] <= 48.0) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    if (x[4] <= 12.941666603088379) {
                                        if (x[0] <= 9.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[7] <= 28.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[0] <= 10.5) {
                                                    if (x[7] <= 30.0) {
                                                        votes[1] += 1;
                                                    }

                                                    else {
                                                        if (x[6] <= 26.0) {
                                                            votes[3] += 1;
                                                        }

                                                        else {
                                                            if (x[4] <= 12.53333330154419) {
                                                                votes[1] += 1;
                                                            }

                                                            else {
                                                                votes[3] += 1;
                                                            }
                                                        }
                                                    }
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[6] <= 32.0) {
                                            if (x[4] <= 13.25) {
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
                                }
                            }
                        }

                        else {
                            if (x[5] <= 0.33047865331172943) {
                                if (x[6] <= 30.0) {
                                    if (x[2] <= 14.5) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        if (x[6] <= 4.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.3105113357305527) {
                                                if (x[7] <= 54.5) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }

                            else {
                                if (x[7] <= 50.0) {
                                    votes[2] += 1;
                                }

                                else {
                                    if (x[7] <= 51.5) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }
                            }
                        }

                        // tree #3
                        if (x[0] <= 11.5) {
                            if (x[7] <= 56.0) {
                                if (x[4] <= 10.208333492279053) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[2] <= 9.5) {
                                        if (x[3] <= 13.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }

                                    else {
                                        if (x[7] <= 20.5) {
                                            if (x[1] <= 14.0) {
                                                if (x[0] <= 10.5) {
                                                    if (x[5] <= 0.6565732657909393) {
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

                                        else {
                                            if (x[5] <= 1.5968050956726074) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[7] <= 36.5) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            if (x[4] <= 15.40833330154419) {
                                if (x[4] <= 15.008333206176758) {
                                    if (x[2] <= 12.5) {
                                        if (x[1] <= 14.0) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[6] <= 37.0) {
                                                if (x[5] <= 0.711645781993866) {
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
                                    }

                                    else {
                                        if (x[5] <= 0.06400954723358154) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[1] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[7] <= 56.5) {
                                        if (x[2] <= 14.5) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.2881927043199539) {
                                                if (x[4] <= 15.074999809265137) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }

                                            else {
                                                if (x[7] <= 53.5) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #4
                        if (x[0] <= 13.5) {
                            if (x[3] <= 13.5) {
                                if (x[0] <= 9.5) {
                                    if (x[3] <= 11.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[6] <= 25.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 0.7404013872146606) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[7] <= 21.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[7] <= 26.5) {
                                    if (x[5] <= 3.183941960334778) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }

                                else {
                                    if (x[5] <= 1.652888298034668) {
                                        if (x[2] <= 9.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.5462676882743835) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[1] <= 16.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[3] <= 19.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                votes[2] += 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 18.0) {
                                if (x[0] <= 14.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[6] <= 0.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[7] <= 57.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.15376229584217072) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #5
                        if (x[7] <= 52.5) {
                            if (x[3] <= 15.5) {
                                if (x[4] <= 12.866666793823242) {
                                    if (x[5] <= 1.381917417049408) {
                                        if (x[2] <= 9.5) {
                                            if (x[4] <= 10.241666316986084) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[1] <= 13.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[6] <= 39.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[7] <= 19.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[1] <= 14.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[2] <= 9.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[7] <= 30.0) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[2] <= 11.5) {
                                        if (x[5] <= 1.2196159362792969) {
                                            votes[3] += 1;
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
                                if (x[1] <= 18.5) {
                                    if (x[5] <= 0.3485030382871628) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        else {
                            if (x[6] <= 0.5) {
                                if (x[2] <= 11.0) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                if (x[5] <= 0.38349613547325134) {
                                    if (x[4] <= 13.058333396911621) {
                                        if (x[5] <= 0.2662117928266525) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }

                                    else {
                                        if (x[5] <= 0.233694389462471) {
                                            if (x[4] <= 15.041666984558105) {
                                                if (x[4] <= 15.025000095367432) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }

                                        else {
                                            if (x[4] <= 15.108333587646484) {
                                                if (x[5] <= 0.2881927043199539) {
                                                    if (x[4] <= 15.074999809265137) {
                                                        votes[0] += 1;
                                                    }

                                                    else {
                                                        votes[0] += 1;
                                                    }
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }
                                    }
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }
                        }

                        // tree #6
                        if (x[3] <= 15.5) {
                            if (x[4] <= 12.941666603088379) {
                                if (x[4] <= 10.208333492279053) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[5] <= 1.7409200072288513) {
                                        if (x[3] <= 12.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[6] <= 39.5) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[2] <= 10.5) {
                                                    if (x[5] <= 0.7340589165687561) {
                                                        votes[3] += 1;
                                                    }

                                                    else {
                                                        if (x[0] <= 9.5) {
                                                            votes[3] += 1;
                                                        }

                                                        else {
                                                            votes[1] += 1;
                                                        }
                                                    }
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
                            }

                            else {
                                if (x[6] <= 32.0) {
                                    if (x[2] <= 13.0) {
                                        if (x[2] <= 10.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.6306457221508026) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[5] <= 1.4807180762290955) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[2] <= 14.5) {
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
                            if (x[6] <= 10.0) {
                                if (x[5] <= 0.2881927043199539) {
                                    if (x[4] <= 15.058333396911621) {
                                        if (x[5] <= 0.19872522354125977) {
                                            if (x[5] <= 0.15376229584217072) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }

                                    else {
                                        if (x[5] <= 0.26291461288928986) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }

                                else {
                                    if (x[5] <= 0.3105113357305527) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        if (x[6] <= 7.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            if (x[4] <= 15.141666412353516) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 11.0) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #7
                        if (x[3] <= 19.0) {
                            if (x[4] <= 15.008333206176758) {
                                if (x[1] <= 13.5) {
                                    if (x[4] <= 10.199999809265137) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[3] += 1;
                                    }
                                }

                                else {
                                    if (x[7] <= 35.5) {
                                        if (x[1] <= 14.5) {
                                            if (x[5] <= 1.0528195202350616) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }

                                        else {
                                            if (x[4] <= 12.824999809265137) {
                                                if (x[4] <= 12.541666984558105) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    if (x[7] <= 25.5) {
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

                                    else {
                                        if (x[5] <= 0.6306457221508026) {
                                            if (x[0] <= 13.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[1] += 1;
                                            }
                                        }

                                        else {
                                            if (x[3] <= 14.5) {
                                                if (x[4] <= 10.566667079925537) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }

                                            else {
                                                if (x[2] <= 9.5) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[6] <= 10.0) {
                                    if (x[7] <= 57.5) {
                                        if (x[4] <= 15.074999809265137) {
                                            if (x[7] <= 56.5) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }

                                    else {
                                        if (x[7] <= 58.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            votes[0] += 1;
                                        }
                                    }
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #8
                        if (x[0] <= 13.0) {
                            if (x[7] <= 56.0) {
                                if (x[2] <= 9.5) {
                                    if (x[2] <= 8.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[5] <= 1.185661256313324) {
                                            if (x[1] <= 11.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[5] <= 0.7136430442333221) {
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

                                else {
                                    if (x[3] <= 14.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[7] <= 29.5) {
                                            if (x[5] <= 2.6679952144622803) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[2] += 1;
                                            }
                                        }

                                        else {
                                            if (x[6] <= 25.0) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[4] <= 12.883333206176758) {
                                                    votes[3] += 1;
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
                                votes[1] += 1;
                            }
                        }

                        else {
                            if (x[7] <= 50.0) {
                                if (x[1] <= 18.0) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }

                            else {
                                if (x[4] <= 15.008333206176758) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[4] <= 15.09166669845581) {
                                        if (x[5] <= 0.19872522354125977) {
                                            if (x[5] <= 0.15376229584217072) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }

                                        else {
                                            if (x[5] <= 0.233694389462471) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                if (x[7] <= 55.5) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[6] <= 6.5) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.33047865331172943) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                if (x[4] <= 15.141666412353516) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        // tree #9
                        if (x[2] <= 13.5) {
                            if (x[4] <= 10.233333587646484) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[2] <= 9.5) {
                                    if (x[4] <= 10.474999904632568) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    if (x[5] <= 1.3610863089561462) {
                                        if (x[2] <= 12.5) {
                                            if (x[5] <= 1.0784839391708374) {
                                                if (x[0] <= 10.5) {
                                                    if (x[7] <= 20.5) {
                                                        if (x[1] <= 12.5) {
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

                                            else {
                                                if (x[0] <= 10.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    if (x[6] <= 35.5) {
                                                        votes[3] += 1;
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
                                        if (x[4] <= 12.508333683013916) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[0] <= 11.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[2] += 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[4] <= 15.591666221618652) {
                                if (x[6] <= 16.0) {
                                    if (x[4] <= 15.008333206176758) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[6] <= 4.5) {
                                            if (x[7] <= 57.5) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                if (x[7] <= 58.5) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[5] <= 0.3105113357305527) {
                                                if (x[4] <= 15.09166669845581) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
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

                        // tree #10
                        if (x[0] <= 13.5) {
                            if (x[3] <= 13.5) {
                                if (x[3] <= 10.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[3] <= 11.5) {
                                        if (x[4] <= 10.224999904632568) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }

                                    else {
                                        if (x[0] <= 8.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[6] <= 39.0) {
                                                votes[3] += 1;
                                            }

                                            else {
                                                if (x[4] <= 10.875) {
                                                    if (x[3] <= 12.5) {
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
                                    }
                                }
                            }

                            else {
                                if (x[2] <= 9.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[7] <= 22.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[5] <= 1.6666576862335205) {
                                            if (x[2] <= 12.5) {
                                                if (x[0] <= 11.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    if (x[6] <= 27.0) {
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

                                        else {
                                            if (x[4] <= 12.358333587646484) {
                                                votes[3] += 1;
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
                            if (x[1] <= 18.0) {
                                if (x[4] <= 15.008333206176758) {
                                    if (x[2] <= 14.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
                                }

                                else {
                                    if (x[2] <= 14.5) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        if (x[5] <= 0.2881927043199539) {
                                            if (x[5] <= 0.233694389462471) {
                                                if (x[7] <= 57.5) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    if (x[5] <= 0.15376229584217072) {
                                                        votes[0] += 1;
                                                    }

                                                    else {
                                                        votes[0] += 1;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[6] <= 4.5) {
                                                    votes[0] += 1;
                                                }

                                                else {
                                                    votes[0] += 1;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[7] <= 53.5) {
                                                votes[0] += 1;
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                votes[2] += 1;
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