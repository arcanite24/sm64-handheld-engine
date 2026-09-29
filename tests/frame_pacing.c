#include <assert.h>
#include <math.h>
#include "src/pc/gfx/android_frame_pacing.h"

int main(void) {
    assert(android_swap_interval(60.0f) == 1);
    assert(android_swap_interval(120.0f) == 2);
    assert(android_swap_interval(0.0f) == 0);
    assert(android_swap_interval(90.0f) == 0);
    assert(android_swap_interval(240.0f) == 0);
    assert(android_swap_interval(INFINITY) == 0);
    assert(android_swap_interval(NAN) == 0);
    return 0;
}
