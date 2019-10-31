class VertexListNode
{
	bool headNode;   
public:
	VertexListNode *next;
	int name;
	int weight;
	VertexListNode(int name, bool isHead, int weight, VertexListNode * next)
	{
		this->name = name;
		headNode = isHead;
		this->weight = weight;
		this->next = next;
	}
};