partition(arr[], low, high)
{
    // pivot (Element to be placed at right position)
    pivot = arr[high];  
    i = (low - 1)  // Index of smaller element

    for (j = low; j <= high- 1; j++)
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
            swap arr[++i] and arr[j]
    swap arr[i + 1] and arr[high])
    return (i + 1)
}

/*Radix sort an array of Strings
Assume all are all ASCII
Assume all have same length*/
void radixSortA( vector<string> & arr, int stringLen )
{
    const int BUCKETS = 256;
    vector<vector<string>> buckets(BUCKETS);

    for(int pos = stringLen - 1; pos >= 0; --pos)
    {
        for( string  &s:arr)
        buckets[s[pos]].push_back(move(s));

        int idx = 0;
        for(auto & thisBucket : buckets)
        {
            for(string & s : thisBucket)
                arr[idx++] = move(s);
            thisBucket.clear();
        }
    }
}
