
        #ifndef __WINDOW__140654142461136
        #define __WINDOW__140654142461136

        class Window {
            public:
                const uint16_t features_count = 8;
                float features[8];

                /**
                 * Extract features
                 */
                 bool transform(float *x, float *dest = NULL) {
                    // append source to queue
                    memcpy(queue + head, x, sizeof(float) * 1);
                    head += 1;

                    if (head != 60) {
                        return false;
                    }

                    // extract features for each axis
                    uint16_t feature_idx = 0;

                    for (uint16_t j = 0; j < 1; j++) {
                        float m = queue[j];
                        float M = m;
                        float abs_m = abs(m);
                        float abs_M = abs_m;
                        float mean = m;
                        float std = 0;
                        float count_above_mean = 0;
                        float count_below_mean = 0;

                        // first-order features
                        for (uint16_t i = j + 1; i < 60; i += 1) {
                            float xi = queue[i];
                            float abs_xi = abs(xi);

                            mean += xi;

                            if (xi < m) m = xi;
                            if (xi > M) M = xi;
                            if (abs_xi < abs_m) abs_m = abs_xi;
                            if (abs_xi > abs_M) abs_M = abs_xi;
                        }

                        mean /= 60;

                        // second-order features
                        for (uint16_t i = j; i < 60; i += 1) {
                            float xi = queue[i];
                            float x0 = xi - mean;

                            std += x0 * x0;

                            if (x0 > 0) count_above_mean += 1;
                            else count_below_mean += 1;
                        }

                        std = sqrt(std / 60);

                        features[feature_idx++] = m;
                        features[feature_idx++] = M;
                        features[feature_idx++] = abs_m;
                        features[feature_idx++] = abs_M;
                        features[feature_idx++] = mean;
                        features[feature_idx++] = std;
                        features[feature_idx++] = count_above_mean;
                        features[feature_idx++] = count_below_mean;
                    }

                    // copy to dest, if any
                    if (dest != NULL) memcpy(dest, features, sizeof(float) * 8);

                    // shift
                    memcpy(queue, queue + 15, sizeof(float) * 45);
                    head -= 15;

                    return true;
                 }

                 /**
                  * Clear the current data of the window
                  */
                 void clear() {
                    head = 0;
                 }

            protected:
                uint16_t head = 0;
                float queue[60];
        };

        #endif
        