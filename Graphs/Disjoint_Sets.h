class Disjoint_Sets
{    
public:
    Disjoint_Sets();
    Disjoint_Sets(int size);
	// if you dynamically allocate any memory remove the "= default"
	// and implement a destructor in Disjoint_Sets.cpp
    ~Disjoint_Sets() = default;
   
    void union_set(int x, int y);
    int find(int x) const;
    const static int MAXNUMVERTICES = 100;
    //if id[10] = 20 then vertex 10 is in the same set as 20
    //but 20 is not necessarily the root
	int id[MAXNUMVERTICES];
	int sizes[MAXNUMVERTICES];
};

/* Preconditions: size is the number of sets to initialize for the class instance
   Postconditions: creates a new disjoint sets object that can handle size elements
   (with indicies 0 - size-1)
*/
Disjoint_Sets::Disjoint_Sets(int size)
{
	for(int i = 0; i < MAXNUMVERTICES; i++)
	{
		id[i] = i;
		sizes[i] = 1;
	}
}

Disjoint_Sets::Disjoint_Sets()
{
	for(int i = 0; i < MAXNUMVERTICES; i++)
	{
		id[i] = i;
		sizes[i] = 1;
	}
}

/* Union by size
   Preconditions: x and y are integer values between [0, size-1]
   Postconditions: attaches the root of one tree to the root of the other tree
*/
//I borrowed this code from the UF Programming Team powerpoint slides that Joe made
void Disjoint_Sets::union_set(int x, int y)
{
    //i and j are the sets that x and y are in
    int i = find(x);
    int j = find(y);
    if(i == j)
        return;
    //set the lower vertex to be in the set of the higher vertex
    if(sizes[i] < sizes[j])
	{
        id[i] = j;
        sizes[j] += sizes[i];
    }
	else
	{
        id[j] = i;
        sizes[i] += sizes[j];
    }
}

/* Preconditions: x is an integer values between [0, size-1]
   Postconditions: returns the root of the tree to which x belongs
*/
//I borrowed this code from the UF Programming Team powerpoint slides that Joe made
int Disjoint_Sets::find(int x) const
{
    while(x != id[x])
        x = id[x];
    return x;
}