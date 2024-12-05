#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <math.h>
#include <functional>

template <typename T>
class BinaryTree;

template <typename T>
class BinarySearchTree;

template <typename T>
class Node
{
	friend class BinaryTree<T>;
	friend class BinarySearchTree<T>;

private:
	T data;
	Node<T>* left;
	Node<T>* right;

public:
	Node(T data = T(), Node<T>* left = nullptr, Node<T>* right = nullptr)
		: data(data), left(left), right(right) {
	}
};

template <typename T>
class BinaryTree
{
protected:
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
		{
			std::cout << -1 << " ";
			return;
		}
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

	Node<T>* extendedPreOrderHelper(const T& stopFlag, const T& endFlag, bool& isEnd)
	{
		if (isEnd)
		{
			return nullptr;
		}
		T data;
		std::cin >> data;
		if (data == endFlag)
		{
			isEnd = true;
			return nullptr;
		}
		if (data == stopFlag)
		{
			return nullptr;
		}
		Node<T>* node = new Node<T>(data);
		node->left = extendedPreOrderHelper(stopFlag, endFlag, isEnd);
		node->right = extendedPreOrderHelper(stopFlag, endFlag, isEnd);
		return node;
	}

	Node<T>* pruneHelper(Node<T>* node, std::function<bool(const T&)> condition)
	{
		if (node == nullptr)
			return nullptr;

		node->left = pruneHelper(node->left, condition);
		node->right = pruneHelper(node->right, condition);

		if (node->left == nullptr && node->right == nullptr && condition(node->data)) {
			delete node;
			return nullptr;
		}

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

	void nodeCreate(int num, const T& stopFlag)
	{
		std::vector<Node<T>*> v(num);
		int n = 1;
		root = new Node<T>(n++);
		v[0] = root;
		for (int i = 0; i < num; i++)
		{
			int cA, cB;
			std::cin >> cA >> cB;
			if (cA == stopFlag)
			{
				v[i]->left = nullptr;
			}
			else
			{
				v[i]->left = new Node<T>(n++);
				v[cA - 1] = v[i]->left;
			}
			if (cB == stopFlag)
			{
				v[i]->right = nullptr;
			}
			else
			{
				v[i]->right = new Node<T>(n++);
				v[cB - 1] = v[i]->right;
			}
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

	void extendedPreOrderCreate(const T& stopFlag, const T& endFlag, bool& isEnd)
	{
		root = extendedPreOrderHelper(stopFlag, endFlag, isEnd);
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

	bool find(const T& data)
	{
		if (root == nullptr)
			return false;
		Node<T>* temp = root;
		std::stack<Node<T>*> s;
		while (temp != nullptr || !s.empty())
		{
			while (temp != nullptr)
			{
				if (temp->data == data)
					return true;
				s.push(temp);
				temp = temp->left;
			}
			temp = s.top();
			s.pop();
			temp = temp->right;
		}
		return false;
	}

	void prune(std::function<bool(const T&)> shouldPrune)
	{
		root = pruneHelper(root, shouldPrune);
	}

	void swapSubTrees(int k)
	{
		std::queue<Node<T>*> q;
		q.push(root);
		int level = 1;
		while (!q.empty())
		{
			int size = q.size();
			while (size--)
			{
				Node<T>* temp = q.front();
				q.pop();
				if (level % k == 0)
				{
					std::swap(temp->left, temp->right);
				}
				if (temp->left != nullptr)
					q.push(temp->left);
				if (temp->right != nullptr)
					q.push(temp->right);
			}
			level++;
		}
	}

	~BinaryTree()
	{
		Destroy(root);
	}
};



template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
private:
	bool findHelper(Node<T>* node, const T& data)
	{
		if (node == nullptr)
			return false;
		if (node->data == data)
			return true;
		if (data < node->data)
			return findHelper(node->left, data);
		return findHelper(node->right, data);
	}

	Node<T>* removeHelper(Node<T>* node, const T& data)
	{
		if (node == nullptr)
			return nullptr;

		if (data < node->data)
		{
			node->left = removeHelper(node->left, data);
		}
		else if (data > node->data)
		{
			node->right = removeHelper(node->right, data);
		}
		else
		{
			if (node->left == nullptr)
			{
				Node<T>* temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == nullptr)
			{
				Node<T>* temp = node->left;
				delete node;
				return temp;
			}

			Node<T>* temp = findMax(node->left);
			node->data = temp->data;
			node->left = removeHelper(node->left, temp->data);
		}
		return node;
	}

	Node<T>* findMax(Node<T>* node)
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node;
	}

	Node<T>* findMin(Node<T>* node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	void NthSmallestHelper(Node<T>* node, int& n, T& result)
	{
		if (node == nullptr || n <= 0)
		{
			return;
		}

		inOrder(node->left, n, result);

		if (--n == 0)
		{
			result = node->data;
			return;
		}

		inOrder(node->right, n, result);
	}

	void SmallestDiffHelper(Node<T>* node, T& prev, T& minDiff)
	{
		if (node == nullptr)
		{
			return;
		}
		SmallestDiffHelper(node->left, prev, minDiff);
		minDiff = std::min(minDiff, node->data - prev);
		prev = node->data;
		SmallestDiffHelper(node->right, prev, minDiff);
	}

public:
	BinarySearchTree() : BinaryTree<T>() {}

	void insert(const T& data)
	{
		Node<T>*& root = this->root;
		if (root == nullptr)
		{
			root = new Node<T>(data);
			return;
		}

		Node<T>* current = root;
		Node<T>* parent = nullptr;

		while (current != nullptr)
		{
			parent = current;

			if (data < current->data)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		if (data < parent->data)
		{
			parent->left = new Node<T>(data);
		}
		else
		{
			parent->right = new Node<T>(data);
		}
	}

	bool find(const T& data)
	{
		return findHelper(this->root, data);
	}

	void remove(const T& data)
	{
		Node<T>*& root = this->root;
		root = removeHelper(root, data);
	}

	T findNthSmallest(int n)
	{
		T result = T();
		NthSmallestHelperr(this->root, n, result);
		return result;
	}

	void findSmallestDiff(T& minDiff)
	{
		T prev = T();
		SmallestDiffHelper(this->root, prev, minDiff);
	}

	~BinarySearchTree() = default;
};

/*
tree.prune([](const int& data) {
		return data == 0;
		});
*/

int main()
{
	return 0;
}
