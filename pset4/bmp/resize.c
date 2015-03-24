/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int resizefactor = atoi(argv[1]);
    
    // check resize factor supplied and confirm it is valid, if not, crash
    if (resizefactor < 0 || resizefactor > 100)
    {
        printf("Resize should be between 0 and 100. \n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // bmp header for resized files
    BITMAPFILEHEADER resized_bf;
    BITMAPINFOHEADER resized_bi;
    resized_bf = bf;
    resized_bi = bi;
    resized_bi.biWidth = bi.biWidth * resizefactor;
    resized_bi.biHeight = bi.biHeight * resizefactor;
    
    
    // determine padding for scanlines
    // redesigned for resizing
    int incomingpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outgoingpadding = (4 - (resized_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // image and file size // formula thanks to google code
    resized_bf.bfSize = 54 + resized_bi.biWidth * abs(resized_bi.biHeight) * 3 + abs(resized_bi.biHeight) * outgoingpadding;
    resized_bi.biSizeImage = ((((resized_bi.biWidth * resized_bi.biBitCount) + 31) & ~31) / 8) * abs(resized_bi.biHeight);
    
     // write outfile's BITMAPFILEHEADER
    fwrite(&resized_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&resized_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int u = 0; u < resizefactor; u++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile
                for (int r = 0; r < resizefactor; r++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding from incoming padding, if any
            fseek(inptr, incomingpadding, SEEK_CUR);
    
            // then add it back
            for (int k = 0; k < outgoingpadding; k++)
                fputc(0x00, outptr);
            // seek correctly    
            fseek(inptr, -(bi.biWidth * 3 + incomingpadding ), SEEK_CUR);
        }
        fseek(inptr, bi.biWidth * 3 + incomingpadding, SEEK_CUR);

    }    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
