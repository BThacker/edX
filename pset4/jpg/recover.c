/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
  // we need to open the file yo
  FILE* recovered = fopen("card.raw", "r");

  if (recovered == NULL)
  {
    // If theres a problem, close the file and stop prog
    fclose(recovered);
    fprintf(stderr, "Failure on file read.\n");
    return 1;
  }

  // check for jpegs based on jpeg signature
  uint8_t jpg1[4] = {0xff, 0xd8, 0xff, 0xe0};
  uint8_t jpg2[4] = {0xff, 0xd8, 0xff, 0xe1};

  int count = 0;
  int open = 0;
  FILE* outfile;

  // read the file
  uint8_t buff[512];
  uint8_t checked[4];
  fread(buff, 512, 1, recovered);

  while (fread(buff, 512, 1, recovered) > 0)
  {
    for(int i = 0; i < 4; ++i)
    {
      checked[i] = buff[i];
    }

    // check for jpg

    if ((memcmp(jpg1, checked, 4) == 0 ) || (memcmp(jpg2, checked, sizeof(checked)) == 0))
    {
      // filename
      char filename[8];
      sprintf(filename, "%03d.jpg", count);

      if (open == 0)
      {
        outfile = fopen(filename, "w");
        fwrite(buff, sizeof(buff), 1, outfile);
        open = 1;
      }
      // once opened 
      if(open == 1)
      {
        fclose(outfile);
        outfile = fopen(filename, "w");
        fwrite(buff, sizeof(buff), 1, outfile);
        count++;
      }
    }
    else
    {
      if (open == 1)
      {
        fwrite(buff, sizeof(buff), 1, outfile);
      }
    }

    }
    // close files to prevent further issues 
    if (outfile)
    {
      fclose(outfile);
    }
    fclose(recovered);
    return 0;
 }

