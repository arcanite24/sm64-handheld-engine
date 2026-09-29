#include <assert.h>
#include <math.h>
#include "src/pc/gfx/android_frame_pacing.h"

int main(void) {
    assert(android_frame_multiplier(60.0f) == 1);
    assert(android_frame_multiplier(120.0f) == 2);
    assert(android_frame_multiplier(0.0f) == 0);
    assert(android_frame_multiplier(90.0f) == 0);
    assert(android_frame_multiplier(240.0f) == 0);
    assert(android_frame_multiplier(INFINITY) == 0);
    assert(android_frame_multiplier(NAN) == 0);
    return 0;
}
