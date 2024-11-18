#pragma once
#include <stdint.h>

struct StereoSample
{
    float left;
    float right;

    inline StereoSample operator*(float scale) const { return {left * scale, right * scale}; }
};

struct Buzzic2;

struct Buzzic2* Buzzic2Load(const uint8_t* data, uint32_t size);
void Buzzic2Release(struct Buzzic2* buzzic2);
void Buzzic2Reset(struct Buzzic2* buzzic2);
uint32_t Buzzic2DurationMs(struct Buzzic2* buzzic2);
uint32_t Buzzic2NumIntruments(struct Buzzic2* buzzic2);
const char* Buzzic2IntrumentName(struct Buzzic2* buzzic2, uint32_t index);
uint32_t Buzzic2Render(struct Buzzic2* buzzic2, StereoSample* samples, uint32_t numSamples);
