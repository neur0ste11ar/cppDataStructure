#include <iostream>
#include <queue>

template <typename T>
class BST;

template <typename T>
class Node
{
	friend class BST<T>;
private:
	T data;
	Node<T>* left;
	Node<T>* right;
	int factor;
public:
	Node(T data) : data(data), left(nullptr), right(nullptr), factor(0) {}
};

template <typename T>
class BST
{
private:
	Node<T>* root;


public:
	BST() : root(nullptr) {}

	void insert(T data)
	{
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

	bool find(T data)
	{
		Node<T>* current = root;

		while (current != nullptr)
		{
			if (data == current->data)
			{
				return true;
			}

			if (data < current->data)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		return false;
	}

	void remove(T data)
	{
		Node<T>* current = root;
		Node<T>* parent = nullptr;

		while (current != nullptr && current->data != data)
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

		if (current == nullptr)
		{
			return;
		}

		if (current->left == nullptr || current->right == nullptr)
		{
			Node<T>* child = current->left;

			if (child == nullptr)
			{
				child = current->right;
			}

			if (parent == nullptr)
			{
				root = child;
			}
			else if (parent->left == current)
			{
				parent->left = child;
			}
			else
			{
				parent->right = child;
			}

			delete current;
		}
		else
		{
			Node<T>* mostRight = current->left;
			Node<T>* mostRightParent = current;

			while (mostRight->right != nullptr)
			{
				mostRightParent = mostRight;
				mostRight = mostRight->right;
			}

			current->data = mostRight->data;

			if (mostRightParent->left == mostRight)
			{
				mostRightParent->left = mostRight->left;
			}
			else
			{
				mostRightParent->right = mostRight->left;
			}

			delete mostRight;
		}
	}

	void levelOrder()
	{
		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty())
		{
			Node<T>* current = q.front();
			q.pop();

			if (current == nullptr)
			{
				continue;
			}

			std::cout << current->data << " ";

			q.push(current->left);
			q.push(current->right);
		}
	}

	~BST()
	{
		std::queue<Node<T>*> q;
		q.push(root);

		while (!q.empty())
		{
			Node<T>* current = q.front();
			q.pop();

			if (current == nullptr)
			{
				continue;
			}

			q.push(current->left);
			q.push(current->right);

			delete current;
		}
	}
};


int main()
{
	return 0;
}

