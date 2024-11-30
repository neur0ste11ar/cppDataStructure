#include <iostream>
#include <queue>
#include <vector>

struct Node
{
	char data;
	int weight;
	Node* left;
	Node* right;
	Node(char data, int weight) : data(data), weight(weight), left(nullptr), right(nullptr) {}
};

struct Compare
{
	bool operator()(Node* l, Node* r)
	{
		return l->weight > r->weight;
	}
};

Node* buildHuffmanTree(const std::vector<char>& data, const std::vector<int>& weight)
{
	std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
	for (int i = 0; i < data.size(); i++)
	{
		pq.push(new Node(data[i], weight[i]));
	}
	while (pq.size() != 1)
	{
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();
		Node* top = new Node('\0', left->weight + right->weight);
		top->left = left;
		top->right = right;
		pq.push(top);
	}
	return pq.top();
}

void printHuffmanCodes(Node* root, std::string str)
{
	if (!root)
	{
		return;
	}
	if (root->data != '\0')
	{
		std::cout << root->data << ": " << str << std::endl;
	}
	printHuffmanCodes(root->left, str + "0");
	printHuffmanCodes(root->right, str + "1");
}

int main()
{
	return 0;
}