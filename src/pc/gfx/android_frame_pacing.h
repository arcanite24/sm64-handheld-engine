#ifndef ANDROID_FRAME_PACING_H
#define ANDROID_FRAME_PACING_H

// A failed or ambiguous vsync probe uses the 60 FPS timer instead.
static inline int android_frame_multiplier(float refresh_hz) {
    if (refresh_hz >= 50.0f && refresh_hz <= 70.0f) return 1;
    if (refresh_hz >= 105.0f && refresh_hz <= 135.0f) return 2;
    return 0;
}

#endif
