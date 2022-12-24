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

	// 현재 레드블랙트리의 조건을 만족하는 트리인지 반환한다.
	bool is_complete(tree_node root)
	{
		// root black check
		if (root._is_red)
			return false;

		// executive red node

		// red after black

		// all black depth same

	};



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

		// if double red....
		if (double_red())
		{
			// if uncle_node is red..
				// recoloring

			// if uncloe_node is black..
				// restructuring
		}
	};

	void recoloring(tree_node &n, tree_node &p, tree_node &g, tree_node &u)
	{
		p.is_red = true;
		u.is_red = true;
		g.is_red = false;

	};

	void restructuring(tree_node &n, tree_node &p, tree_node &g, tree_node &u)
	{
		// n p g를 오름차순으로 정렬한다.
		// p n g or p g n
		// low mid high로 명명한다.

		// mid를 부모노드로. low high를 왼쪽자식 오른쪽 자식으로 수정.

		// 색깔변경
	};

	void erase(tree_node a); // 레드블랙트리에 a노드를 제거한다.
	size_t bh(tree_node a); // a에서 nil까지의 높이를 구한다. 본인노드는 높이에서 제외.


	// STL
	template <class _NodePtr>
	unsigned
	__tree_sub_invariant(_NodePtr __x)
	{
		if (__x == nullptr)
			return 1;
		// parent consistency checked by caller
		// check __x->__left_ consistency
		if (__x->__left_ != nullptr && __x->__left_->__parent_ != __x)
			return 0;
		// check __x->__right_ consistency
		if (__x->__right_ != nullptr && __x->__right_->__parent_ != __x)
			return 0;
		// check __x->__left_ != __x->__right_ unless both are nullptr
		if (__x->__left_ == __x->__right_ && __x->__left_ != nullptr)
			return 0;
		// If this is red, neither child can be red
		if (!__x->__is_black_)
		{
			if (__x->__left_ && !__x->__left_->__is_black_)
				return 0;
			if (__x->__right_ && !__x->__right_->__is_black_)
				return 0;
		}
		unsigned __h = __tree_sub_invariant(__x->__left_);
		if (__h == 0)
			return 0;  // invalid left subtree
		if (__h != __tree_sub_invariant(__x->__right_))
			return 0;  // invalid or different height right subtree
		return __h + __x->__is_black_;  // return black height of this node
	}

	template <class _NodePtr>
	bool
	__tree_invariant(_NodePtr __root)
	{
		if (__root == nullptr)
			return true;
		// check __x->__parent_ consistency
		if (__root->__parent_ == nullptr)
			return false;
		if (!__tree_is_left_child(__root))
			return false;
		// root must be black
		if (!__root->__is_black_)
			return false;
		// do normal node checks
		return __tree_sub_invariant(__root) != 0;
	}

	// __x의 맨아래왼쪽노드를 반환
	template <class _NodePtr>
	_NodePtr
	__tree_min(_NodePtr __x)
	{
		while (__x->__left_ != nullptr)
			__x = __x->__left_;
		return __x;
	}

	template <class _NodePtr>
	_NodePtr
	__tree_max(_NodePtr __x)
	{
		while (__x->__right_ != nullptr)
			__x = __x->__right_;
		return __x;
	}

	// template <class _NodePtr>
	// _NodePtr
	// __tree_next(_NodePtr __x)
	// {
	// 	if (__x->__right_ != nullptr)
	// 		return __tree_min(__x->__right_);
	// 	while (!__tree_is_left_child(__x)) // ????????????
	// 		__x = __x->__parent_unsafe(); // 부모
	// 	return __x->__parent_unsafe();
	// }

	// template <class _EndNodePtr, class _NodePtr>
	// _EndNodePtr
	// __tree_next_iter(_NodePtr __x)
	// {
	// 	if (__x->__right_ != nullptr)
	// 		return static_cast<_EndNodePtr>(__tree_min(__x->__right_));
	// 	while (!__tree_is_left_child(__x))
	// 		__x = __x->__parent_unsafe();
	// 	return static_cast<_EndNodePtr>(__x->__parent_);
	// }

	// Returns:  pointer to a node which has no children
	// Precondition:  __x != nullptr.
	template <class _NodePtr>
	_NodePtr
	__tree_leaf(_NodePtr __x) _NOEXCEPT
	{
		while (true)
		{
			if (__x->__left_ != nullptr)
			{
				__x = __x->__left_;
				continue;
			}
			if (__x->__right_ != nullptr)
			{
				__x = __x->__right_;
				continue;
			}
			break;
		}
		return __x;
	}

	// Effects:  Makes __x->__right_ the subtree root with __x as its left child
	//           while preserving in-order order.
	// Precondition:  __x->__right_ != nullptr
	template <class _NodePtr>
	void
	__tree_left_rotate(_NodePtr __x)
	{
		_NodePtr __y = __x->__right_;
		__x->__right_ = __y->__left_;
		if (__x->__right_ != nullptr)
			__x->__right_->__set_parent(__x);
		__y->__parent_ = __x->__parent_;
		if (__tree_is_left_child(__x)) 				// __tree_is_left_child는 노드가 부모의 왼쪽자식인지 여부를 반환한다.
			__x->__parent_->__left_ = __y;
		else
			__x->__parent_unsafe()->__right_ = __y; // 왜 __x->__parent_->__right_ = __y가 아닐까?
		__y->__left_ = __x;
		__x->__set_parent(__y);
	}

	// Effects:  Makes __x->__left_ the subtree root with __x as its right child
	//           while preserving in-order order.
	// Precondition:  __x->__left_ != nullptr
	template <class _NodePtr>
	void
	__tree_right_rotate(_NodePtr __x) _NOEXCEPT
	{
		_NodePtr __y = __x->__left_;
		__x->__left_ = __y->__right_;
		if (__x->__left_ != nullptr)
			__x->__left_->__set_parent(__x);
		__y->__parent_ = __x->__parent_;
		if (__tree_is_left_child(__x))
			__x->__parent_->__left_ = __y;
		else
			__x->__parent_unsafe()->__right_ = __y;
		__y->__right_ = __x;
		__x->__set_parent(__y);
	}
};

}

#endif