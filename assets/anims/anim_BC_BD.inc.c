static const struct Animation anim_BC[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_BC_BD_indices),
    anim_BC_BD_values,
    anim_BC_BD_indices,
    0,
};

static const struct Animation anim_BD[] = {
    1,
    189,
    1,
    0,
    0x12,
    ANIMINDEX_NUMPARTS(anim_BC_BD_indices),
    anim_BC_BD_values,
    anim_BC_BD_indices,
    0,
};


ROM_ASSET_LOAD_ANIM(anim_BC_BD_indices, 0x0056e3ac, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_BC_BD_values, 0x0056e4a8, 1528, 0x00000000, 1528);
