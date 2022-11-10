// read a BMP file into a Texture:

#define VERBOSE false

unsigned char *	BmpToTexture( char *, int *, int * );
int		ReadInt( FILE * );
short		ReadShort( FILE * );

#define BMP_MAGIC_NUMBER 0x4d42
#ifndef BI_RGB
#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#endif
// #include "../MyLibrary/util.h"
// bmp file header:
struct bmfh
{
    short bfType; // BMP_MAGIC_NUMBER = "BM"
    int bfSize;   // size of this file in bytes
    short bfReserved1;
    short bfReserved2;
    int bfOffBytes; // # bytes to get to the start of the per-pixel data
} FileHeader;

// bmp info header:
struct bmih
{
    int biSize;        // info header size, should be 40
    int biWidth;       // image width
    int biHeight;      // image height
    short biPlanes;    // #color planes, should be 1
    short biBitCount;  // #bits/pixel, should be 1, 4, 8, 16, 24, 32
    int biCompression; // BI_RGB, BI_RLE4, BI_RLE8
    int biSizeImage;
    int biXPixelsPerMeter;
    int biYPixelsPerMeter;
    int biClrUsed; // # colors in the palette
    int biClrImportant;
} InfoHeader;

// read a BMP file into a Texture:

unsigned char *
BmpToTexture(char *filename, int *width, int *height)
{
    FILE *fp;
#ifdef _WIN32
    errno_t err = fopen_s(&fp, filename, "rb");
    if (err != 0)
    {
        fprintf(stderr, "Cannot open Bmp file '%s'\n", filename);
        return NULL;
    }
#else
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open Bmp file '%s'\n", filename);
        return NULL;
    }
#endif

    FileHeader.bfType = ReadShort(fp);

    // if bfType is not BMP_MAGIC_NUMBER, the file is not a bmp:

    if (VERBOSE)
        fprintf(stderr, "FileHeader.bfType = 0x%0x = \"%c%c\"\n",
                FileHeader.bfType, FileHeader.bfType & 0xff, (FileHeader.bfType >> 8) & 0xff);
    if (FileHeader.bfType != BMP_MAGIC_NUMBER)
    {
        fprintf(stderr, "Wrong type of file: 0x%0x\n", FileHeader.bfType);
        fclose(fp);
        return NULL;
    }

    FileHeader.bfSize = ReadInt(fp);
    if (VERBOSE)
        fprintf(stderr, "FileHeader.bfSize = %d\n", FileHeader.bfSize);

    FileHeader.bfReserved1 = ReadShort(fp);
    FileHeader.bfReserved2 = ReadShort(fp);

    FileHeader.bfOffBytes = ReadInt(fp);

    InfoHeader.biSize = ReadInt(fp);
    InfoHeader.biWidth = ReadInt(fp);
    InfoHeader.biHeight = ReadInt(fp);

    const int nums = InfoHeader.biWidth;
    const int numt = InfoHeader.biHeight;

    InfoHeader.biPlanes = ReadShort(fp);

    InfoHeader.biBitCount = ReadShort(fp);
    if (VERBOSE)
        fprintf(stderr, "InfoHeader.biBitCount = %d\n", InfoHeader.biBitCount);

    InfoHeader.biCompression = ReadInt(fp);
    if (VERBOSE)
        fprintf(stderr, "InfoHeader.biCompression = %d\n", InfoHeader.biCompression);

    InfoHeader.biSizeImage = ReadInt(fp);
    if (VERBOSE)
        fprintf(stderr, "InfoHeader.biSizeImage = %d\n", InfoHeader.biSizeImage);

    InfoHeader.biXPixelsPerMeter = ReadInt(fp);
    InfoHeader.biYPixelsPerMeter = ReadInt(fp);

    InfoHeader.biClrUsed = ReadInt(fp);
    if (VERBOSE)
        fprintf(stderr, "InfoHeader.biClrUsed = %d\n", InfoHeader.biClrUsed);

    InfoHeader.biClrImportant = ReadInt(fp);

    // fprintf( stderr, "Image size found: %d x %d\n", ImageWidth, ImageHeight );

    // pixels will be stored bottom-to-top, left-to-right:
    unsigned char *texture = new unsigned char[3 * nums * numt];
    if (texture == NULL)
    {
        fprintf(stderr, "Cannot allocate the texture array!\n");
        return NULL;
    }

    // extra padding bytes:

    int requiredRowSizeInBytes = 4 * ((InfoHeader.biBitCount * InfoHeader.biWidth + 31) / 32);
    if (VERBOSE)
        fprintf(stderr, "requiredRowSizeInBytes = %d\n", requiredRowSizeInBytes);

    int myRowSizeInBytes = (InfoHeader.biBitCount * InfoHeader.biWidth + 7) / 8;
    if (VERBOSE)
        fprintf(stderr, "myRowSizeInBytes = %d\n", myRowSizeInBytes);

    int numExtra = requiredRowSizeInBytes - myRowSizeInBytes;
    if (VERBOSE)
        fprintf(stderr, "New NumExtra padding = %d\n", numExtra);

    // this function does not support compression:

    if (InfoHeader.biCompression != 0)
    {
        fprintf(stderr, "Wrong type of image compression: %d\n", InfoHeader.biCompression);
        fclose(fp);
        return NULL;
    }

    // we can handle 24 bits of direct color:
    if (InfoHeader.biBitCount == 24)
    {
        rewind(fp);
        fseek(fp, FileHeader.bfOffBytes, SEEK_SET);
        int t;
        unsigned char *tp;
        for (t = 0, tp = texture; t < numt; t++)
        {
            for (int s = 0; s < nums; s++, tp += 3)
            {
                *(tp + 2) = fgetc(fp); // b
                *(tp + 1) = fgetc(fp); // g
                *(tp + 0) = fgetc(fp); // r
            }

            for (int e = 0; e < numExtra; e++)
            {
                fgetc(fp);
            }
        }
    }

    // we can also handle 8 bits of indirect color:
    if (InfoHeader.biBitCount == 8 && InfoHeader.biClrUsed == 256)
    {
        struct rgba32
        {
            unsigned char r, g, b, a;
        };
        struct rgba32 *colorTable = new struct rgba32[InfoHeader.biClrUsed];

        rewind(fp);
        fseek(fp, sizeof(struct bmfh) + InfoHeader.biSize - 2, SEEK_SET);
        for (int c = 0; c < InfoHeader.biClrUsed; c++)
        {
            colorTable[c].r = fgetc(fp);
            colorTable[c].g = fgetc(fp);
            colorTable[c].b = fgetc(fp);
            colorTable[c].a = fgetc(fp);
            if (VERBOSE)
                fprintf(stderr, "%4d:\t0x%02x\t0x%02x\t0x%02x\t0x%02x\n",
                        c, colorTable[c].r, colorTable[c].g, colorTable[c].b, colorTable[c].a);
        }

        rewind(fp);
        fseek(fp, FileHeader.bfOffBytes, SEEK_SET);
        int t;
        unsigned char *tp;
        for (t = 0, tp = texture; t < numt; t++)
        {
            for (int s = 0; s < nums; s++, tp += 3)
            {
                int index = fgetc(fp);
                *(tp + 0) = colorTable[index].r; // r
                *(tp + 1) = colorTable[index].g; // g
                *(tp + 2) = colorTable[index].b; // b
            }

            for (int e = 0; e < numExtra; e++)
            {
                fgetc(fp);
            }
        }

        delete[] colorTable;
    }

    fclose(fp);

    *width = nums;
    *height = numt;
    return texture;
}

int ReadInt(FILE *fp)
{
    const unsigned char b0 = fgetc(fp);
    const unsigned char b1 = fgetc(fp);
    const unsigned char b2 = fgetc(fp);
    const unsigned char b3 = fgetc(fp);
    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

short ReadShort(FILE *fp)
{
    const unsigned char b0 = fgetc(fp);
    const unsigned char b1 = fgetc(fp);
    return (b1 << 8) | b0;
}

// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void HsvRgb(float hsv[3], float rgb[3])
{
    // guarantee valid input:

    float h = hsv[0] / 60.f;
    while (h >= 6.)
        h -= 6.;
    while (h < 0.)
        h += 6.;

    float s = hsv[1];
    if (s < 0.)
        s = 0.;
    if (s > 1.)
        s = 1.;

    float v = hsv[2];
    if (v < 0.)
        v = 0.;
    if (v > 1.)
        v = 1.;

    // if sat==0, then is a gray:

    if (s == 0.0)
    {
        rgb[0] = rgb[1] = rgb[2] = v;
        return;
    }

    // get an rgb from the hue itself:

    float i = (float)floor(h);
    float f = h - i;
    float p = v * (1.f - s);
    float q = v * (1.f - s * f);
    float t = v * (1.f - (s * (1.f - f)));

    float r = 0., g = 0., b = 0.; // red, green, blue
    switch ((int)i)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;

    case 1:
        r = q;
        g = v;
        b = p;
        break;

    case 2:
        r = p;
        g = v;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = v;
        break;

    case 4:
        r = t;
        g = p;
        b = v;
        break;

    case 5:
        r = v;
        g = p;
        b = q;
        break;
    }

    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

// void Cross(float v1[3], float v2[3], float vout[3])
// {
//     float tmp[3];
//     tmp[0] = v1[1] * v2[2] - v2[1] * v1[2];
//     tmp[1] = v2[0] * v1[2] - v1[0] * v2[2];
//     tmp[2] = v1[0] * v2[1] - v2[0] * v1[1];
//     vout[0] = tmp[0];
//     vout[1] = tmp[1];
//     vout[2] = tmp[2];
// }

float Dot(float v1[3], float v2[3])
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

// float Unit(float vin[3], float vout[3])
// {
//     float dist = vin[0] * vin[0] + vin[1] * vin[1] + vin[2] * vin[2];
//     if (dist > 0.0)
//     {
//         dist = sqrtf(dist);
//         vout[0] = vin[0] / dist;
//         vout[1] = vin[1] / dist;
//         vout[2] = vin[2] / dist;
//     }
//     else
//     {
//         vout[0] = vin[0];
//         vout[1] = vin[1];
//         vout[2] = vin[2];
//     }
//     return dist;
// }
