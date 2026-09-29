#ifndef ANDROID_FRAME_PACING_H
#define ANDROID_FRAME_PACING_H

// A failed or ambiguous vsync probe uses the 60 FPS timer instead.
static inline int android_swap_interval(float refresh_hz) {
    if (refresh_hz >= 50.0f && refresh_hz <= 70.0f) return 1;
    if (refresh_hz >= 105.0f && refresh_hz <= 135.0f) return 2;
    return 0;
}

// A long render stall should cost one late frame, not a burst of catch-up drops.
static inline double android_resync_frame_deadline(double last_time, double ticks, double frame_time) {
    return ticks > last_time + 2.0 * frame_time ? ticks - frame_time : last_time;
}

#endif
