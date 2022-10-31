#ifndef GPUFUNC_H
#define GPUFUNC_H
class useGPU
{
public:
	void adding(int* c, const int* a, const int* b, unsigned int size);
	int ImageToGrayGpu(unsigned char* imageRGBA, int width, int height);
};
#endif