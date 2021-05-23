#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main()
{
    /*FILE* file = fopen("/dev/random", "r");
    if(file == NULL)
    {
        printf("error in open randBytes\n");
        return 1;
    }
    if (fread(bytesOfKey, 4, 8, file) != 8)
    {
        printf("error in fread\n");
        return 2;
    }
    fclose(file);
   */
    uint32_t bytesOfKey[8];
    srand(time(NULL));
    for(int index = 0; index < 8; index ++)
    {
        bytesOfKey[index] = rand()%0xffffffff;
    }
    char NameFile[256] = "FileWithByteNumber0";
    FILE* file = fopen("key.key", "w");
    if (fwrite(bytesOfKey, 4, 8, file) != 8)
    {
        printf("error in fwrite\n");
        return 3;
    }
    fclose(file);
    for(char index = 0; index < 8; index++)
    {
        NameFile[18] = index + '0';
        file = fopen(NameFile, "w");
        if(file == NULL)
        {
            printf("error in open files\n");
            return 1;
        }
        if (fwrite(bytesOfKey + index, 4, 1, file) != 1)
        {
            printf("error in fwrite\n");
            return 3;
        }
        fclose(file);
    }
    return 0;
}
