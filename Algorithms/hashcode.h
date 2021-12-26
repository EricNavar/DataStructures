int hashCode(char * s, int length, int initial_value, int multiplier) {
    int i;
    int r = initial_value;
    int a = multiplier;

    char c;

    for  (i = 0; i < length(); i++)
    {
        c =s[i];
        r = (int) c + a*r; 
    }
    return(r);
}