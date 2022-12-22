#ifndef RBTREE
#define RBTREE

#include <memory>

namespace ft
{

template<class T, class Alloc = std::allocator<T> >
class rbtree
{
private:

	/* data */
public:
	typedef Alloc										allocator_type;
	typedef T											value_type;
	typedef typename allocator_type::pointer			pointer;

protected:
//==============================================================================
	template<class T, class Alloc = std::allocator<T> >
	struct tree_node
	{
		typedef Alloc										allocator_type;
		typedef T											value_type;
		typedef typename allocator_type::pointer			pointer;

		pointer				_left;
		pointer				_right;
		pointer				_parent;
		bool				_is_red;		// true red, false black
		value_type			data;
	}
	// construct
	tree_node() : _left(0), _right(0), _parent(0), _is_red(0), data(0), _alloc(allocator_type()){};
	tree_node(const tree_node& a)
		: _left(a._left), _right(a._right),_parent(a._parent), _is_red(0)
			, data(a.data), _alloc(a._alloc){};
	tree_node(value_type a) : _left(0), _right(0), _parent(0), _is_red(0), data(a), _alloc(allocator_type()){};
//==============================================================================
	// member variable : 자기자신과 왼쪽자식, 오른쪽자식을 멤버로 가진다.
	allocator_type		_alloc;
	tree_node			_root;

public:
	rbtree()
		: _root(0), _left(0), _right(0), _parent(0), _alloc(allocator_type()){};
	~rbtree(){};

	bool is_complete(); // 현재 레드블랙트리의 조건을 만족하는 트리인지 반환한다.

	void insert(tree_node a)  // 레드블랙트리에 a노드를 추가한다.
	{
		tree_node current = _root;

		a._is_red = true;	// new node is always red.

		// insert node in right place
		while(1)
		{
			if (current < a)
			{
				if (current._left == 0)
				{
					current._left = a;
					return ;
				}
				current = current._left;
			}
			else
			{
				if (current._right == 0)
				{
					current._right = a;
					return ;
				}
			}
		}

		// make this red-black tree perfect
		// ???
	};

	void erase(tree_node a); // 레드블랙트리에 a노드를 제거한다.
	size_t bh(tree_node a); // a에서 nil까지의 높이를 구한다. 본인노드는 높이에서 제외.
};

}

#endif