#pragma once
#include <iostream>


template<class K, class V>
struct BSTNode
{
	BSTNode(const K &key, const V &value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
	K _key;
	V _value;
	BSTNode<K, V> *_left;
	BSTNode<K, V> *_right;
};

template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	~BSTree()
	{
		_Destory(_root);
	}
	BSTree(const BSTree<K, V> &tree)
	{
		_root = _CreatHSTree(_root, tree._root);
	}
	BSTree operator=(const BSTree<K, V> &tree)
	{
		_Destory(_root);
		_root = _CreatHSTree(_root, tree._root);
		return *this;
	}
public:
	bool Insert(const K&key, const V&value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node *parent = NULL;
		Node *cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		if (key > parent->_key)
		{
			parent->_right = new Node(key, value);
		}
		else
		{
			parent->_left = new Node(key, value);
		}
		return true;
	}
	bool Insert_R(const K &key, const V &value)
	{
		return _Insert_R(_root, key, value);
	}
	Node *Find_R(const K &key)
	{
		return _Find_R(_root, key);
	}
	Node *Find(const K &key)
	{
		Node *cur = _root;
		while (cur != NULL)
		{
			if (key == cur->_key)
			{
				return cur;
			}
			else if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
		}
		return NULL;
	}

	/*
	删除要考虑两种情况：
		1、叶子结点（left 和 right 均为 NULL）
		2、非叶子结点(left 和 right 有一个不是 NULL)
		3、非叶子结点(left 和 right均不是 NULL)
	*/
	bool Remove(const K &key)
	{
		Node *prev = NULL;
		Node *cur = _root;
		//找到当前结点和它的父节点
		while (cur)
		{
			if (key == cur->_key)
			{
				break;
			}
			else if (key < cur->_key)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				prev = cur;
				cur = cur->_right;
			}
		}

		//情况1(叶子结点)
		if (cur->_left == NULL && cur->_right == NULL)
		{
			if (prev != NULL)  //不是只剩一个结点的时候：
			{
				if (prev->_left == cur)
				{
					prev->_left = NULL;
				}
				else
				{
					prev->_right = NULL;
				}
			}
			delete cur;
		}
		//情况2(left 或 right 一个不是 NULL)
		else if (cur->_right == NULL)
		{
			if (prev == NULL)	//处理根节点的情况
			{
				_root = cur->_left;
			}
			else
			{
				if (prev->_left == cur)
				{
					prev->_left = cur->_left;
				}
				else
				{
					prev->_right = cur->_left;
				}
				delete cur;
			}
		}
		else if (cur->_left == NULL)
		{
			if (prev == NULL) //处理根节点的情况
			{
				_root = cur->_right;
			}
			else
			{
				if (prev->_left == cur)
				{
					prev->_left = cur->_right;
				}
				else
				{
					prev->_right = cur->_right;
				}
			}
			delete cur;
		}
		//情况3(left 或 riht 都不是 NULL)
		else
		{
			Node *prev = cur;
			Node *FirstLeft = cur->_right;
			while (FirstLeft->_left)
			{
				prev = FirstLeft;
				FirstLeft = FirstLeft->_left;
			}
			Node *del = FirstLeft;

			cur->_key = del->_key;
			cur->_value = del->_value;

			if (prev->_left == FirstLeft)
			{
				prev->_left = FirstLeft->_right;
			}
			else
			{
				prev->_right = FirstLeft->_right;
			}
			delete del;
		}
		return true;
	}
	bool Remove_R(const K &key)
	{
		return _Remove_R(_root, key);
	}
	void InOrder()
	{
		InOrder_R(_root);
	}

protected:
	Node* _CreatHSTree(Node *cur, Node *_cur)
	{
		if (_cur == NULL)
		{
			return NULL;
		}
		else
		{
			cur = new Node(_cur->_key, _cur->_value);
		}

		cur->_left = _CreatHSTree(cur->_left, _cur->_left);
		cur->_right = _CreatHSTree(cur->_right, _cur->_right);
		return cur;
	}
	void _Destory(Node *root)
	{
		if (root == NULL)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;

	}

	bool _Remove_R(Node *&root, const K &key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key > key)
		{
			return _Remove_R(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Remove_R(root->_right, key);
		}
		else  // 相等
		{
			Node *del = root;
			if (root->_left == NULL)
			{
				root = root->_right;			//这里的root是引用，
														   //可能是上一层root->_left 或 root->_right
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node *FirstLeft = root->_right;
				while (FirstLeft->_left)
				{
					FirstLeft = FirstLeft->_left;
				}
				std::swap(root->_key, FirstLeft->_key);
				std::swap(root->_value, FirstLeft->_value);
				return _Remove_R(root->_right, key);
			}
			delete del;
		}
	}

	bool _Insert_R(Node *&root, const K &key, const V &value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		else if (key < root->_key)
		{
			_Insert_R(root->_left, key, value);
		}
		else if (key > root->_key)
		{
			_Insert_R(root->_right, key, value);
		}
		return false;
	}


	Node * _Find_R(Node *root, const K &key)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (key == root->_key)
		{
			return root;
		}
		if (key < root->_key)
		{
			return _Find_R(root->_left, key);
		}
		else if (key > root->_key)
		{
			return _Find_R(root->_right, key);
		}
	}

	void InOrder_R(Node *root)
	{
		if (root == NULL)
		{
			return;
		}
		InOrder_R(root->_left);
		cout << "key: " << root->_key << ", value: " << root->_value << endl;
		InOrder_R(root->_right);
	}
protected:
	Node *_root;
};

void TestInsert()
{
	BSTree<int, int> bsti;
	bsti.Insert(3, 30);
	bsti.Insert(1, 10);
	bsti.Insert(2, 20);
	bsti.Insert(4, 40);
	bsti.Insert(5, 50);
}

void TestInsert_R()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(4, 40);
	bsti.Insert_R(5, 50);
}

void TestFind()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(4, 40);
	bsti.Insert_R(5, 50);

	BSTNode<int, int> *RetNode = bsti.Find(3);
	RetNode = bsti.Find(1);
	RetNode = bsti.Find(2);
	RetNode = bsti.Find(4);
	RetNode = bsti.Find(5);
	RetNode = bsti.Find(6);
}

void TestFind_R()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(4, 40);
	bsti.Insert_R(5, 50);

	BSTNode<int, int> *RetNode = bsti.Find(3);
	RetNode = bsti.Find_R(1);
	RetNode = bsti.Find_R(2);
	RetNode = bsti.Find_R(4);
	RetNode = bsti.Find_R(5);
	RetNode = bsti.Find_R(6);
}


void TestInOrder()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(4, 40);
	bsti.Insert_R(5, 50);

	bsti.InOrder();
}

void TestRemove()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(5, 40);
	bsti.Insert_R(6, 50);
	bsti.Insert_R(7, 50);


	bsti.Remove(3);
	bsti.Remove(1);
	bsti.Remove(2);
	bsti.Remove(5);
	bsti.Remove(7);
	bsti.Remove(6);
}

void TestRemove_R()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(5, 40);
	bsti.Insert_R(6, 50);
	bsti.Insert_R(7, 50);

	bsti.Remove_R(3);
	bsti.Remove_R(1);
	bsti.Remove_R(2);
	bsti.Remove_R(5);
	bsti.Remove_R(7);
	bsti.Remove_R(6);
}

void TestCopyCreat()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(5, 40);
	bsti.Insert_R(6, 50);
	bsti.Insert_R(7, 50);

	BSTree<int, int> bsti1(bsti);
}

void TestOperatorEqual()
{
	BSTree<int, int> bsti;
	bsti.Insert_R(3, 30);
	bsti.Insert_R(1, 10);
	bsti.Insert_R(2, 20);
	bsti.Insert_R(5, 40);
	bsti.Insert_R(6, 50);
	bsti.Insert_R(7, 50);

	BSTree<int, int> bsti2;
	bsti2 = bsti;
}
