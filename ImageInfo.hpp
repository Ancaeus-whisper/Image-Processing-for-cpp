#pragma once

namespace image_lib{
struct Color{float r,g,b;float a=1.0f;};
struct Vector{float x=0.0f;float y=0.0f;};

class ImageInfo{
    public:
      Color color;
      Vector vector;
};
}