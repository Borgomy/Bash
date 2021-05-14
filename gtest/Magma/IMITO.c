uint64_t createHelpingKey(uint32_t* ptrOnArrKeys, int numberOfKeyToCreate)
{
    uint64_t key = schemeFeistel(0, ptrOnArrKeys);
    //create First  key 
    if(!((key & (0b1<<63))>>63))
    {
        key = key<<1;
    }
    else
    {
        key = (key<<1)^0b11011;
    }
    if(numberOfKeyToCreate == CREATE_KEY_1)
    {
        return key;
    }
    //create Second key
    if(!(key & (0b1<<63)))
    {
        key = key<<1;
    }
    else
    {
        key = (key<<1)^0b11011;
    }
    return key;
}
uint64_t getMAC(char* nameInputFile, uint32_t* key , uint8_t sizeMAC)
{
    //open input file
    FILE* input = fopen(nameInputFile, "r");
    if(input == NULL)
    {
        printf("error open files\n");
        return -1;
    }
    //get count full blocks
    uint64_t tmp = getSizeInputFile(input);
    uint8_t residue = tmp%8;
    uint32_t countFullBlocks = residue == 0 ? tmp/8 - 1 : tmp/8;
    //create iterationKeys
    uint32_t ptrOnArrKeys[32];
    createEncryptKeys(ptrOnArrKeys, key);
    //create MAC
    uint64_t block; 
    tmp = 0;
    for(int iteration = 0; iteration<countFullBlocks; iteration++)
    {
        fread(&block, 8, 1, input);
        block ^= tmp;
        block = schemeFeistel(block, ptrOnArrKeys);
        tmp = block;
    }
    //read last block and create helping key
    uint64_t helpingKey;
    if(residue != 0)
    {
        block = readLastBlockInputFile(input, PROC_ADD_NULLS_3, residue);
        helpingKey = createHelpingKey(ptrOnArrKeys,CREATE_KEY_2);
    }
    else
    {
        fread(&block, 8, 1, input);
        helpingKey = createHelpingKey(ptrOnArrKeys, CREATE_KEY_1);
    }
    fclose(input);
    //create need key
    block ^= tmp^helpingKey;
    block = schemeFeistel(block, ptrOnArrKeys);
    return block>>(64 - sizeMAC);
}
