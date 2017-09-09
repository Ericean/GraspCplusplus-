#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int key;
	Node*left, *right;
	Node(int k): key(k), left(nullptr), right(nullptr) {}
	bool isLeaf() const {return (left == nullptr && right == nullptr);}
	bool hasLeft() const {return left != nullptr;}
	bool hasRight() const {return right != nullptr;}
};

class bst {
public:
	bst();
	~bst();
	void  insert(int key);
	Node* search(int key);
	void traverse();
private:
	void _insert(int key, Node* n);
	Node* _search(int key, Node* n);
	void inorder_traverse(Node* n);
	void preorder_traverse(Node* n);
	void postorder_traverse(Node* n);
	void _destory(Node* n);
	Node* _root;
};

bst::bst() {_root = nullptr;}

void bst::insert(int key) {
	if (_root == nullptr)_root = new Node(key);
	else _insert(key, _root);
}

Node* bst::search(int key) {
	if (_root == nullptr) return nullptr;
	else return _search(key, _root);
}
void bst::traverse()
{
	if (_root == nullptr) return;
	inorder_traverse(_root);
	preorder_traverse(_root);
	postorder_traverse(_root);
}

bst::~bst() {_destory(_root);}

void bst::_insert(int key, Node* n)
{
	if (key < n->key)
	{
		if (n->hasLeft()) {
			_insert(key, n->left);
		} else {
			n->left = new Node(key);
		}
	} else if (key > n->key)
	{
		if (n->hasRight()) {
			_insert(key, n->right);
		} else {
			n->right = new Node(key);
		}
	} else
		n->key = key;
}


Node* bst::_search(int key, Node* n)
{
	if (key == n->key) return n;
	else if (key > n->key ) {
		if (n->hasRight()) return _search(key, n->right);
		else return nullptr;
	}
	else {
		if (n->hasLeft()) return _search(key, n->left);
		else return nullptr;
	}
}

void bst::_destory(Node* n)
{
	if (n != nullptr)
	{
		_destory(n->left);
		_destory(n->right);
		cout << n->key << endl;
		delete n;
	}
}




void bst::inorder_traverse(Node* _root)
{
	vector<Node*> v;
	Node *tmp = _root;
	while (tmp != nullptr)
	{
		v.push_back(tmp);
		tmp = tmp->left;
	}
	while (!v.empty()) {
		Node* n = v.back();
		cout << "inorder visiting " << n-> key << "\n";
		v.pop_back();

		tmp = n-> right;
		while (tmp != nullptr)
		{
			v.push_back(tmp);
			tmp = tmp->left;
		}
	}

}


void bst::preorder_traverse(Node* _root)
{
	vector<Node*> v;
	v.push_back(_root);
	while (!v.empty()) {
		Node* n = v.back();
		cout << "preorder visiting " << n-> key << "\n";
		v.pop_back();
		if (n->hasRight())
			v.push_back(n->right);
		if (n->hasLeft())
			v.push_back(n->left);
	}
}

void bst::postorder_traverse(Node* _root)
{
	vector<Node*> vv;
	Node* tmp = _root;
	do {
		while (tmp != nullptr)
		{
			if (tmp->hasRight())
				vv.push_back(tmp->right);
			vv.push_back(tmp);
			tmp = tmp->left;
		}

		Node* item = vv.back();
		vv.pop_back();
		
		if (item->right == vv.back())
		{
			vv.pop_back();
			vv.push_back(item);
			tmp = item->right;
		}else{
			cout << "postorder visiting " << item-> key << "\n";
			tmp = nullptr;
		}

	} while (!vv.empty());
	/**
	vector<Node*> v1;
	vector<Node*> v2;
	v1.push_back(_root);
	while (!v1.empty()) {
		Node* n = v1.back();
		v1.pop_back();
		v2.push_back(n);
		if(n->hasLeft())
			v1.push_back(n->left);
		if(n->hasRight())
			v1.push_back(n->right);
	}
	while(!v2.empty()){
		Node* n = v2.back();
		cout << "postorder visiting " << n-> key << "\n";
		v2.pop_back();
	}**/
}



int main()
{
	bst tree;
	tree.insert(4);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	cout << "--------------\n";
	Node* n = tree.search(4);
	cout << n->key << endl;
	cout << "--------------\n";
	tree.traverse();
}
