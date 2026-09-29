static const struct Animation anim_8E[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_8E_8F_indices),
    anim_8E_8F_values,
    anim_8E_8F_indices,
    0,
};

static const struct Animation anim_8F[] = {
    1,
    189,
    1,
    0,
    0x14,
    ANIMINDEX_NUMPARTS(anim_8E_8F_indices),
    anim_8E_8F_values,
    anim_8E_8F_indices,
    0,
};


ROM_ASSET_LOAD_ANIM(anim_8E_8F_indices, 0x00554ac4, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_8E_8F_values, 0x00554bc0, 1618, 0x00000000, 1618);
