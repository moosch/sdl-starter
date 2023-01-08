#ifndef _GRAPHICS_TYPES_H_
#define _GRAPHICS_TYPES_H_

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} rgba;

typedef struct vec3d {
  float x;
  float y;
  float z;
  float w; // Need a 4th term to perform sensible matrix vector multiplication
} vec3d;

typedef struct {
  vec3d p[3];
  rgba color;
} triangle;

typedef struct {
  triangle *tris; // Array of triangles
  u32 size;
} mesh;

typedef struct {
  float m[4][4];
} mat4x4;

#endif
