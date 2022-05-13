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
                        if (x[4] <= 14.949999809265137) {
                            if (x[4] <= 12.59000015258789) {
                                if (x[0] <= 9.5) {
                                    if (x[5] <= 1.112443208694458) {
                                        if (x[1] <= 13.5) {
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
                                    votes[3] += 1;
                                }
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            if (x[6] <= 12.0) {
                                if (x[6] <= 1.0) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }

                            else {
                                if (x[7] <= 6.0) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #2
                        if (x[3] <= 15.5) {
                            if (x[3] <= 14.5) {
                                if (x[0] <= 8.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[0] <= 9.5) {
                                        if (x[1] <= 13.0) {
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
                                if (x[5] <= 1.6372830271720886) {
                                    if (x[6] <= 65.5) {
                                        if (x[0] <= 12.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[0] <= 14.0) {
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

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        else {
                            if (x[7] <= 88.0) {
                                if (x[1] <= 19.0) {
                                    if (x[0] <= 12.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        if (x[7] <= 21.0) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            if (x[6] <= 38.0) {
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

                            else {
                                if (x[4] <= 15.025000095367432) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }
                        }

                        // tree #3
                        if (x[0] <= 13.0) {
                            if (x[7] <= 77.5) {
                                if (x[3] <= 14.5) {
                                    if (x[2] <= 9.5) {
                                        if (x[3] <= 11.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[2] <= 8.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[7] <= 73.5) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        votes[3] += 1;
                                    }
                                }

                                else {
                                    if (x[0] <= 9.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[5] <= 1.6372830271720886) {
                                            if (x[4] <= 13.380000114440918) {
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
                            }

                            else {
                                votes[3] += 1;
                            }
                        }

                        else {
                            if (x[6] <= 12.0) {
                                if (x[4] <= 15.025000095367432) {
                                    if (x[6] <= 1.0) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }

                                else {
                                    if (x[5] <= 0.2277158945798874) {
                                        if (x[6] <= 4.5) {
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

                            else {
                                if (x[5] <= 0.46165935695171356) {
                                    if (x[3] <= 15.5) {
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

                        // tree #4
                        if (x[0] <= 13.5) {
                            if (x[3] <= 14.5) {
                                if (x[0] <= 8.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[3] <= 10.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[5] <= 0.7407765686511993) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.7471693754196167) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[5] <= 1.0506243705749512) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    if (x[4] <= 10.880000114440918) {
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
                            }

                            else {
                                if (x[5] <= 1.8619015216827393) {
                                    if (x[6] <= 65.5) {
                                        if (x[2] <= 9.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[5] <= 0.608320415019989) {
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
                                    votes[1] += 1;
                                }
                            }
                        }

                        else {
                            if (x[4] <= 15.199999809265137) {
                                if (x[3] <= 15.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[7] <= 97.5) {
                                        if (x[0] <= 14.5) {
                                            if (x[6] <= 54.0) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                votes[0] += 1;
                                            }
                                        }

                                        else {
                                            if (x[5] <= 0.2277158945798874) {
                                                if (x[5] <= 0.2069520652294159) {
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

                                    else {
                                        votes[0] += 1;
                                    }
                                }
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #5
                        if (x[7] <= 87.5) {
                            if (x[3] <= 19.0) {
                                if (x[1] <= 14.5) {
                                    if (x[3] <= 10.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[2] <= 9.5) {
                                            if (x[4] <= 10.684999942779541) {
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
                                    if (x[1] <= 17.0) {
                                        if (x[6] <= 23.5) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[0] <= 9.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[1] <= 15.5) {
                                                    if (x[2] <= 10.5) {
                                                        if (x[7] <= 44.0) {
                                                            votes[1] += 1;
                                                        }

                                                        else {
                                                            votes[3] += 1;
                                                        }
                                                    }

                                                    else {
                                                        if (x[2] <= 12.5) {
                                                            if (x[5] <= 0.9824405014514923) {
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
                                                    if (x[7] <= 21.0) {
                                                        votes[0] += 1;
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
                                if (x[0] <= 13.0) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        else {
                            if (x[6] <= 5.5) {
                                if (x[4] <= 15.045000076293945) {
                                    if (x[4] <= 15.025000095367432) {
                                        if (x[1] <= 15.5) {
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

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #6
                        if (x[3] <= 15.5) {
                            if (x[5] <= 0.9552358686923981) {
                                if (x[4] <= 13.710000038146973) {
                                    if (x[0] <= 9.5) {
                                        if (x[3] <= 11.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[6] <= 26.0) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[2] <= 8.5) {
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

                                else {
                                    if (x[7] <= 80.0) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }
                            }

                            else {
                                if (x[5] <= 1.6245689392089844) {
                                    if (x[5] <= 1.4201892614364624) {
                                        if (x[5] <= 1.1037809252738953) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[2] <= 8.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[7] <= 34.0) {
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

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        else {
                            if (x[5] <= 0.3245965987443924) {
                                if (x[1] <= 18.5) {
                                    if (x[5] <= 0.15529361367225647) {
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

                            else {
                                if (x[6] <= 21.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #7
                        if (x[3] <= 15.5) {
                            if (x[4] <= 12.654999732971191) {
                                if (x[2] <= 9.5) {
                                    if (x[6] <= 62.5) {
                                        if (x[7] <= 63.0) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[2] <= 8.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                if (x[4] <= 10.990000247955322) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }
                                        }
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
                                    votes[3] += 1;
                                }
                            }

                            else {
                                if (x[7] <= 75.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }
                        }

                        else {
                            if (x[7] <= 83.5) {
                                if (x[1] <= 18.0) {
                                    if (x[4] <= 14.819999694824219) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        votes[0] += 1;
                                    }
                                }

                                else {
                                    if (x[2] <= 13.0) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #8
                        if (x[7] <= 88.0) {
                            if (x[7] <= 77.5) {
                                if (x[3] <= 18.0) {
                                    if (x[2] <= 9.5) {
                                        if (x[0] <= 8.5) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[7] <= 60.5) {
                                                if (x[5] <= 0.9087767004966736) {
                                                    votes[3] += 1;
                                                }

                                                else {
                                                    votes[1] += 1;
                                                }
                                            }

                                            else {
                                                if (x[4] <= 10.990000247955322) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    votes[3] += 1;
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[2] <= 12.5) {
                                            if (x[4] <= 13.019999980926514) {
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
                                    votes[2] += 1;
                                }
                            }

                            else {
                                if (x[4] <= 14.059999942779541) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        else {
                            if (x[3] <= 15.5) {
                                votes[0] += 1;
                            }

                            else {
                                if (x[4] <= 15.025000095367432) {
                                    votes[0] += 1;
                                }

                                else {
                                    if (x[5] <= 0.2277158945798874) {
                                        if (x[4] <= 15.045000076293945) {
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

                        // tree #9
                        if (x[2] <= 13.5) {
                            if (x[3] <= 14.5) {
                                if (x[4] <= 10.329999923706055) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[4] <= 10.639999866485596) {
                                        if (x[5] <= 0.7983881533145905) {
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
                                if (x[2] <= 9.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    if (x[5] <= 0.608320415019989) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[0] <= 10.5) {
                                            if (x[7] <= 48.5) {
                                                votes[1] += 1;
                                            }

                                            else {
                                                votes[3] += 1;
                                            }
                                        }

                                        else {
                                            if (x[2] <= 11.5) {
                                                if (x[7] <= 52.5) {
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
                        }

                        else {
                            if (x[3] <= 18.0) {
                                if (x[6] <= 12.0) {
                                    if (x[6] <= 5.5) {
                                        if (x[5] <= 0.07000000029802322) {
                                            votes[0] += 1;
                                        }

                                        else {
                                            if (x[4] <= 15.045000076293945) {
                                                if (x[5] <= 0.15529361367225647) {
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

                                    else {
                                        votes[0] += 1;
                                    }
                                }

                                else {
                                    if (x[6] <= 38.0) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        if (x[5] <= 0.29991665482521057) {
                                            votes[0] += 1;
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

                        // tree #10
                        if (x[7] <= 88.0) {
                            if (x[3] <= 19.0) {
                                if (x[3] <= 14.5) {
                                    if (x[3] <= 10.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[4] <= 10.329999923706055) {
                                            votes[1] += 1;
                                        }

                                        else {
                                            if (x[0] <= 9.5) {
                                                if (x[6] <= 41.0) {
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
                                    if (x[2] <= 9.5) {
                                        votes[1] += 1;
                                    }

                                    else {
                                        if (x[4] <= 13.25) {
                                            votes[3] += 1;
                                        }

                                        else {
                                            if (x[6] <= 26.5) {
                                                votes[2] += 1;
                                            }

                                            else {
                                                if (x[4] <= 14.949999809265137) {
                                                    votes[1] += 1;
                                                }

                                                else {
                                                    if (x[6] <= 97.0) {
                                                        votes[0] += 1;
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
                                if (x[6] <= 48.5) {
                                    if (x[0] <= 13.0) {
                                        votes[3] += 1;
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

                        else {
                            if (x[3] <= 15.5) {
                                votes[0] += 1;
                            }

                            else {
                                if (x[6] <= 5.5) {
                                    if (x[6] <= 4.5) {
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