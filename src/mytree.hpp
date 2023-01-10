#ifndef TREE_H
#define TREE_H

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

#ifndef rb_tree
#define rb_tree rb_tree
#endif

// KeyOfValue = value_compare, Compare = key_compare
// KeyOfValue는 Value에서 Key를 꺼내주는 함수객체이다.
// KeyOfValue는 Value가 pair를 쓰므로 first를 통해 얻을 수 있따.
// 즉 필요없다.
template <class Key, class Value, class KeyOfValue, class Compare, class _Allocator>
class rb_tree {
protected:
	enum color_type {red, black};
	typedef _Allocator::rebind<void>::other::pointer	void_pointer; // 이게 맞나?
	struct rb_tree_node;
	friend rb_tree_node;
	struct rb_tree_node {
		color_type color_field;
		void_pointer parent_link;
		void_pointer left_link;
		void_pointer right_link;
		Value value_field;
	};
public:
	typedef Key key_type;
	typedef Value value_type;
	// 값에 대한 타입
	typedef _Allocator::pointer								pointer;
	typedef _Allocator::reference							reference;
	typedef _Allocator::const_reference						const_reference;
	// 노드에 대한 타입
	typedef _Allocator::rebind<rb_tree_node>::other			rb_tree_node_allocator_type;
	typedef rb_tree_node_allocator_type::pointer			link_type;
	typedef rb_tree_node_allocator_type::size_type			size_type;
	typedef rb_tree_node_allocator_type::difference_type	difference_type;
protected:
	static rb_tree_node_allocator_type rb_tree_node_allocator;
	static _Allocator value_allocator;

	// 대충 노드 한개의 메모리크기를 반환해주는 함수.
	// std::allocator에서는 필요없는 방식이다.
	size_type buffer_size() { return rb_tree_node_allocator.init_page_size(); }

	// 어째서 buffer를 사용하는지 이해가 가지 않는다.
	struct rb_tree_node_buffer;
	friend rb_tree_node_buffer;
	struct rb_tree_node_buffer
	{
		void_pointer next_buffer;
		link_type buffer;
	};
public:
	typedef _Allocator::rebind<rb_tree_node_buffer>::other	buffer_allocator_type;
	typedef buffer_allocator_type::pointer					buffer_pointer;
protected:
	// 이 변수들은 멤버변수가 아니라 정적변수이다. 클래스들이 공유하는 값이다.
	// 왜 이런 공유변수를 정의하였는지 이해가 가지 않는다.
	// 만약 노드를 잘못처리해서 노드를 가리키는 포인터가 없어져도 static변수에서 해당 노드를 참조할 수 있게된다.
	static buffer_allocator_type buffer_allocator;
	static buffer_pointer buffer_list;		// Node_Buffer의 헤드포인터이다.
	static link_type free_list;				// root이다.
	static link_type next_avail;			// 맨앞노드버퍼의 노드
	static link_type last;					// stl vector 에서 end()같은 역할을 한다.

	// 새로운 노드버퍼를 추가한다.
	void add_new_buffer()
	{
		buffer_pointer tmp = buffer_allocator.allocate(1);
		// tmp->buffer에 노드1개 크기만큼 할당한다.
		tmp->buffer = rb_tree_node_allocator.allocate(buffer_size());
		// next 연결 && head 최신화
		tmp->next_buffer = buffer_list;
		buffer_list = tmp;
		next_avail = buffer_list->buffer;
		// 맨앞노드버퍼의 노드 뒤를 가리킴. 왜..>?
		last = next_avail + buffer_size();
	}
	static size_type number_of_trees;
	void deallocate_buffers();
	// ??
	link_type get_node() {
		link_type tmp = free_list;
		return free_list ?
			(free_list = (link_type)(free_list->right_link), tmp) // ???????
				: (next_avail == last ? (add_new_buffer(), next_avail++)
					: next_avail++);
		// ugly code for inlining - avoids multiple returns
	}
	// p의 우측자식에 루트를 연결하고 p를 새로운 루트로 설정한다.
	void put_node(link_type p)
	{
		p->right_link = free_list;
		free_list = p;
	}
protected:
	// // header의 부모는 root, 왼쪽은 트리최솟값, 오른쪽은 트리 최댓값. begin, end의 상수시간 호출을 위해 선언한 것으로 예상됨.
	link_type header;
	link_type& root() { return parent(header); }
	link_type& root() const { return parent(header); }
	link_type& leftmost() { return left(header); }
	link_type& leftmost() const { return left(header); }
	link_type& rightmost() { return right(header); }
	link_type& rightmost() const { return right(header); }
	size_type node_count; // keeps track of size of tree
	bool insert_always;  // controls whether an element already in the
							// tree is inserted again
//public:
	Compare key_compare;
	// 왜 static으로 선언한거지?
	// 멤버함수로 선언하면, 인스턴스가 존재해야 사용할 수 있다.
	// static함수로 선언해서 인스턴스가 없어도 호출할 수 있게 한 것이다.
	static link_type NIL;
	static link_type& left(link_type x) { return (link_type&)((*x).left_link); }
	static link_type& right(link_type x) { return (link_type&)((*x).right_link); }
	static link_type& parent(link_type x) { return (link_type&)((*x).parent_link); }
	static reference value(link_type x) { return (*x).value_field; }
	// link_type에서 key에 접근해주는 함수
	static Allocator<Key>::const_reference key(link_type x)
	{ return KeyOfValue()(value(x)); }
	static color_type& color(link_type x) { return (color_type&)(*x).color_field; }
	static link_type minimum(link_type x)
	{
		while (left(x) != NIL)
			x = left(x);
		return x;
	}
	static link_type maximum(link_type x)
	{
		while (right(x) != NIL)
			x = right(x);
		return x;
	}
public:
	class iterator;
	friend iterator;
	class const_iterator;
	friend const_iterator;
	//class iterator : public bidirectional_iterator<Value, difference_type>
	class iterator : public std::iterator<std::bidirectional_iterator_tag, Value>
	{
	friend class rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>;
	friend class const_iterator;	// 왜 해주는지 모르겠다.
	/*
	friend bool operator==(const iterator& x, const iterator& y) {
		return x.node == y.node;
	}
	*/
	protected:
		link_type node;
		iterator(link_type x) : node(x) {}
	public:
		iterator() {}
		bool operator==(const iterator& y) const { return node == y.node; }
		reference operator*() const { return value(node); }
		iterator& operator++()
		{
			// 우측자식이 존재시, 우측서브트리의 최솟값을 반환
			if (right(node) != NIL)
			{
				node = right(node);
				while (left(node) != NIL)
					node = left(node);
			}
			// 없다면 현재노드가 부모의 좌측노드가 될때까지 올라간다.
			else
			{
				link_type y = parent(node);
				while (node == right(y)) {
					node = y;
					y = parent(y);
				}
				if (right(node) != y) // necessary because of rightmost
					node = y;
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++*this;
			return tmp;
		}
		iterator& operator--()
		{
			if (color(node) == red && parent(parent(node)) == node)
			{
				// check for header
				node = right(node);   // return rightmost
			}
			else if (left(node) != NIL)
			{
				link_type y = left(node);
				while (right(y) != NIL)
					y = right(y);
				node = y;
			}
			else
			{
				link_type y = parent(node);
				while (node == left(y)) {
					node = y;
					y = parent(y);
				}
				node = y;
			}
			return *this;
		}
		iterator operator--(int) {
			iterator tmp = *this;
			--*this;
			return tmp;
		}
	};
	class const_iterator
		: public bidirectional_iterator<Value,difference_type>
	{
	friend class rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>;
	friend class iterator;
/*
	friend bool operator==(const const_iterator& x, const const_iterator& y) {
		return x.node == y.node;
	}
*/
	protected:
		link_type node;
		const_iterator(link_type x) : node(x) {}
	public:
		const_iterator() {}
		const_iterator(const iterator& x) : node(x.node) {}
		bool operator==(const const_iterator& y) const {
			return node == y.node;
		}
		bool operator!=(const const_iterator& y) const {
			return node != y.node;
		}
		const_reference operator*() const { return value(node); }
		const_iterator& operator++() {
			if (right(node) != NIL) {
				node = right(node);
				while (left(node) != NIL)
					node = left(node);
			} else {
				link_type y = parent(node);
				while (node == right(y)) {
					node = y;
					y = parent(y);
				}
				if (right(node) != y) // necessary because of rightmost
					node = y;
			}
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator tmp = *this;
			++*this;
			return tmp;
		}
		const_iterator& operator--() {
			if (color(node) == red && parent(parent(node)) == node)
				// check for header
				node = right(node);   // return rightmost
			else if (left(node) != NIL) {
				link_type y = left(node);
				while (right(y) != NIL)
					y = right(y);
				node = y;
			} else {
				link_type y = parent(node);
				while (node == left(y)) {
					node = y;
					y = parent(y);
				}
				node = y;
			}
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator tmp = *this;
			--*this;
			return tmp;
		}
	};
	// 이게 왜 여기에 선언되어있지?
	typedef reverse_bidirectional_iterator<iterator, value_type, reference,
											difference_type>
		reverse_iterator;
	typedef reverse_bidirectional_iterator<const_iterator, value_type,
											const_reference, difference_type>
	const_reverse_iterator;
private:
	// x는 NIL노드, y는 추가할 위치의 leaf노드.
	// x는 필요없는거 아닌가...?
	iterator __insert(link_type x, link_type y, const value_type& v)
	{
		++node_count;
		link_type z = get_node();

		// v값으로 z노드를 초기화한다.
		// std::allocator 형식으로 바꿔야 함.
		// value_allocator.construct(value(z), v); // 이렇게!
		construct(value_allocator.address(value(z)), v);

		if (y == header || x != NIL || key_compare(KeyOfValue()(v), key(y)))
		{
			left(y) = z;  // also makes leftmost() = z when y == header
			if (y == header) {
				root() = z;
				rightmost() = z;
			} else if (y == leftmost())
				leftmost() = z;   // maintain leftmost() pointing to minimum node
		}
		else
		{
			right(y) = z;
			if (y == rightmost())
				rightmost() = z;   // maintain rightmost() pointing to maximum node
		}
		parent(z) = y;
		left(z) = NIL;
		right(z) = NIL;
		x = z;  // recolor and rebalance the tree
		color(x) = red;
		while (x != root() && color(parent(x)) == red)
			if (parent(x) == left(parent(parent(x))))
			{
				y = right(parent(parent(x)));
				if (color(y) == red) {
					color(parent(x)) = black;
					color(y) = black;
					color(parent(parent(x))) = red;
					x = parent(parent(x));
				} else {
					if (x == right(parent(x))) {
						x = parent(x);
						rotate_left(x);
					}
					color(parent(x)) = black;
					color(parent(parent(x))) = red;
					rotate_right(parent(parent(x)));
				}
			}
			else
			{
				y = left(parent(parent(x)));
				if (color(y) == red) {
					color(parent(x)) = black;
					color(y) = black;
					color(parent(parent(x))) = red;
					x = parent(parent(x));
				} else {
					if (x == left(parent(x))) {
						x = parent(x);
						rotate_right(x);
					}
					color(parent(x)) = black;
					color(parent(parent(x))) = red;
					rotate_left(parent(parent(x)));
				}
			}
		color(root()) = black;
		return iterator(z);	// 추가한 노드 이터를 반환
	};
	link_type __copy(link_type x, link_type p)
	{
		// structural copy
		link_type r = x;
		while (x != NIL)
		{
			link_type y = get_node();
			if (r == x) r = y;  // save for return value
			construct(value_allocator.address(value(y)), value(x));
			left(p) = y;
			parent(y) = p;
			color(y) = color(x);
			right(y) = __copy(right(x), y);
			p = y;
			x = left(x);
		}
		left(p) = NIL;
		return r;
	};
	void __erase(link_type x)
	{
		// erase without rebalancing
		while (x != NIL)
		{
			__erase(right(x));
			link_type y = left(x);
			destroy(value_allocator.address(value(x)));
			put_node(x);
			x = y;
		}
	};
	void init()
	{
		++number_of_trees;
		if (NIL == 0) {
			NIL = get_node();
			color(NIL) = black;
			parent(NIL) = 0;
			left(NIL) = 0;
			right(NIL) = 0;
		}
		header = get_node();
		color(header) = red;  // used to distinguish header from root,
								// in iterator.operator++
		root() = NIL;
		leftmost() = header;
		rightmost() = header;
	}
public:

// allocation/deallocation
// insert_always default value : true -> false

	rb_tree(const Compare& comp = Compare(), bool always = false)
			: node_count(0), key_compare(comp), insert_always(always) {
		init();
	}
	rb_tree(const value_type* first, const value_type* last,
			const Compare& comp = Compare(), bool always = false)
			: node_count(0), key_compare(comp), insert_always(always) {
		init();
		insert(first, last);
	}
	rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>& x,
			bool always = false) : node_count(x.node_count),
					key_compare(x.key_compare), insert_always(always) {
		++number_of_trees;
		header = get_node();
		color(header) = red;
		root() = __copy(x.root(), header);
		if (root() == NIL) {
			leftmost() = header;
			rightmost() = header;
		} else {
		leftmost() = minimum(root());
			rightmost() = maximum(root());
		}
	}
	~rb_tree() {
		erase(begin(), end());
		put_node(header);
		if (--number_of_trees == 0) {
			put_node(NIL);
			NIL = 0;
			deallocate_buffers();
			free_list = 0;
			next_avail = 0;
			last = 0;
		}
	}
	rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>&
		operator=(const rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>& x)
	{
		if (this != &x)
		{
			// can't be done as in list because Key may be a constant type
			erase(begin(), end());
			root() = __copy(x.root(), header);
			if (root() == NIL)
			{
				leftmost() = header;
				rightmost() = header;
			}
			else
			{
				leftmost() = minimum(root());
				rightmost() = maximum(root());
			}
			node_count = x.node_count;
		}
		return *this;
	};

// accessors:

	Compare key_comp() const { return key_compare; }
	// make this constant time.
	// why header node when end()?
	iterator begin() { return leftmost(); }
	const_iterator begin() const { return leftmost(); }
	iterator end() { return header; }
	const_iterator end() const { return header; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	bool empty() const { return node_count == 0; }
	size_type size() const { return node_count; }
	size_type max_size() const { return rb_tree_node_allocator.max_size(); }
	void swap(rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>& t)
	{
		::swap(header, t.header);
		::swap(node_count, t.node_count);
		::swap(insert_always, t.insert_always);
		::swap(key_compare, t.key_compare);
	}

// insert/erase

	typedef ft::pair<iterator, bool> pair_iterator_bool;
	// typedef done to get around compiler bug
	pair_iterator_bool insert(const value_type& x);
	iterator insert(iterator position, const value_type& x);
	void insert(iterator first, iterator last);
	void insert(const value_type* first, const value_type* last);
	void erase(iterator position);
	size_type erase(const key_type& x)
	{
		pair_iterator_iterator p = equal_range(x);
		size_type n = 0;
		distance(p.first, p.second, n);
		erase(p.first, p.second);
		return n;
	};
	void erase(iterator first, iterator last);
	void erase(const key_type* first, const key_type* last);

// set operations:

	iterator find(const key_type& x);
	const_iterator find(const key_type& x) const;
	size_type count(const key_type& x) const
	{
		pair<const_iterator, const_iterator> p = equal_range(k);
		size_type n = 0;
		distance(p.first, p.second, n);

		return n;
	};
	iterator lower_bound(const key_type& x);
	const_iterator lower_bound(const key_type& x) const;
	iterator upper_bound(const key_type& x);
	const_iterator upper_bound(const key_type& x) const;
	typedef  pair<iterator, iterator> pair_iterator_iterator;
	// typedef done to get around compiler bug
	pair_iterator_iterator equal_range(const key_type& x);
	typedef  pair<const_iterator, const_iterator> pair_citerator_citerator;
	// typedef done to get around compiler bug
	pair_citerator_citerator equal_range(const key_type& x) const;
	inline void rotate_left(link_type x)
	{
		link_type y = right(x);
		right(x) = left(y);
		if (left(y) != NIL)
			parent(left(y)) = x;
		parent(y) = parent(x);
		if (x == root())
			root() = y;
		else if (x == left(parent(x)))
			left(parent(x)) = y;
		else
			right(parent(x)) = y;
		left(y) = x;
		parent(x) = y;
	};
	inline void rotate_right(link_type x)
	{
		link_type y = left(x);
		left(x) = right(y);
		if (right(y) != NIL)
			parent(right(y)) = x;
		parent(y) = parent(x);
		if (x == root())
			root() = y;
		else if (x == right(parent(x)))
			right(parent(x)) = y;
		else
			left(parent(x)) = y;
		right(y) = x;
		parent(x) = y;
	};
};

// ?????????????

template <class Key, class Value, class KeyOfValue, class Compare, class _Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Allocator>::buffer_pointer
        rb_tree<Key, Value, KeyOfValue, Compare, _Allocator>::buffer_list = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::link_type
        rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::free_list = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::link_type
        rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::next_avail = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::link_type
        rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::last = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::size_type
        rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::number_of_trees = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::rb_tree_node_allocator_type
        rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::rb_tree_node_allocator;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
_Alloc rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::value_allocator;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::buffer_allocator_type
        rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::buffer_allocator;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::link_type
        rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::NIL = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::deallocate_buffers()
{
	while (buffer_list)
	{
		buffer_pointer tmp = buffer_list;
		buffer_list = (buffer_pointer)(buffer_list->next_buffer);
		rb_tree_node_allocator.deallocate(tmp->buffer);
		buffer_allocator.deallocate(tmp);
	}
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
inline bool operator==(const rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>& x,
                       const rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>& y) {
    return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
inline bool operator<(const rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>& x,
                      const rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>& y) {
    return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

// single insert
// 삽입할 위치를 찾는다.
// 중복된 원소가 존재할 경우의 처리를 해준다(insert_always값에 따라 다르게 처리할 수 있음.)
template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::pair_iterator_bool
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::insert(const Value& v) {
	link_type y = header;
	link_type x = root();
	bool comp = true;
	// 추가할 값의 키를 통해 루트에서 적절한 위치를 찾아 내려간다.
	// 중복된 값을 찾으면 멈춰야 되는 거 아닌가? 왜 안멈추고 오른쪽으로 내려가지?
	while (x != NIL) {
		y = x;
		comp = key_compare(KeyOfValue()(v), key(x));
		x = comp ? left(x) : right(x);
	}
	// 이 시점에서 x는 NIL노드, y는 추가할 위치의 leaf노드에 해당한다.
	// 아니면, x는 NIL노드, y는 v와 동일한 키를가진 노드에 해당할 수도 있다. -> 중복된 값을 insert하려는중!!
	if (insert_always) // insert_always 값에 따라 중복된 노드가 허락할지 말지 결정할 수 있다.
		return pair_iterator_bool(__insert(x, y, v), true);
	iterator j = iterator(y);
	// x가 y의 왼쪽자식인 경우.
	// v키 < y키
	if (comp)
	{
		if (j == begin()) // 추가하려는 노드가 최솟값이라면,,
			return pair_iterator_bool(__insert(x, y, v), true);
		else
			--j;	// j는 x가 된다.
	}

	if (key_compare(key(j.node), KeyOfValue()(v)))
		return pair_iterator_bool(__insert(x, y, v), true);
	return pair_iterator_bool(j, false);
}

// insert with hint
// 새로 추가한 노드나 중복된 삽입인 경우에 이미 존재하는 노드를 이터로 반환한다.
template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::insert(iterator position,
                                                 const Value& v) {
	if (position == iterator(begin()))
	{
		if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
			return __insert(position.node, position.node, v);
			// first argument just needs to be non-NIL
		else
			return insert(v).first;
	}
	else if (position == iterator(end()))
	{

		if (key_compare(key(rightmost()), KeyOfValue()(v)))
			return __insert(NIL, rightmost(), v);
		else
			return insert(v).first;
	}
	else
	{
		iterator before = --position;
		if (key_compare(key(before.node), KeyOfValue()(v))
			&& key_compare(KeyOfValue()(v), key(position.node)))
			if (right(before.node) == NIL)
				return __insert(NIL, before.node, v);
			else
				return __insert(position.node, position.node, v);
				// first argument just needs to be non-NIL
		else
			return insert(v).first;
	}
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::insert(iterator first,
                                                      iterator last) {
    while (first != last) insert(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::insert(const Value* first,
                                                      const Value* last) {
    while (first != last) insert(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::erase(iterator position) {
    link_type z = position.node;
    link_type y = z;
    link_type x;
    if (left(y) == NIL)
        x = right(y);
    else
        if (right(y) == NIL)
            x = left(y);
        else {
            y = right(y);
            while (left(y) != NIL)
                y = left(y);
            x = right(y);
        }
    if (y != z) { // relink y in place of z
        parent(left(z)) = y;
        left(y) = left(z);
        if (y != right(z)) {
            parent(x) = parent(y); // possibly x == NIL
            left(parent(y)) = x;   // y must be a left child
            right(y) = right(z);
            parent(right(z)) = y;
        } else
            parent(x) = y;  // needed in case x == NIL
        if (root() == z)
            root() = y;
        else if (left(parent(z)) == z)
            left(parent(z)) = y;
        else
            right(parent(z)) = y;
        parent(y) = parent(z);
        ::swap(color(y), color(z));
        y = z;
                       // y points to node to be actually deleted
    } else {  // y == z
        parent(x) = parent(y);   // possibly x == NIL
        if (root() == z)
            root() = x;
        else
            if (left(parent(z)) == z)
                left(parent(z)) = x;
            else
                right(parent(z)) = x;
        if (leftmost() == z)
            if (right(z) == NIL)  // left(z) must be NIL also
                leftmost() = parent(z);
                // makes leftmost() == header if z == root()
        else
            leftmost() = minimum(x);
        if (rightmost() == z)
            if (left(z) == NIL) // right(z) must be NIL also
                rightmost() = parent(z);
                // makes rightmost() == header if z == root()
        else  // x == left(z)
            rightmost() = maximum(x);
    }
    if (color(y) != red) {
        while (x != root() && color(x) == black)
            if (x == left(parent(x))) {
                link_type w = right(parent(x));
                if (color(w) == red) {
                    color(w) = black;
                    color(parent(x)) = red;
                    rotate_left(parent(x));
                    w = right(parent(x));
                }
                if (color(left(w)) == black && color(right(w)) == black) {
                    color(w) = red;
                    x = parent(x);
                } else {
                    if (color(right(w)) == black) {
                        color(left(w)) = black;
                        color(w) = red;
                        rotate_right(w);
                        w = right(parent(x));
                    }
                    color(w) = color(parent(x));
                    color(parent(x)) = black;
                    color(right(w)) = black;
                    rotate_left(parent(x));
                    break;
                }
            } else {  // same as then clause with "right" and "left" exchanged
                link_type w = left(parent(x));
                if (color(w) == red) {
                    color(w) = black;
                    color(parent(x)) = red;
                    rotate_right(parent(x));
                    w = left(parent(x));
                }
                if (color(right(w)) == black && color(left(w)) == black) {
                    color(w) = red;
                    x = parent(x);
                } else {
                    if (color(left(w)) == black) {
                        color(right(w)) = black;
                        color(w) = red;
                        rotate_left(w);
                        w = left(parent(x));
                    }
                    color(w) = color(parent(x));
                    color(parent(x)) = black;
                    color(left(w)) = black;
                    rotate_right(parent(x));
                    break;
                }
            }
        color(x) = black;
    }
    destroy(value_allocator.address(value(y)));
    put_node(y);
    --node_count;
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::erase(iterator first,
                                                     iterator last) {
    if (first == begin() && last == end() && node_count != 0) {
        __erase(root());
        leftmost() = header;
        root() = NIL;
        rightmost() = header;
        node_count = 0;
    } else
        while (first != last) erase(first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::erase(const Key* first,
                                                     const Key* last) {
    while (first != last) erase(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::find(const Key& k) {
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root(); /* Current node. */

   while (x != NIL)
     if (!key_compare(key(x), k))
       y = x, x = left(x);
   else
       x = right(x);

   iterator j = iterator(y);
   return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::const_iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::find(const Key& k) const {
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root(); /* Current node. */

   while (x != NIL) {
     if (!key_compare(key(x), k))
       y = x, x = left(x);
   else
       x = right(x);
   }
   const_iterator j = const_iterator(y);
   return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::lower_bound(const Key& k) {
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root(); /* Current node. */

   while (x != NIL)
     if (!key_compare(key(x), k))
       y = x, x = left(x);
     else
       x = right(x);

   return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::const_iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::lower_bound(const Key& k) const {
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root(); /* Current node. */

   while (x != NIL)
     if (!key_compare(key(x), k))
       y = x, x = left(x);
     else
       x = right(x);

   return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::upper_bound(const Key& k) {
  link_type y = header; /* Last node which is greater than k. */
  link_type x = root(); /* Current node. */

   while (x != NIL)
     if (key_compare(k, key(x)))
       y = x, x = left(x);
     else
       x = right(x);

   return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::const_iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::upper_bound(const Key& k) const {
  link_type y = header; /* Last node which is greater than k. */
  link_type x = root(); /* Current node. */

   while (x != NIL)
     if (key_compare(k, key(x)))
       y = x, x = left(x);
     else
       x = right(x);

   return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::pair_iterator_iterator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::equal_range(const Key& k) {
    return pair_iterator_iterator(lower_bound(k), upper_bound(k));
}

template <class Key, class Value, class KeyOfValue, class Compare, class _Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::pair_citerator_citerator
rb_tree<Key, Value, KeyOfValue, Compare, _Alloc>::equal_range(const Key& k) const {
    return pair_citerator_citerator(lower_bound(k), upper_bound(k));
}

#endif
