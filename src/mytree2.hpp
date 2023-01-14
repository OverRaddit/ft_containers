/*

Red-black tree class, designed for use in implementing STL
associative containers (set, multiset, map, and multimap). The
insertion and deletion algorithms are based on those in Cormen,
Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990),
except that

(1) the header cell is maintained with links not only to the root
but also to the leftmost node of the tree, to enable constant time
begin(), and to the rightmost node of the tree, to enable linear time
performance when used with the generic set algorithms (set_union,
etc.);

// 헤더셀은 루트뿐만아니라 최솟값 최댓값또한 링크로 유지한다
// begin end를 constant time에 동작시키기 위해서이다.
// set 알고리즘과 함께 사용될 때 선형 시간성능을 가능하게 한다. -> 왜>??????

(2) when a node being deleted has two children its successor node is
relinked into its place, rather than copied, so that the only
iterators invalidated are those referring to the deleted node.

삭제되는 노드가 2명의 자식을 가질때, 해당 노드의 자리를 대체하는 노드(successor node)는 복사되지 않고
올바른 위치에 다시 연결되게 된다.
무효화된 반복자는 삭제된 노드를 참조한 반복자 뿐이다.


*/

#ifndef __TREE
#define __TREE

# include "utility.hpp"

namespace ft
{


// algorithm

template <class _NodePtr>
inline bool __tree_is_left_child(_NodePtr __x) throw()
{
	return __x == __x->_parent->_left;
}

template <class _NodePtr>
inline _NodePtr __tree_min(_NodePtr __x) throw()
{
	while (__x->_left != nullptr)
		__x = __x->_left;
	return __x;
}

template <class _NodePtr>
inline _NodePtr __tree_max(_NodePtr __x) throw()
{
	while (__x->_right != nullptr)
		__x = __x->_right;
	return __x;
}

template <class _NodePtr>
inline _NodePtr __tree_next_iter(_NodePtr __x) throw()
{
	if (__x->_right != nullptr)
		return __tree_min(__x->_right);
	while (!__tree_is_left_child(__x))
		__x = __x->_parent;
	return __x->_parent;
}

template <class _NodePtr>
inline _NodePtr __tree_prev_iter(_NodePtr __x) throw()
{
	if (__x->_left != nullptr)
		return __tree_max(__x->_left);
	_NodePtr __xx = __x;
	while (__tree_is_left_child(__xx))
		__xx = __xx->_parent;
	return __xx->_parent;
}

template <class _NodePtr>
_NodePtr __tree_next(_NodePtr __x) throw()
{
	if (__x->__right_ != nullptr)
		return __tree_min(__x->__right_);
	while (!__tree_is_left_child(__x))
		__x = __x->_parent;
	return __x->_parent;
}

template <class _NodePtr>
void __tree_left_rotate(_NodePtr __x) throw()
{
	_NodePtr __y = __x->_right;
	__x->_right = __y->_left;
	if (__x->_right != nullptr)
		__x->_right->_parent = __x;
	__y->_parent = __x->_parent;
	if (__tree_is_left_child(__x))
		__x->_parent->_left = __y;
	else
		__x->_parent->_right = __y;
	__y->_left = __x;
	__x->_parent = __y;
}

template <class _NodePtr>
void __tree_right_rotate(_NodePtr __x) throw()
{
	_NodePtr __y = __x->_left;
	__x->_left = __y->_right;
	if (__x->_left != nullptr)
		__x->_left->_parent = __x;
	__y->_parent = __x->_parent;
	if (__tree_is_left_child(__x))
		__x->_parent->_left = __y;
	else
		__x->_parent->_right = __y;
	__y->_right = __x;
	__x->_parent = __y;
}

template <class _NodePtr>
void
__tree_balance_after_insert(_NodePtr __root, _NodePtr __x) _NOEXCEPT
{
	__x->_is_black = (int)(__x == __root);
	while (__x != __root && !__x->_parent->_is_black)
	{
		// __x->__parent_ != __root because __x->__parent_->__is_black == false
		if (__tree_is_left_child(__x->_parent))
		{
			_NodePtr __y = __x->_parent->_parent->_right;
			if (__y != nullptr && !__y->_is_black)
			{
				__x = __x->_parent;
				__x->_is_black = true;
				__x = __x->_parent;
				__x->_is_black = (int)(__x == __root);
				__y->_is_black = true;
			}
			else
			{
				if (!__tree_is_left_child(__x))
				{
					__x = __x->_parent;
					__tree_left_rotate(__x);
				}
				__x = __x->_parent;
				__x->_is_black = true;
				__x = __x->_parent;
				__x->_is_black = false;
				__tree_right_rotate(__x);
				break;
			}
		}
		else
		{
			_NodePtr __y = __x->_parent->_parent->_left;
			if (__y != nullptr && !__y->_is_black)
			{
				__x = __x->_parent;
				__x->_is_black = true;
				__x = __x->_parent;
				__x->_is_black = __x == __root;
				__y->_is_black = true;
			}
			else
			{
				if (__tree_is_left_child(__x))
				{
					__x = __x->_parent;
					__tree_right_rotate(__x);
				}
				__x = __x->_parent;
				__x->_is_black = true;
				__x = __x->_parent;
				__x->_is_black = false;
				__tree_left_rotate(__x);
				break;
			}
		}
	}
}

template <class Tp, class Compare, class Alloc>
class rb_tree
{
protected:
	struct rb_tree_node
	{
		bool			_is_black;
		rb_tree_node*	_parent;
		rb_tree_node*	_left;
		rb_tree_node*	_right;
		Tp				_value;

		rb_tree_node() : _is_black(true), _parent(nullptr), _left(nullptr), _right(nullptr), _value(Tp())
		{}
		rb_tree_node(Tp val) : _is_black(true), _parent(nullptr), _left(nullptr), _right(nullptr), _value(val)
		{}
		rb_tree_node(const rb_tree_node &x)
			: _is_black(x._is_black), _parent(x._parent), _left(x._left), _right(x._right), _value(x._value)
		{}
	};
	friend class rb_tree_node;

public:
	typedef Tp											value_type;
	//typedef Compare										key_compare;
	typedef Alloc										allocator_type;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	// node type=

	typedef typename Alloc::template rebind<rb_tree_node>::other	node_alloc_type;
	typedef typename node_alloc_type::pointer						link_type;
	typedef typename node_alloc_type::size_type						size_type;
	typedef typename node_alloc_type::difference_type				difference_type;

	// custom type
	typedef typename value_type::first_type							key_type;
	typedef typename value_type::second_type						mapped_type;

protected:
	link_type _begin;	// 최솟값을 가리킴
	link_type _end;		// 루트를 왼쪽 자식으로 가지는 것으로 정의된 _end노드.
	node_alloc_type _alloc;		// 노드할당기.

	link_type& root() { return left(_end); }
	link_type& root() const { return left(_end); }
	link_type& leftmost() { return _begin; }
	link_type& leftmost() const { return _begin; }
	// __tree_max
	link_type rightmost()
	{
		//link_type ret = static_cast<link_type>(__tree_max<link_type>(root()));
		//return ret;
		return static_cast<link_type>(__tree_max<link_type>(root()));
	}
	link_type rightmost() const
	{
		//link_type ret = static_cast<link_type>(__tree_max<link_type>(root()));
		//return ret;
		return static_cast<link_type>(__tree_max<link_type>(root()));
	}

	size_type node_count; // keeps track of size of tree
	bool insert_always;  // controls whether an element already in the
							// tree is inserted again

	Compare key_compare; // 필요없어 보이는데.,.?
	static link_type NIL; // 필요없도록 바꾸고 싶다.
	static link_type& left(link_type x) { return x->_left; }
	static link_type& right(link_type x) { return x->_right; }
	static link_type& parent(link_type x) { return x->_parent; }
	static reference value(link_type x) { return x->_value; }

	// ?
	// static Allocator<Key>::const_reference key(link_type x) {
	// 	return KeyOfValue()(value(x));
	// }
	static key_type key(link_type x) { return x->_value.first; }

	static bool color(link_type x) { return x->_is_black; }
	static link_type minimum(link_type x) {
		while (left(x) != NIL)
			x = left(x);
		return x;
	}
	static link_type maximum(link_type x) {
		while (right(x) != NIL)
			x = right(x);
		return x;
	}

// ITERATOR : ++ --  * -> == != cons dest copy
//========================================================================================
public:

	template <class T>
	class __iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef T											value_type;
		typedef ptrdiff_t									difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::bidirectional_iterator_tag	iterator_category;

		friend class rb_tree;
		friend class const_iterator;

	protected:
		link_type node;
		__iterator(link_type x) : node(x) {}
	public:
		__iterator() : node(nullptr) {}
		__iterator(const __iterator& x) : node(x.node) {}
		// const_iterator에 접근할 수 없다.
		//iterator(const const_iterator& x) : node(x.node) {}

		bool operator==(const __iterator& x) const { return node == x.node; }
		bool operator!=(const __iterator& x) const { return node != x.node;}

		Tp& operator*() const { return *(node->_value); }
		Tp* operator->() const { return &(node->_value); }

		// __tree_next_iter를 구현해야함.
		__iterator& operator++() { node = __tree_next_iter<link_type>(node); return *this; }
		__iterator operator++(int)
		{
			__iterator tmp = *this;
			++*this;
			return tmp;
		}
		__iterator& operator--() { node = __tree_prev_iter<link_type>(node); return *this; }
		__iterator operator--(int)
		{
			__iterator tmp = *this;
			--*this;
			return tmp;
		}
	};

	// 외않되
	//friend __iterator;

	typedef __iterator<Tp>									iterator;
	typedef __iterator<const Tp>							const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
//========================================================================================

// Custom member func
//========================================================================================
private:
	// __insert, __copy, __erase, init 함수,,
	void __init()
	{
		// allocate를 하면 construct를 어떻게 해야하지?
		_end = _alloc.allocate(1);
		_alloc.construct(_end, rb_tree_node());
		_begin = nullptr;
	}
	iterator __find(const key_type& k)
	{
		link_type x = root();
		link_type tmp = x;

		while (x != nullptr)
		{
			tmp = x;
			if (key_compare(k, key(x)))
				x = x->_left;
			else if (key_compare(key(x), k))
				x = x->_right;
			else
				return iterator(x);
		}

		return iterator(_end);
	}
	const_iterator __find(const key_type& k) const
	{
		link_type x = root();
		link_type tmp = x;

		while (x != nullptr)
		{
			tmp = x;
			if (key_compare(k, key(x)))
				x = x->_left;
			else if (key_compare(key(x), k))
				x = x->_right;
			else
				return const_iterator(x);
		}

		return const_iterator(_end);
	}

	// 노드할당 + 노드수증가
	iterator __insert(link_type x, link_type y, const value_type& v)
	{
		++node_count;

		// 내가 알던 초기화방식
		link_type n = _alloc.allocate(1);
		_alloc.construct(n, rb_tree_node(v));
		// placement new 방식
		// link_type n;
		// new(n) rb_tree_node(v);

		// 노드 추가
		// 1. 트리에 최초로 새 노드를 삽입한다.( x is root )
		// 2. x가 nil인 경우
		// 3. y의 왼쪽 자식으로 노드를 추가한다.]
		// 왼쪽으로 추가한다.
		if (y == _end || key_compare(key(n), key(y)))
		{
			y->_left = n;
			if (y == _end)
			{
				_begin = n; // // 이게 leftmost를 셋팅해준것과 동일하다.
				//rightmost() = n;
			}
			else if (y == leftmost())
				_begin = n;
		}
		else
		{
			y->_right = n;
			// if (y == rightmost())
			// 	rightmost() = n;
		}

		n->_parent = y;
		n->_left = nullptr;
		n->_right = nullptr;
		n->_is_black = false;

		// 규칙 만족 recolor and rebalance
		// __tree 2104 번째 줄을 참조.
		__tree_balance_after_insert<link_type>(root(), n);

		return iterator(n);
	}
//========================================================================================

public:

	rb_tree(Compare comp, bool always)
		: node_count(0), insert_always(always), key_compare(comp)
	{
		__init();
	};
	template <class InputIterator>
		rb_tree(InputIterator first, InputIterator last, Compare comp, bool always)
		: node_count(0), insert_always(always), key_compare(comp)
	{
		__init();
		// __insert(first, last)
	};
	// x에 const 안붙이니까 에러가 났다. 왜났지>?
	// map의 복사생성자에서 이녀석을 부르는데 map의 복사생성자에서 const파라미터를 받기때문에 여기서의 x도 const여야 한다.
	rb_tree(const rb_tree& x, bool always)
		: node_count(x.node_count), insert_always(x.insert_always), key_compare(x.key_compare)
	{
		__init();
		// *this = x;
	};
	rb_tree& operator=(const rb_tree& x)
	{
		// __insert(x.begin(), x.end())
	};

	// ?
	~rb_tree()
	{
		// begin~end지우기
		// end지우기
		// 멤버변수 0으로 바꾸기.
	};

// [O]Iteartors:
// const_iterator의 생성자 인자로 iterator를 넘겨줘도 돌아갈까?

	iterator begin() { return iterator(_begin); };
	const_iterator begin() const { return const_iterator(_begin); };
	iterator end() { return iterator(_end); };
	const_iterator end() const { return const_iterator(_end); };
	reverse_iterator rbegin() { return reverse_iterator(_begin); };
	const_reverse_iterator rbegin() const { return const_reverse_iterator(_begin); };
	reverse_iterator rend() { return reverse_iterator(_end); };
	const_reverse_iterator rend() const { return const_reverse_iterator(_end); };

// [O]Capacity:

	bool empty() const { return node_count == 0; };
	size_type size() const { return node_count; };
	size_type max_size() const { return _alloc.max_size(); };

// Modifiers:
	// pair <
	typedef pair<iterator, bool> pair_iterator_bool;
	// return pair_iterator_bool(__insert(x, y, val), true); 이 되나???

	// single
	pair_iterator_bool insert (const value_type& val)
	{
		link_type y = _end;
		link_type x = _end->_left; // root
		key_type k =  val.first;

		while (x != nullptr)
		{
			y = x;
			if (key_compare(k, key(x)))
				x = x->_left;
			else if (key_compare(key(x), k))
				x = x->_right;
			// else
			// 	return iterator(x);
		}
		// x,y = null, 추가될위치 부모

		// 중복 키값을 허용할 경우 추가한다.
		if (insert_always)
			return pair_iterator_bool(__insert(x, y, val), true);
		// y의 복사본 j
		iterator j = iterator(y);

		// k < y's key key_compare(k, key(y))
		if (key_compare(k, key(j.node)))
		{
			if (j == begin())
				return pair_iterator_bool(__insert(x, y, val), true);
			else
				--j;
		}
		if (key_compare(key(j.node), k))
			return pair_iterator_bool(__insert(x, y, val), true);
		// 중복된 원소를 넣으려고 함.
		return pair_iterator_bool(j, false);
	};
	// with hint
	iterator insert (iterator pos, const value_type& val);
	// range
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last);

	void erase(iterator position);
	size_type erase(const key_type& k);
	void erase(iterator first, iterator last);

	void swap(rb_tree& x)
	{
		link_type tmp_begin = x._begin;
		link_type tmp_end = x._end;
		node_alloc_type tmp_alloc = x._alloc ;
		size_type tmp_size = x.node_count;
		bool tmp_always = x.insert_always;

		x._begin = _begin;
		x._end = _end;
		x._alloc = _alloc;
		x.node_count = node_count;
		x.insert_always = insert_always;

		_begin = tmp_begin;
		_end = tmp_end;
		_alloc = tmp_alloc;
		node_count = tmp_size;
		insert_always = tmp_always;
	};
	void clear()
	{
		// __tree기준

		// destroy(__root)
		// size = 0
		// _begin = _end
		// _end->_left = nullptr
	}

// [O]Observers:

	Compare key_comp() const { return key_comp(); }

// map operations:

	iterator find(const key_type& k);
	const_iterator find(const key_type& k) const;
	size_type count(const key_type& k) const;
	iterator lower_bound(const key_type& k);
	const_iterator lower_bound(const key_type& k) const;
	iterator upper_bound(const key_type& k);
	const_iterator upper_bound(const key_type& k) const;

	typedef ft::pair<iterator, iterator> pair_iterator_iterator;

	// 없을시, upper_bound(k) 2개를 pair에 넣어 반환
	pair_iterator_iterator equal_range(const key_type& x);

	typedef ft::pair<const_iterator, const_iterator> pair_citerator_citerator;
	pair_citerator_citerator equal_range(const key_type& x) const;
};

}

#endif
