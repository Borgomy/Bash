/*********************************************************/
int EncryptECB(char* nameInputFile, char* nameOutputFile, uint32_t* key , int modePaddingNulls)
{
    //open files
    FILE* input = fopen(nameInputFile, "r");
    FILE* output = fopen(nameOutputFile, "w");
    if(input == NULL || output == NULL)
    {
        printf("error open files\n");
        return -1;
    }
    //get count full blocks
    uint64_t sizeInputFile = getSizeInputFile(input);
    uint32_t countFullBlocks = sizeInputFile/8;
    //create iteration keys
    uint32_t ptrOnArrKeys[32];
    createEncryptKeys(ptrOnArrKeys, key);
    //cipher full bloks
    uint64_t block;
    for(uint64_t iteration = 0; iteration<countFullBlocks; iteration++)
    {
        if(fread(&block, 8, 1, input) != 1)
        {
            printf("error in fread\n");
            return -2;
        }
        block = schemeFeistel(block, ptrOnArrKeys);
        fwrite(&block, 8, 1, output);
    }
    //cipher last block
    uint8_t countReadByte = sizeInputFile%8;
    if(countReadByte != 0)
    {
        block = readLastBlockInputFile(input, modePaddingNulls, countReadByte);
    }
    else if(modePaddingNulls == PROC_ADD_NULLS_2)
    {
        block = 0x0000000000000001;
    }
    else
    {
        fclose(input);
        fclose(output);
        return 1;
    }
    block = schemeFeistel(block, ptrOnArrKeys);
    fwrite(&block, 8, 1, output);
    //close files
    fclose(input);
    fclose(output);
    return 1;
}
/*********************************************************/
int DecryptECB(char* nameInputFile, char* nameOutputFile, uint32_t* key , int modePaddingNulls,  uint8_t countByteInLastBlock)
{
    //open files
    FILE* input = fopen(nameInputFile, "r");
    FILE* output = fopen(nameOutputFile, "w");
    if(input == NULL || output == NULL)
    {
        printf("error open files\n");
        return -1;
    }
    //get count full blocks
    uint64_t sizeInputFile = getSizeInputFile(input);
    uint32_t countFullBlocks = sizeInputFile/8 - 1;
    //create iteration keys
    uint32_t ptrOnArrKeys[32];
    createDecryptKeys(ptrOnArrKeys, key);    
    //cipher full bloks
    uint64_t block;
    for(uint64_t iteration = 0; iteration<countFullBlocks; iteration++)
    {
        if(fread(&block, 8, 1, input) != 1)
        {
            printf("error in fread\n");
            return -2;
        }
        block = schemeFeistel(block, ptrOnArrKeys);
        fwrite(&block, 8, 1, output);
    }
    //cipher last block
    fread(&block, 8, 1, input);
    block = schemeFeistel(block, ptrOnArrKeys);
    if(modePaddingNulls == PROC_ADD_NULLS_2)
    {
        fwrite(&block, countBytesForWrite((uint8_t*)&block), 1, output);
    }
    else 
    {
        fwrite(&block, countByteInLastBlock, 1, output);   
    }
    //close files
    fclose(input);
    fclose(output);
    return 1;
}
/*********************************************************/
uint64_t readLastBlockInputFile(FILE* input, int modePaddingNulls, uint8_t countReadByte)
{
    uint8_t dataInBytes[8];
    fread(dataInBytes, countReadByte, 1, input);
    return procPaddingNulls(dataInBytes, 8 - countReadByte, modePaddingNulls);
}
/*********************************************************/
uint64_t procPaddingNulls(uint8_t* data, int countAddByte, int mode)
{
    if(mode == PROC_ADD_NULLS_1)
    {
        for(int index = 8 - countAddByte; index<8; index++)
        {
            data[index] = 0;
        }
        return *((uint64_t*)data);
    }
    else
    {
        data[8 - countAddByte] = 1;
        for(int index = 8 - (countAddByte - 1); index<8; index++)
        {
            data[index] = 0;
        }
        return *((uint64_t*)data);
    }
    return 0;
}
/*********************************************************/
uint8_t countBytesForWrite(uint8_t* blockInBytes)
{
    int indexByte = 7;
    while(blockInBytes[indexByte] != 1)
    {
        indexByte--;
    }
    return indexByte; // count bytes in open text
}
/*********************************************************/
