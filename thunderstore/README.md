# Deku Glide
This mod gives Deku Link the option to glide after jumping from a ledge. Press A in midair and he'll float forward using the same mechanic as Deku Flowers.

It’s a small change that goes a long way into making Deku Link feel more useful, giving players more reason to stay in Deku form.

![preview](https://github.com/user-attachments/assets/aff2cc6d-4a80-4c07-a9a2-d87544d00bdd)

## Header
```
RECOMP_IMPORT("mm_deku_glide", bool IsCheatingEnabled());

#define ON_DEKU_GLIDE RECOMP_CALLBACK("mm_deku_glide", onDekuGlide)
```