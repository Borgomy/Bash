/*
Функция EncryptECB реализует алгоритм зашифрования открытого текста.
char* nameInputFile - указатель на массив символов, содержащий имя фаила с открытым текстом;
char* nameOutputFile - указатель на массив символов, содержащий имя фаила, в который нужно записать закрытый текст;
uint32_t* key - указатель на 256 битный ключ;
int modePaddingNulls - номер процедуры дополнения(по ГОСТ 34.13-2015).
*/
int EncryptECB(char* nameInputFile, char* nameOutputFile, uint32_t* key , int modePaddingNulls)
{
    //open files
    FILE* input = fopen(nameInputFile, "r");
    FILE* output = fopen(nameOutputFile, "w");
    if(input == NULL || output == NULL)
    {
        printf("error open files\n");
        fclose(input);
        fclose(output);
        return 2 ;
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
            fclose(input);
            fclose(output);
            return 3;
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
        return 0;
    }
    block = schemeFeistel(block, ptrOnArrKeys);
    fwrite(&block, 8, 1, output);
    //close files
    fclose(input);
    fclose(output);
    return 0;
}
/*
Функция DecryptECB реализует алгоритм расшифрования открытого текста.
char* nameInputFile - указатель на массив символов, содержащий имя фаила с открытым текстом;
char* nameOutputFile - указатель на массив символов, содержащий имя фаила, в который нужно записать закрытый текст;
uint32_t* key - указатель на 256 битный ключ;
int modePaddingNulls - номер процедуры дополнения(по ГОСТ 34.13-2015);
uint8_t countByteInLastBlock - 8-ми битное беззнаковое число, являющееся количеством байт в последнем блоке при расшифровании(нужно для первой процедуры дополнения).
*/
int DecryptECB(char* nameInputFile, char* nameOutputFile, uint32_t* key , int modePaddingNulls,  uint8_t countByteInLastBlock)
{
    //open files
    FILE* input = fopen(nameInputFile, "r");
    FILE* output = fopen(nameOutputFile, "w");
    if(input == NULL || output == NULL)
    {
        printf("error open files\n");
        return 2;
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
            return 3;
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
    return 0;
}
/*

*/
uint64_t readLastBlockInputFile(FILE* input, int modePaddingNulls, uint8_t countReadByte)
{
    uint8_t dataInBytes[8];
    fread(dataInBytes, countReadByte, 1, input);
    return procPaddingNulls(dataInBytes, 8 - countReadByte, modePaddingNulls);
}
/*
Функция procPaddingNulls - реализует процедуры дополнения, описанные в ГОСТ Р 34.13-2015, кроме условий полного блока.
Принимает на вход:
uint8_t* data - указатель на ячейку памяти с читаемым последним блоком;
int countAddByte - целое число, обозначающее количество байт, которые нужно добавить в блок;
int mode - режим добавления.
*/
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
    return 1;
}
/*
Функция countBytesForWrite обеспечивает правильное расшифрование закрытого текста, а имеено возвращает количество байт последнего блока, которое нужно записать в фаил, чтобы получить открытый текст.
uint8_t* blockInBytes -указатель на ячейку памяти с последним блоком закрытого текста.
*/
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
