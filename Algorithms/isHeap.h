//first element is at index 0
bool isHeap(vector<int> v) 
{ 
    int n = v.size();
    // Start from root and go till the last internal node 
    for (int i=0; i <= (n-2)/2; i++) 
    { 
        // If left child is greater
        if (v[2*i + 1] > v[i]) 
                return false; 
  
        // If right child exists and is greater 
        if (2*i+2 < n && v[2*i+2] > v[i]) 
                return false; 
    } 
    return true; 
} 