#ifndef Image_CPP
#define Image_CPP
#include <iostream>
#include <fstream>
#include "Mask.cpp"

using namespace std;

class Image
{

public:
	Image();
	Image(int Width, int Height);
	Image(const Image&);
	~Image();
	Image& operator=(const Image&);

	void readImage(const char*);
	void writeImage(const char*);

	Image convolve(const Mask&);
	Image convolveX(const Mask&);
	Image convolveY(const Mask&);

	Image multiply(const Image&);

	float& at(int row, int col) const;

	int getWidth() const { return Width; };
	int getHeight() const { return Height; };

private:
	float** Data;
	int Width;
	int Height;
};

Image::Image()
{
	Width = 0;
	Height = 0;
	Data = NULL;
}

Image::Image(int scr_Width, int scr_Height)
{
	Width = scr_Width;
	Height = scr_Height;

	Data = new float*[Height];
	for (int i = 0; i < Height; i++ )
	{
		Data[i] = new float[Width];
		for(int j = 0; j < Width; j++)
		{
			Data[i][j] = 0;
		}
	}
}

Image::Image(const Image& scr)
{
	Width = scr.Width;
	Height = scr.Height;

	Data = new float*[scr.Height];
	for (int i = 0; i < scr.Height; i++ )
	{
		Data[i] = new float[scr.Width];
		for(int j = 0; j < scr.Width; j++)
		{
			Data[i][j] = scr.Data[i][j];
		}
	}

}

Image::~Image()
{
	for (int i = 0; i < Height; i++)
	{
		delete[] Data[i];
	}
	delete[] Data;
	Data = NULL;

	Width = Height = 0;
}

Image& Image::operator=(const Image& scr)
{
	if(&scr == this)
		return *this;

	if(Width != scr.Width || Height != scr.Height)
	{
		for( int i = 0; i < Height; i++ )
		{
			delete[] Data[i];
		}
		delete[] Data;

		// Copy fields
		Width = scr.Width;
		Height = scr.Height;
	}

	Data = new float*[scr.Height];
	for(int i = 0; i < scr.Height; i++ )
	{
		Data[i] = new float[scr.Width];
		for(int j = 0; j < scr.Width; ++j )
		{
			Data[i][j] = scr.Data[i][j];
		}
	}

	return *this;
}

void Image::readImage(const char* fileName)
{
	char buff[255];
	ifstream fileIn(fileName);

	fileIn >> buff;
	fileIn.get();

	while(fileIn.peek() == '#')
	{
		fileIn.getline(buff, 255);
	}

	fileIn >> Width >> Height >> buff;
	fileIn.get();

	Data = new float*[Height];
	for(int i = 0; i < Height; i++)
	{
		Data[i] = new float[Width];
		for(int j = 0; j < Width; j++)
		{
			Data[i][j] = fileIn.get();
		}
	}
}

void Image::writeImage(const char* fileName)
{
	// Initialize variables
	ofstream fileOut(fileName);

	// Output
	fileOut << "P5\n" << Width << ' ' << Height << '\n' << 255 << '\n';

	// Loop and write
	for( int i = 0; i < Height; ++i )
	{
		for( int j = 0; j < Width; ++j )
		{
			if(Data[i][j] > 255)
			{
				fileOut << (unsigned char) 255;
			}
			else if(Data[i][j] < 0)
			{
				fileOut << (unsigned char) 0;
			}
			else
			{
				fileOut << (unsigned char) Data[i][j];
			}
		}
	}
}

Image Image::convolve(const Mask& mask)
{
	int Half = mask.getDimention() / 2;
	Image resultTemp(Width, Height);
	Image result(Width, Height);

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( j+k >= 0 && j+k < Width )
				{
					resultTemp.Data[i][j] += Data[i][j + k] * mask.at(k + Half);
				}
			}
		}
	}

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( i+k >= 0 && i+k < Height )
				{
					result.Data[i][j] += resultTemp.Data[i + k][j] * mask.at(k + Half);
				}
			}
		}
	}
	return result;
}

Image Image::convolveX(const Mask& mask)
{
	int Half = mask.getDimention() / 2;
	Image result(Width, Height);

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( j+k >= 0 && j+k < Width )
				{
					result.Data[i][j] += Data[i][j + k] * mask.at(k + Half);
				}
			}
		}
	}
	return result;
}

Image Image::convolveY(const Mask& mask)
{
	int Half = mask.getDimention() / 2;
	Image result(Width, Height);

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			for(int k = -Half; k <= Half; k++)
			{
				if( i+k >= 0 && i+k < Height )
				{
					result.Data[i][j] += Data[i + k][j] * mask.at(k + Half);
				}
			}
		}
	}
	return result;
}

Image Image::multiply(const Image& scr)
{
	Image result(Width, Height);

	if( scr.Width != Width || scr.Height != Height )
		return result;

	for(int i = 0; i < Height; i++)
	{
		for(int j = 0; j < Width; j++)
		{
			result.Data[i][j] = Data[i][j] * scr.Data[i][j];
		}
	}
	return result;
}

float& Image::at(int row, int col) const
{
return Data[row][col];
}

#endif