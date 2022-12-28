#ifndef RBTREE
#define RBTREE

#include <memory>

namespace ft
{

	template <class _Tp, class _NodePtr, class _DiffType>
	class _LIBCPP_TEMPLATE_VIS __rbtree_iterator;
	template <class _Tp, class _ConstNodePtr, class _DiffType>
	class _LIBCPP_TEMPLATE_VIS __rbtree_const_iterator;

	template <class _Tp, class _Compare, class _Allocator>
	class __rbtree;

	// =============================================================================
	//  ▄▄        ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄
	// ▐░░▌      ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌
	// ▐░▌░▌     ▐░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀
	// ▐░▌▐░▌    ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌▐░▌
	// ▐░▌ ▐░▌   ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄▄▄
	// ▐░▌  ▐░▌  ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌
	// ▐░▌   ▐░▌ ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌▐░█▀▀▀▀▀▀▀▀▀
	// ▐░▌    ▐░▌▐░▌▐░▌       ▐░▌▐░▌       ▐░▌▐░▌
	// ▐░▌     ▐░▐░▌▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄▄▄
	// ▐░▌      ▐░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌
	//  ▀        ▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀

	template <class _Pointer>
	struct __tree_end_node
	{
		typedef _Pointer pointer;
		pointer __left_;

		__tree_end_node() : __left_() {}
	};

	template <class _VoidPtr>
	struct __tree_node_base : public __tree_end_node // 수정필요! public __tree_node_base_types<_VoidPtr>::__end_node_type
	{
		typedef __tree_node_base_types<_VoidPtr> _NodeBaseTypes;
		typedef typename _NodeBaseTypes::__node_base_pointer pointer;
		typedef typename _NodeBaseTypes::__parent_pointer __parent_pointer;

		pointer __right_;
		__parent_pointer __parent_;
		bool __is_black;

		pointer __parent_unsafe() const { return static_cast<pointer>(__parent_); }
		void __set_parent(pointer __p) { __parent_ = static_cast < __parent_pointer(__p); }

	private: // 복사,소멸,대입등의 연산은 호출금지! -> 그러면 복사/소멸/대입시킬때 어떻게 해야하지?
		~__tree_node_base();
		__tree_node_base(__tree_node_base const &);
		__tree_node_base &operator=(__tree_node_base const &);
	};

	template <class _Tp, class _VoidPtr>
	struct __tree_node : public __tree_node_base<_VoidPrt>
	{
		typedef _Tp __node_value_type;

		__node_value_type __value;

	private:
		~__tree_node();
		__tree_node(__tree_node const &);
		__tree_node &operator=(__tree_node const &);
	};

	template <class _Allocator>
	class __tree_node_destructor
	{
		typedef _Allocator allocator_type;
		typedef allocator_traits<allocator_type> __alloc_traits;

	public:
		typedef typename __alloc_traits::pointer pointer;

	private:
		typedef __tree_node_types<pointer> _NodeTypes;
		allocator_type &__na_; // na가 무슨뜻? node allocator?

	public:
		bool __value_constructed; // ???

		// ??????????????????????????????????????????????????????????????????
		// __tree_node_destructor(const __tree_node_destructor &) = default;
		// __tree_node_destructor &operator=(const __tree_node_destructor &) = delete;

		// explicit __tree_node_destructor(allocator_type &__na, bool __val = false)
		// 	: __na_(__na), __value_constructed(__val) {}

		// void operator()(pointer __p)
		// {
		// 	if (__value_constructed)
		// 		__alloc_traits::destroy(__na_, _NodeTypes::__get_ptr(__p->__value_));
		// 	if (__p)
		// 		__alloc_traits::deallocate(__na_, __p, 1);
		// }

		// template <class>
		// friend class __map_node_destructor;
		// ??????????????????????????????????????????????????????????????????
	};

	// 줄맞춤하고싶은데 저장하면 자동완성기능처럼 줄맞춤이 사라진다....;;;;
	template <class _Tp, class _NodePtr, class _DiffType>
	class __tree_iterator
	{
		typedef __tree_node_types<_NodePtr> _NodeTypes;
		typedef _NodePtr __node_pointer;
		typedef typename _NodeTypes::__node_base_pointer __node_base_pointer;
		typedef typename _NodeTypes::__end_node_pointer __end_node_pointer;
		typedef typename _NodeTypes::__iter_pointer __iter_pointer;
		typedef pointer_traits<__node_pointer> __pointer_traits;

		__iter_pointer __ptr;

	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef _DiffType difference_type;
		typedef value_type &reference;
		typedef typename _NodeTypes::__node_value_type_pointer pointer;
	};

	// =============================================================================

	template <class _Tp, class _Compare, class _Allocator>
	class __rbtree
	{
	private:
		/* data */
	public:
		typedef _Allocator allocator_type;
		typedef _Tp value_type;
		typedef typename allocator_type::pointer pointer;

	protected:
		//==============================================================================
		template <class T, class Alloc = std::allocator<T>>
		struct tree_node
		{
			typedef _Allocator allocator_type;
			typedef _Tp value_type;
			typedef typename allocator_type::pointer pointer;

			pointer _left;
			pointer _right;
			pointer _parent;
			bool _is_red; // true red, false black
			value_type data;
		}
		// construct
		tree_node() : _left(0), _right(0), _parent(0), _is_red(0), data(0), _alloc(allocator_type()){};
		tree_node(const tree_node &a)
			: _left(a._left), _right(a._right), _parent(a._parent), _is_red(0), data(a.data), _alloc(a._alloc){};
		tree_node(value_type a) : _left(0), _right(0), _parent(0), _is_red(0), data(a), _alloc(allocator_type()){};
		//==============================================================================
		// member variable : 자기자신과 왼쪽자식, 오른쪽자식을 멤버로 가진다.
		allocator_type _alloc;
		tree_node _root;

	public:
		rbtree()
			: _root(0), _left(0), _right(0), _parent(0), _alloc(allocator_type()){};

		rbtree(const key_compare &comp = key_compare(),
			   const allocator_type &alloc = allocator_type())
			: __tree(comp, alloc){};

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

		void insert(tree_node a) // 레드블랙트리에 a노드를 추가한다.
		{
			tree_node current = _root;

			a._is_red = true; // new node is always red.

			// insert node in right place
			while (1)
			{
				if (current < a)
				{
					if (current._left == 0)
					{
						current._left = a;
						return;
					}
					current = current._left;
				}
				else
				{
					if (current._right == 0)
					{
						current._right = a;
						return;
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

		void restructuring(tree_node &n, tree_node &p, tree_node &g, tree_node &u){
			// n p g를 오름차순으로 정렬한다.
			// p n g or p g n
			// low mid high로 명명한다.

			// mid를 부모노드로. low high를 왼쪽자식 오른쪽 자식으로 수정.

			// 색깔변경
		};

		void erase(tree_node a); // 레드블랙트리에 a노드를 제거한다.
		size_t bh(tree_node a);	 // a에서 nil까지의 높이를 구한다. 본인노드는 높이에서 제외.

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
				return 0; // invalid left subtree
			if (__h != __tree_sub_invariant(__x->__right_))
				return 0;				   // invalid or different height right subtree
			return __h + __x->__is_black_; // return black height of this node
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

		void __tree_left_rotate(tree_node *_x)
		{
			tree_node *_y = _x->_right;

			_x->right = _y->_left;
			if (_y->left != NULL)
				_y->_left->_parent = _x;
			_y->_parent = _x->_parent;
			if (__tree_is_left_child(_x))
				_x->_parent->_left = _y;
			else
				_x->_parent->_right = _y;
			_y->_left = _x;
			_x->_parent = _y;
		}

		void __tree_right_rotate(tree_node *_x)
		{
			tree_node *_y = _x->_left;

			_x->left = _y->_right;
			if (_y->right != NULL)
				_y->_right->_parent = _x;
			_y->_parent = _x->_parent;
			if (__tree_is_left_child(_x))
				_x->_parent->_left = _y;
			else
				_x->_parent->_right = _y;
			_y->_right = _x;
			_x->_parent = _y;
		}

		void __tree_insert(tree_node *_root, tree_node *_x)
		{
			_x->_is_red = (_x != _root);
		}

		// Find place to insert if __v doesn't exist
		// Set __parent to parent of null leaf
		// Return reference to null leaf
		// If __v exists, set parent to node of __v and return reference to node of __v
		template <class _Tp, class _Compare, class _Allocator>
		template <class _Key>
		typename __tree<_Tp, _Compare, _Allocator>::__node_base_pointer &
		__tree<_Tp, _Compare, _Allocator>::__find_equal(__parent_pointer &__parent,
														const _Key &__v)
		{
			__node_pointer __nd = __root();
			__node_base_pointer *__nd_ptr = __root_ptr();
			if (__nd != nullptr)
			{
				while (true)
				{
					if (value_comp()(__v, __nd->__value_))
					{
						if (__nd->__left_ != nullptr)
						{
							__nd_ptr = _VSTD::addressof(__nd->__left_);
							__nd = static_cast<__node_pointer>(__nd->__left_);
						}
						else
						{
							__parent = static_cast<__parent_pointer>(__nd);
							return __parent->__left_;
						}
					}
					else if (value_comp()(__nd->__value_, __v))
					{
						if (__nd->__right_ != nullptr)
						{
							__nd_ptr = _VSTD::addressof(__nd->__right_);
							__nd = static_cast<__node_pointer>(__nd->__right_);
						}
						else
						{
							__parent = static_cast<__parent_pointer>(__nd);
							return __nd->__right_;
						}
					}
					else
					{
						__parent = static_cast<__parent_pointer>(__nd);
						return *__nd_ptr;
					}
				}
			}
			__parent = static_cast<__parent_pointer>(__end_node());
			return __parent->__left_;
		}
	};

}

#endif