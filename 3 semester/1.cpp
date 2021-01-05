int
bitcount(STYPE value)
{
    UTYPE v = (UTYPE)value;
    int result = 0;
    while(v){
        result += v & 1;
        v >>= 1;
    }
    return result;
}