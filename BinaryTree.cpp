#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <math.h>

template <typename T>
class BinaryTree;

template <typename T>
class Node
{
	friend class BinaryTree<T>;

private:
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* next;
	int leftFlag;
	int rightFlag;

public:
	Node(T data = 0, Node<T>* left = nullptr, Node<T>* right = nullptr, Node<T>* next = nullptr, int leftFlag = 0, int rightFlag = 0)
		: data(data), left(left), right(right), next(next), leftFlag(leftFlag), rightFlag(rightFlag) {}
	void setNext(Node<T>* next)
	{
		this->next = next;
	}
};

template <typename T>
class BinaryTree
{
private:
	Node<T>* root;

	int Size(Node<T>* node)
	{
		if (node == nullptr)
			return 0;
		return 1 + Size(node->left) + Size(node->right);
	}

	int Height(Node<T>* node)
	{
		if (node == nullptr)
			return 0;
		return 1 + std::max(Height(node->left), Height(node->right));
	}

	void PreOrder(Node<T>* node)
	{
		if (node == nullptr)
			return;
		std::cout << node->data << " ";
		PreOrder(node->left);
		PreOrder(node->right);
	}

	void InOrder(Node<T>* node)
	{
		if (node == nullptr)
			return;
		InOrder(node->left);
		std::cout << node->data << " ";
		InOrder(node->right);
	}

	void PostOrder(Node<T>* node)
	{
		if (node == nullptr)
			return;
		PostOrder(node->left);
		PostOrder(node->right);
		std::cout << node->data << " ";
	}

	void LevelOrder(Node<T>* node)
	{
		if (node == nullptr)
			return;
		std::queue<Node<T>*> q;
		q.push(node);
		while (!q.empty())
		{
			Node<T>* temp = q.front();
			q.pop();
			std::cout << temp->data << " ";
			if (temp->left != nullptr)
				q.push(temp->left);
			if (temp->right != nullptr)
				q.push(temp->right);
		}
	}

	Node<T>* PreInOrderHelper(T pre[], T in[], int pl, int pr, int il, int ir)
	{
		if (pl > pr || il > ir)
			return nullptr;
		Node<T>* node = new Node<T>(pre[pl]);
		int i = il;
		while (in[i] != pre[pl])
			i++;
		/* num = i - il */
		node->left = PreInOrderHelper(pre, in, pl + 1, pl + i - il, il, i - 1);
		node->right = PreInOrderHelper(pre, in, pl + i - il + 1, pr, i + 1, ir);
		return node;
	}

	Node<T>* PostInOrderHelper(T post[], T in[], int pl, int pr, int il, int ir)
	{
		if (pl > pr || il > ir)
			return nullptr;
		Node<T>* node = new Node<T>(post[pr]);
		int i = il;
		while (in[i] != post[pr])
			i++;
		node->left = PostInOrderHelper(post, in, pl, pl + i - il - 1, il, i - 1);
		node->right = PostInOrderHelper(post, in, pl + i - il, pr - 1, i + 1, ir);
		return node;
	}

	void Destroy(Node<T>* node)
	{
		if (node == nullptr)
			return;
		Destroy(node->left);
		Destroy(node->right);
		delete node;
	}

public:
	BinaryTree(Node<T>* root = nullptr) : root(root) {}

	void levelOrderCreate(const T& stopFlag)
	{
		std::queue<Node<T>*> q;
		T data;
		std::cin >> data;
		root = new Node<T>(data);
		q.push(root);
		while (!q.empty())
		{
			Node<T>* temp = q.front();
			q.pop();
			std::cin >> data;
			if (data != stopFlag)
			{
				temp->left = new Node<T>(data);
				q.push(temp->left);
			}
			std::cin >> data;
			if (data != stopFlag)
			{
				temp->right = new Node<T>(data);
				q.push(temp->right);
			}
		}
	}

	void createFullTree(int height)
	{
		if (height < 1)
			return;
		T data;
		std::cin >> data;
		root = new Node<T>(data);
		std::queue<Node<T>*> q;
		q.push(root);
		for (int i = 0; i < pow(2, height - 1) - 1; i++)
		{
			Node<T>* temp = q.front();
			q.pop();
			std::cin >> data;
			temp->left = new Node<T>(data);
			q.push(temp->left);
			std::cin >> data;
			temp->right = new Node<T>(data);
			q.push(temp->right);
		}
	}

	void preInOrderCreate(T pre[], T in[], int pl, int pr, int il, int ir)
	{
		root = PreInOrderHelper(pre, in, pl, pr, il, ir);
	}

	void postInOrderCreate(T post[], T in[], int pl, int pr, int il, int ir)
	{
		root = PostInOrderHelper(post, in, pl, pr, il, ir);
	}

	bool isEmpty()
	{
		return root == nullptr;
	}

	int size()
	{
		return Size(root);
	}

	int height()
	{
		return Height(root);
	}

	void preOrder()
	{
		PreOrder(root);
		std::cout << std::endl;
	}

	void inOrder()
	{
		InOrder(root);
		std::cout << std::endl;
	}

	void postOrder()
	{
		PostOrder(root);
		std::cout << std::endl;
	}

	void levelOrder()
	{
		LevelOrder(root);
		std::cout << std::endl;
	}

	Node<T>* getRoot()
	{
		return root;
	}

	Node<T>* find(const T& data, Node<T>* node)
	{
		if (node == nullptr)
			return nullptr;
		Node<T>* temp = node;
		std::stack<Node<T>*> s;
		while (temp != nullptr || !s.empty())
		{
			while (temp != nullptr)
			{
				if (temp->data == data)
					return temp;
				s.push(temp);
				temp = temp->left;
			}
			temp = s.top();
			s.pop();
			temp = temp->right;
		}
		return nullptr;
	}

	Node<T>* findInForest(const T& data, Node<T>* node, std::vector<Node<T>*>& v)
	{
		if (node == nullptr)
			return nullptr;
		Node<T>* temp = node;
		std::stack<Node<T>*> s;
		while (temp != nullptr || !s.empty())
		{
			while (temp != nullptr)
			{
				bool flag = true;
				for (int i = 0; i < v.size(); i++)
				{
					if (v[i] == temp)
					{
						flag = false;
						break;
					}
				}
				if (flag)
				{
					v.push_back(temp);
					Node<T>* tempNext = findInForest(data, temp->next, v);
					if (tempNext != nullptr)
						return tempNext;
				}
				if (temp->data == data)
					return temp;
				s.push(temp);
				temp = temp->left;
			}
			temp = s.top();
			s.pop();
			temp = temp->right;
		}
		return nullptr;
	}

	~BinaryTree()
	{
		Destroy(root);
	}
};

int main()
{
	return 0;
}
