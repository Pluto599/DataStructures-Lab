#include<iostream>
using namespace std;
#include<cassert>
#include<queue>

//��������ڵ�
template <class T>
struct BinTreeNode {	                        //����������ඨ��
	T data;	 		                            //������
	BinTreeNode<T>* leftChild, * rightChild;	//����Ů������Ů����

	BinTreeNode()                               //���캯��
	{
		leftChild = nullptr;  rightChild = nullptr;
	}
	BinTreeNode(T x, BinTreeNode<T>* l = nullptr, BinTreeNode<T>* r = nullptr)
	{
		data = x;  leftChild = l;  rightChild = r;
	}
};

template <class T>
class BinaryTree
{
public:
	BinaryTree() :root(nullptr) {}	//���캯��
	BinaryTree(T value) :RefValue(value), root(nullptr) {}
	~BinaryTree() { Destroy(root); }//��������

	void CreateBinTree(int len) { CreateBinTree(len, root); }	//����ǰ���������Ϊ len ����

	int* levelNum;
	void setLevelNum(BinTreeNode<T>* subTree, int i)
	{	
		if (subTree != nullptr)
		{
			levelNum[i]++;
			i++;
			setLevelNum(subTree->leftChild, i);
			setLevelNum(subTree->rightChild, i);
		}
	}
	void Solution(int n)
	{
		levelNum = new int[n];
		int* levelStart = new int[n];
		for (int i = 0; i < n; i++)
		{
			levelNum[i] = 0;
			levelStart[i] = 0;
		}
		setLevelNum(root, 0);
		levelStart[0] = 0;
		for (int i = 1; levelNum[i] != 0; i++)
			levelStart[i] = levelStart[i - 1] + levelNum[i - 1];

		int index = 0, level = 1;
		int pre = 0, cur;
		queue<BinTreeNode<T>*> q;
		BinTreeNode<T>* p = root;
		if (p->leftChild != nullptr)
			q.push(p->leftChild);
		if (p->rightChild != nullptr)
			q.push(p->rightChild);
		if (p->data % 2 == 0)
		{
			cout << "false";
			return;
		}
		p = q.front();

		while (!q.empty())
		{
			index++;
			if (index == levelStart[level + 1])
				level++;
			p = q.front();
			cur = p->data;
			q.pop();
			
			if (cur % 2 == level % 2)
			{
				cout << "false";
				return;
			}
			if (index != levelStart[level])
			{
				if (level % 2 == 1)
				{
					if (cur >= pre)
					{
						cout << "false";
						return;
					}
				}
				else
				{
					if (cur <= pre)
					{
						cout << "false";
						return;
					}
				}
			}
			pre = cur;

			if (p->leftChild != nullptr)
				q.push(p->leftChild);
			if (p->rightChild != nullptr)
				q.push(p->rightChild);
		}

		cout << "true";
		return;
	}

protected:
	BinTreeNode<T>* root; 	//�������ĸ�ָ��
	T RefValue;	 			//��������ֹͣ��־

	void CreateBinTree(int len, BinTreeNode<T>*& subTree);		//����ǰ���������Ϊ len ����
	
	void Destroy(BinTreeNode<T>*& subTree);						//ɾ��
};

template<class T>
void BinaryTree<T>::CreateBinTree(int len, BinTreeNode<T>*& subTree)
{
	if (len <= 0)
		return;

	T item;
	cin >> item;
	if (item != RefValue)
	{
		subTree = new BinTreeNode<T>(item);
		if (subTree == nullptr)
		{
			cerr << "�洢�����!" << endl;
			exit(1);
		}
		CreateBinTree(len - 1, subTree->leftChild);
		CreateBinTree(len - 1, subTree->rightChild);
	}
	else
		subTree = nullptr;

}

template<class T>
void BinaryTree<T>::Destroy(BinTreeNode<T>*& subTree)
{
	if (subTree != nullptr)
	{
		Destroy(subTree->leftChild);
		Destroy(subTree->rightChild);
		delete subTree;
		subTree = nullptr;
	}
}