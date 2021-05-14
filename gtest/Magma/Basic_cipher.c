/*********************************************************/
uint32_t S_box(uint32_t rightPart)
{
    int S [8][16]={
    {12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0,  3, 15, 1},
    {6,  8, 2, 3, 9, 10, 5, 12, 1, 14, 4,  7, 11, 13, 0, 15},
    {11, 3, 5, 8, 2, 15, 10, 13,14, 1, 7,  4, 12, 9,  6, 0},
    {12, 8, 2, 1, 13, 4, 15,  6, 7, 0, 10, 5, 3,  14, 9, 11},
    {7, 15, 5, 10, 8, 1, 6,  13, 0, 9, 3,  14, 11,4,  2, 12},
    {5, 13, 15, 6, 9, 2, 12, 10, 11,7, 8,   1, 4, 3, 14, 0},
    {8, 14,  2 ,5 ,6, 9, 1,  12, 15,4, 11,  0, 13,10, 3, 7},
    {1, 7,  14,13, 0, 5, 8,  3,  4, 15,10,  6, 9, 12, 11,2},
    };

    for(int i=0; i<=7; i++)
    {
       rightPart = rightPart & ~(0b1111<<(4*i)) | S[i][ (rightPart & (0b1111<<(4*i)) )>>(4*i) ]<<(4*i) ; //Замена элементов на соответствующие подстановки 
    }  
    return rightPart;   
}
/*********************************************************/
void oneFeistelIteration(uint32_t* leftAndRightPart, uint32_t key)
{
    uint32_t result = S_box( leftAndRightPart[0] + key );
    result = (result & 0b11111111111<<21)>>21 | result<<11; // Циклическое смещение на 11 элементов
    result = leftAndRightPart[1] ^ result;
    leftAndRightPart[1] = leftAndRightPart[0];
    leftAndRightPart[0] = result;
}
/*********************************************************/
void lastFeistelIteration(uint32_t* leftAndRightPart, uint32_t key)
{
    uint32_t result = S_box( leftAndRightPart[0] + key );
    result = (result & 0b11111111111<<21)>>21 | result<<11; // Циклическое смещение на 11 элементов
    result = leftAndRightPart[1] ^ result;
    leftAndRightPart[1] = result;
}
/*********************************************************/
void createEncryptKeys(uint32_t* iterationKeys, uint32_t* key)
{
    int index;
    for(index = 0; index<24; index++)
    {
        iterationKeys[index] = key[7 - index%8];
    }
    for(index = 24; index<32; index++)
    {
        iterationKeys[index] = key[index%8];
    }
}
/*********************************************************/
void createDecryptKeys(uint32_t* iterationKeys, uint32_t* key)
{
    int index;
    for(index = 0; index<8; index++)
    {
        iterationKeys[index] = key[7 - index%8];
    }
    for(index = 8; index<32; index++)
    {
        iterationKeys[index] = key[index%8];
    }
}
/*********************************************************/
uint64_t getSizeInputFile(FILE* input)
{
    uint64_t size;
    fseek(input, 0, SEEK_END);
    size = ftell(input);
    fseek(input, 0, SEEK_SET);
    return size;
}
/*********************************************************/
uint64_t schemeFeistel(uint64_t block, uint32_t* ptrOnArrKeys)
{
    uint32_t* leftAndRightPart = (uint32_t*)&block; // 0 - rightPart, 1 - leftPart 
    for(int iteration = 0; iteration<31; iteration++)
    {
        oneFeistelIteration(leftAndRightPart, ptrOnArrKeys[iteration]);
    }
    //end 1-31 iteration
    lastFeistelIteration(leftAndRightPart, ptrOnArrKeys[31]);
    return block;
}
/*********************************************************/

