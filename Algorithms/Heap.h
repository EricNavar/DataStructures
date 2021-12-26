void deleteRoot(int arr[], int& n) 
{ 
    // Replace root with first element 
    arr[0] = arr[n - 1];
  
    // heapify the root node 
    heapify(arr, --n, 0); 
}

void insertNode(int arr[], int& n, int Key) 
{ 
    // Insert the element at end of Heap 
    arr[n++] = Key;
  
    // Heapify the new node following a bottom-up approach 
    heapify(arr, n, n - 1);
}

// For Max-Heap 
void heapify(int arr[], int n, int i) 
{ 
    // Find parent
    int parent = (i-1)/2;
  
    if (arr[parent] > 0)
    {
        // If current node is greater than its parent
        // Swap them and call heapify on the parent
        if (arr[i] > arr[parent])
        {
            swap(arr[i], arr[parent]);
            // Recursively heapify the parent node
            heapify(arr, n, parent);
        }
    }
}

void insert( const Comparable & x )
{
     if( currentSize == array.size()-1)
                  array.resize( array.size( ) * 2 );
      // Percolate up
      int hole = ++currentSize;
     Comparable copy = x;
      array[0 ] = std::move( copy );
      for(; (x < array[ hole / 2 ] && hole>1) ; hole /= 2 )
              array[ hole ] = std::move( array[ hole/2]);
      array[ hole ] = std::move( array[ 0 ] );
}
