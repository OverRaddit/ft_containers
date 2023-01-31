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

# include <iterator> // distance
# include "utility.hpp"
# include <type_traits>

# include "tree_algorithm.hpp"
namespace ft
{
// // set
// template <class Tp>
// class tree_key_value_types
// {
// 	typedef Tp					key_type;
// };

// // map
// template <class pair>
// class tree_key_value_types
// {
// 	typedef typename pair::first_type	key_type;
// 	typedef typename pair::second_type	mapped_type;
// };

// _tree_iterator

template <class Node>
class __const_iterator;
template <class Node>
class __iterator;

template <class Node>
class __iterator
{
	friend class __const_iterator<Node>;
	//friend class rb_tree<Tp, Compare, Alloc>;
public:
	// C++11 함수이므로 커스텀 함수로 제작할것.
	//typedef typename std::remove_const<T>::type value_type;
	typedef typename Node::data					value_type;
	typedef ptrdiff_t							difference_type;
	typedef value_type*							pointer;
	typedef value_type&							reference;
	// 다른 <iterator> 함수들의 호환성을 위해 std의 태그를 사용한다.
	typedef std::bidirectional_iterator_tag		iterator_category;

	typedef typename Node::data				data;
protected:
public:
	Node* node;
	__iterator(Node* x) : node(x) {}
	__iterator() : node(nullptr) {}
	__iterator(const __iterator& x) : node(x.node) {}

	// __iterator만 가질 수 있다.
	__iterator& operator=(const __iterator& x)
	{
		node = x.node;
		return *this;
	}

	bool operator==(const __iterator& x) const { return node == x.node; }
	bool operator!=(const __iterator& x) const { return node != x.node;}

	reference operator*() const { return node->_value; }
	pointer operator->() const { return &(node->_value); }

	// __tree_next_iter를 구현해야함.
	__iterator& operator++() { node = ft::__tree_next_iter<Node*>(node); return *this; }
	__iterator operator++(int)
	{
		__iterator tmp = *this;
		++*this;
		return tmp;
	}
	__iterator& operator--() { node = ft::__tree_prev_iter<Node*>(node); return *this; }
	__iterator operator--(int)
	{
		__iterator tmp = *this;
		--*this;
		return tmp;
	}
};

template <class Node>
class __const_iterator
{
	friend class __iterator<Node>;
	//friend class rb_tree<Tp, Compare, Alloc>;
public:
	typedef typename Node::data					value_type;
	typedef ptrdiff_t							difference_type;
	typedef value_type*							pointer;
	typedef value_type&							reference;
	typedef std::bidirectional_iterator_tag		iterator_category;

	typedef typename Node::data					data;
protected:
public:
	Node* node;
	__const_iterator(Node* x) : node(x) {}
	__const_iterator() : node(nullptr) {}
	__const_iterator(const __iterator<Node>& x) : node(x.node) {}
	__const_iterator(const __const_iterator& x) : node(x.node) {}

	__const_iterator& operator=(const __const_iterator& x)
	{
		node = x.node;
		return *this;
	}
	bool operator==(const __const_iterator& x) const { return node == x.node; }
	bool operator!=(const __const_iterator& x) const { return node != x.node;}

	reference operator*() const { return node->_value; }
	pointer operator->() const { return &(node->_value); }
	__const_iterator& operator++() { node = ft::__tree_next_iter<Node*>(node); return *this; }
	__const_iterator operator++(int)
	{
		__const_iterator tmp = *this;
		++*this;
		return tmp;
	}
	__const_iterator& operator--() { node = ft::__tree_prev_iter<Node*>(node); return *this; }
	__const_iterator operator--(int)
	{
		__const_iterator tmp = *this;
		--*this;
		return tmp;
	}

};

template <class Tp>
struct rb_tree_node
{
	typedef Tp data;

	bool			_is_black;
	rb_tree_node*	_parent;
	rb_tree_node*	_left;
	rb_tree_node*	_right;
	Tp				_value;

	rb_tree_node() : _is_black(true), _parent(nullptr), _left(nullptr), _right(nullptr), _value(Tp())
	{}
	rb_tree_node(const Tp val) : _is_black(true), _parent(nullptr), _left(nullptr), _right(nullptr), _value(val)
	{}
	rb_tree_node(const rb_tree_node &x)
		: _is_black(x._is_black), _parent(nullptr), _left(nullptr), _right(nullptr), _value(x._value)
	{}

	~rb_tree_node()
	{
		_left = nullptr;
		_right = nullptr;
		_parent = nullptr;
		_is_black = false;
	}
};

template <class Tp, class Compare, class Alloc>
class rb_tree
{
public:
	typedef Alloc												allocator_type;

	typedef typename allocator_type::value_type					value_type;
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	// node type
	typedef rb_tree_node<value_type>							node_type;
	typedef typename Alloc::template rebind<node_type>::other	node_alloc_type;
	typedef typename node_alloc_type::pointer					link_type;
	typedef typename node_alloc_type::const_pointer				const_link_type;
	typedef typename node_alloc_type::size_type					size_type;
	typedef typename node_alloc_type::difference_type			difference_type;

	// custom type
	// typedef typename tree_key_value_types::key_type				key_type;
	// typedef typename tree_key_value_types::mapped_type			mapped_type;
	typedef typename value_type::first_type						key_type;
	typedef typename value_type::second_type					mapped_type;


protected:
	link_type _begin;	// 최솟값을 가리킴
	link_type _end;		// 루트를 왼쪽 자식으로 가지는 것으로 정의된 _end노드.
	node_alloc_type _alloc;		// 노드할당기.

	link_type& root() { return left(_end); }
	link_type& root() const { return left(_end); }

	// empty()일때 _begin은 _end를 가리킨다...
	link_type& leftmost() { return _begin; }
	link_type& leftmost() const { return _begin; }

	// __tree_max
	link_type& rightmost()
	{
		return _end->_right;
	}
	link_type& rightmost() const
	{
		return _end->_right;
	}

	size_type node_count; // keeps track of size of tree
	bool insert_always;  // controls whether an element already in the
							// tree is inserted again

	Compare key_compare; // 필요없어 보이는데.,.?
	static link_type& left(link_type x) { return x->_left; }
	static link_type& right(link_type x) { return x->_right; }
	static link_type& parent(link_type x) { return x->_parent; }
	static reference value(link_type x) { return x->_value; }

	static key_type key(link_type x) { return x->_value.first; }

	static bool color(link_type x) { return x->_is_black; }
	// static link_type minimum(link_type x) {
	// 	while (left(x) != NIL)
	// 		x = left(x);
	// 	return x;
	// }
	// static link_type maximum(link_type x) {
	// 	while (right(x) != NIL)
	// 		x = right(x);
	// 	return x;
	// }

// ITERATOR : ++ --  * -> == != cons dest copy
//========================================================================================
public:
	// template <class Node>
	// class __const_iterator;
	// template <class Node>
	// class __iterator;

	friend class __const_iterator<rb_tree_node<value_type> >;
	friend class __iterator<rb_tree_node<value_type> >;

	typedef	__iterator<rb_tree_node<value_type> >			iterator;
	typedef __const_iterator<rb_tree_node<value_type> >		const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
//========================================================================================

// Custom member func
//========================================================================================
private:
	typedef ft::pair<iterator, iterator> pair_iterator_iterator;
	typedef ft::pair<const_iterator, const_iterator> pair_citerator_citerator;
	// __insert, __copy, __erase, init 함수,,
	void __init()
	{
		// allocate를 하면 construct를 어떻게 해야하지?
		_end = _alloc.allocate(1);
		_alloc.construct(_end, rb_tree_node<Tp>());
		_begin = _end;
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
		_alloc.construct(n, rb_tree_node<Tp>(v));
		// placement new 방식
		// link_type n;
		// new(n) rb_tree_node(v);

		// 노드 추가
		// 1. 트리에 최초로 새 노드를 삽입한다.( x is root )
		// 2. x가 nil인 경우
		// 3. y의 왼쪽 자식으로 노드를 추가한다.]
		// 왼쪽으로 추가한다.
		if (y == _end || x != nullptr || key_compare(key(n), key(y)))
		{
			y->_left = n;
			if (y == _end)
			{
				_begin = n; // // 이게 leftmost를 셋팅해준것과 동일하다.
				rightmost() = n;
			}
			else if (y == leftmost())
				_begin = n;
		}
		else
		{
			y->_right = n;
			if (y == rightmost())
				rightmost() = n;
		}

		n->_parent = y;
		n->_left = nullptr;
		n->_right = nullptr;
		n->_is_black = false;

		// 규칙 만족 recolor and rebalance
		// __tree 2104 번째 줄을 참조.
		ft::__tree_balance_after_insert<link_type>(root(), n);

		return iterator(n);
	}

	// clear
	void __clear(link_type x)
	{
		if (x == nullptr) return;

		link_type l = x->_left, r = x->_right;

		_alloc.destroy(x);
		_alloc.deallocate(x, 1);
		//delete x;

		if(l != nullptr)
			__clear(l);
		if(r != nullptr)
			__clear(r);
	}

	// 매우 비효율적...
	link_type __copy(link_type origin, link_type copy)
	{
		_alloc.construct(copy, *origin); //copy = origin;

		copy->_left = _alloc.allocate(1);
		copy->_right = _alloc.allocate(1);
		__copy(origin->_left, copy->_left);
		__copy(origin->_right, copy->_right);
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
		insert(first, last);
	};

	rb_tree(const rb_tree& x, bool always)
		: node_count(x.node_count), insert_always(always), key_compare(x.key_compare)
	{
		__init();
		insert(x.begin(), x.end());
	};
	rb_tree& operator=(const rb_tree& x)
	{
		clear();
		insert(x.begin(), x.end());

		insert_always = x.insert_always;
		key_compare = x.key_compare;

		return *this;
	};
	~rb_tree()
	{
		if (!_end)
			return ;
		_end->_right = nullptr;
		__clear(_end->_left);
		delete _end;
	};

// [O]Iteartors:
// 여기서 const가 붙은 멤버함수를 정의해주기 때문에 Const context일때 const_iterator가 사용되는 것이다.

	iterator begin() { return iterator(_begin); };
	const_iterator begin() const { return const_iterator(_begin); };
	iterator end() { return iterator(_end); };
	const_iterator end() const { return const_iterator(_end); };

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
			else
				break;
			// else
			// 	return iterator(x);
		}
		// x,y = null, 추가될위치 부모

		if (empty())
			return pair_iterator_bool(__insert(x, y, val), true);

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
	iterator insert (iterator pos, const value_type& val)
	{
		// if (pos == end())
		// {
 		// 	if (!empty() && key_compare(key(rightmost()), val.first))
		// 		return __insert(nullptr, rightmost(), val);
		// 	return __insert ()
		// }
		// if (key_compare(val.first, key(pos.node)) && pos.node->_left == nullptr)
		// 	return __insert(pos.node, pos.node, val);
		// return insert(val).first;



		if (pos == begin())
		{
			// 왼 자식으로 삽입.
			if (!empty() && key_compare(val.first, key(pos.node)))
				return __insert(pos.node, pos.node, val);
			return insert(val).first;
		}
		else if (pos == end())
		{
			// 오른 자식으로 삽입.
			if (key_compare(key(rightmost()), val.first))
				return __insert(nullptr, rightmost(), val);
			return insert(val).first;
		}
		else
		{
			iterator before = --pos;
			if (key_compare(key(before.node), val.first) &&
				key_compare(val.first, key(pos.node)))
			{
				// =========================== 어렵당...
				if (right(before.node) == nullptr)
					return __insert(nullptr, before.node, val);
				else
					return __insert(pos.node, pos.node, val);
				// first argument just needs to be non-NIL
				// if (pos->_left == nullptr)
				// 	return __insert(pos.node, pos.node, val);
				// else if (right(before.node) == NIL)
				// 	return __insert(NIL, before.node, val);
				// ===========================
			}
			return insert(val).first;
		}
	};
	// range
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		while (first != last) insert(*first++);
	};

	void erase(iterator position)
	{
		if (position == begin())
			_begin = __tree_next_iter(_begin);
		ft::__tree_remove<link_type>(root(), position.node);
		delete position.node;
		node_count--;
	};
	// 반환값??
	size_type erase(const key_type& k)
	{
		pair_iterator_iterator range = equal_range(k);
		size_type ret = std::distance(range.first, range.second);

		erase(range.first, range.second);
		return ret;
	};
	void erase(iterator first, iterator last)
	{
		while (first != last) erase(first++);
	};

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
		__clear(_end->_left);
		_begin = _end;
		_end->_right = nullptr;
		_end->_left = nullptr;
		node_count = 0;
	}

// [O]Observers:

	Compare key_comp() const { return key_compare; }

// map operations:

	iterator find(const key_type& k)
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
		return iterator(tmp);
	};
	const_iterator find(const key_type& k) const
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
		return const_iterator(tmp);
	};
	// 특정키값이 있는지 찾을것.
	size_type count(const key_type& k) const
	{
		return std::distance(lower_bound(k), upper_bound(k));
	};
	iterator lower_bound(const key_type& k)
	{
		link_type x = root();
		link_type tmp = _end;

		while (x != nullptr)
		{
			if (key_compare(key(x), k))
				x = x->_right;
			else
			{
				tmp = x;
				x = x->_left;
			}
		}
		return iterator(tmp);
	};
	const_iterator lower_bound(const key_type& k) const
	{
		link_type x = root();
		link_type tmp = _end;

		while (x != nullptr)
		{
			tmp = x;
			if (key_compare(key(x), k))
				x = x->_right;
			else
			{
				tmp = x;
				x = x->_left;
			}
		}
		return const_iterator(tmp);
	};

	iterator upper_bound(const key_type& k)
	{
		link_type x = root();
		link_type tmp = _end;

		while (x != nullptr)
		{
			if (key_compare(k, key(x)))
			{
				tmp = x;
				x = x->_left;
			}
			else
				x = x->_right;
		}
		return iterator(tmp);
	};
	const_iterator upper_bound(const key_type& k) const
	{
		link_type x = root();
		link_type tmp = _end;

		while (x != nullptr)
		{
			if (key_compare(k, key(x)))
			{
				tmp = x;
				x = x->_left;
			}
			else
				x = x->_right;
		}
		return const_iterator(tmp);
	};

	pair_iterator_iterator equal_range(const key_type& x)
	{
		return pair_iterator_iterator(lower_bound(x), upper_bound(x));
	};
	pair_citerator_citerator equal_range(const key_type& x) const
	{
		return pair_citerator_citerator(lower_bound(x), upper_bound(x));
	};

};
template <class Tp, class Compare, class Alloc>
bool operator==(const rb_tree<Tp, Compare, Alloc>& lhs,
				const rb_tree<Tp, Compare, Alloc>& rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Tp, class Compare, class Alloc>
bool operator<(const rb_tree<Tp, Compare, Alloc>& lhs,
				const rb_tree<Tp, Compare, Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

}

#endif
