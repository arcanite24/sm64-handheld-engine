static const struct Animation anim_01[] = {
    1,
    189,
    0,
    0,
    0x50,
    ANIMINDEX_NUMPARTS(anim_01_02_indices),
    anim_01_02_values,
    anim_01_02_indices,
    0,
};

static const struct Animation anim_02[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_01_02_indices),
    anim_01_02_values,
    anim_01_02_indices,
    0,
};


ROM_ASSET_LOAD_ANIM(anim_01_02_indices, 0x004ed200, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_01_02_values, 0x004ed2fc, 6576, 0x00000000, 6576);
