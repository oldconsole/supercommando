.include "hdr.asm"

.section ".rodata" superfree
logo_map:
.incbin "data/test.map"
logo_palette:
.incbin "data/test.clr"
interstitial_tiles:
.incbin "data/interstitial/interstitial.dat"
interstitial_palette:
.incbin "data/interstitial/interstitial.clr"
interstitial_continue_map:
.incbin "data/interstitial/continue-x0y0.map"
interstitial_gameover_map:
.incbin "data/interstitial/gameover-x0y0.map"
.ends

.section ".rodata1" superfree
logo_tiles:
.incbin "data/test.dat"
.ends

.section ".rodata2" superfree
level1_tiles:
.incbin "data/level1/level1.dat"
.ends

.section ".rodata3" superfree
level1_palette:
.incbin "data/level1/level1.clr"
level1_map_x0y0:
.incbin "data/level1/level1_map-x0y0.map"
level1_map_x1y0:
.incbin "data/level1/level1_map-x1y0.map"
level1_map_x2y0:
.incbin "data/level1/level1_map-x2y0.map"
level1_map_x3y0:
.incbin "data/level1/level1_map-x3y0.map"
level1_map_x4y0:
.incbin "data/level1/level1_map-x4y0.map"
level1_map_x5y0:
.incbin "data/level1/level1_map-x5y0.map"
level1_map_x6y0:
.incbin "data/level1/level1_map-x6y0.map"
level1_map_x7y0:
.incbin "data/level1/level1_map-x7y0.map"
level1_map_x8y0:
.incbin "data/level1/level1_map-x8y0.map"
level1_map_x9y0:
.incbin "data/level1/level1_map-x9y0.map"
level1_map_x10y0:
.incbin "data/level1/level1_map-x10y0.map"
level1_map_x11y0:
.incbin "data/level1/level1_map-x11y0.map"
level1_map_x12y0:
.incbin "data/level1/level1_map-x12y0.map"
level1_map_x13y0:
.incbin "data/level1/level1_map-x13y0.map"
level1_map_x14y0:
.incbin "data/level1/level1_map-x14y0.map"
.ends

.section ".rodata4" superfree
level1_background1_map:
.incbin "data/level1/background1-x0y0.map"
level1_background2_map:
.incbin "data/level1/background2-x0y0.map"
level1_object:
.incbin "data/level1/level1_object.obj"
level1_collision_x0y0:
.incbin "data/level1/level1_collision-x0y0.col"
level1_collision_x1y0:
.incbin "data/level1/level1_collision-x1y0.col"
level1_collision_x2y0:
.incbin "data/level1/level1_collision-x2y0.col"
level1_collision_x3y0:
.incbin "data/level1/level1_collision-x3y0.col"
level1_collision_x4y0:
.incbin "data/level1/level1_collision-x4y0.col"
level1_collision_x5y0:
.incbin "data/level1/level1_collision-x5y0.col"
level1_collision_x6y0:
.incbin "data/level1/level1_collision-x6y0.col"
level1_collision_x7y0:
.incbin "data/level1/level1_collision-x7y0.col"
level1_collision_x8y0:
.incbin "data/level1/level1_collision-x8y0.col"
level1_collision_x9y0:
.incbin "data/level1/level1_collision-x9y0.col"
level1_collision_x10y0:
.incbin "data/level1/level1_collision-x10y0.col"
level1_collision_x11y0:
.incbin "data/level1/level1_collision-x11y0.col"
level1_collision_x12y0:
.incbin "data/level1/level1_collision-x12y0.col"
level1_collision_x13y0:
.incbin "data/level1/level1_collision-x13y0.col"
level1_collision_x14y0:
.incbin "data/level1/level1_collision-x14y0.col"
.ends
