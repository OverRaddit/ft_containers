#ifndef RBTREE
#define RBTREE

#include <memory>

template <class _Tp, class _NodePtr, class _DiffType>
class _LIBCPP_TEMPLATE_VIS __rbtree_iterator;
template <class _Tp, class _ConstNodePtr, class _DiffType>
class _LIBCPP_TEMPLATE_VIS __rbtree_const_iterator;

template <class _Tp, class _Compare, class _Allocator>
class __rbtree;
//========================================================================================
//            _                  _ _   _
//      /\   | |                (_) | | |
//     /  \  | | __ _  ___  _ __ _| |_| |__  _ __ ___
//    / /\ \ | |/ _` |/ _ \| '__| | __| '_ \| '_ ` _ \
//   / ____ \| | (_| | (_) | |  | | |_| | | | | | | | |
//  /_/    \_\_|\__, |\___/|_|  |_|\__|_| |_|_| |_| |_|
//               __/ |
//              |___/
//========================================================================================

// __x가 부모의 왼쪽자식인지 여부를 반환한다.
template <class _NodePtr>
bool __tree_is_left_child(_NodePtr __x)
{
	return __x == __x->__parent_->__left_; // 왜 부모를 호출할때 parent_unsafe()를 사용하지 않았지?
}

// __x를 루트로 하는 서브트리가 레드블랙트리를 만족하는 지 여부를 반환한다.
// 레드블랙트리라면, black height를 반환한다. null은 1로 친다.
template <class _NodePtr>
unsigned __tree_sub_invariant(_NodePtr __x)
{
	if (__x == NULL)
		return 1;

	// 왜 굳이 해줘야 하는지 모르겠음. 이건 자료구조상에서 해결해야할 문제인데 rbtree의 개념과는 동떨어진 내용으로 보임...
	///===============================================================================
	// 부모자식이 일관적으로 연결되어 있는 지 확인한다.
	if (__x->__left_ != NULL && __x->__left_->__parent_ != __x)
		return 0;
	if (__x->__right_ != NULL && __x->__right_->__parent_ != __x)
		return 0;
	// 왼쪽자식과 오른쪽 자식이 같아선 안됨(널인 경우제외)
	if (__x->__left_ == __x->__right_ && __x->__left_ != NULL)
		return 0;
	//================================================================================

	// Double-Red검사(4번 규칙검증)
	if (!__x->__is_black_)
	{
		if (__x->__left_ && !__x->__left_->__is_black_)
			return 0;
		if (__x->__right_ && !__x->__right_->__is_black_)
			return 0;
	}
	unsigned __bh = __tree_sub_invariant(__x->__left_);
	if (__bh == 0)
		return 0;
	else
		(__bh != __tree_sub_invariant(__x->__right_)) return 0;
	return __bh + __x->__is_black_;
}

// 레드블랙트리의 루트노드인 __root가 레드블랙트리 인지 검사한다.
// 왜 root의 부모에 end_node가 있고 end_node의 왼쪽자식에 root를 가지도록 정의했는지 의도를 모르겠다.
template <class _NodePtr>
bool __tree_invariant(_NodePtr __root)
{
	if (__root == NULL)
		return true;
	if (__root->__parent_ == NULL)
		return false;
	if (!__tree_is_left_child(__root))
		return false;
	if (!__root->__is_black_)
		return false;
	return __tree_sub_invariant(__root) != 0;
}

// 여기부터 inline _LIBCPP_INLINE_VISIBILITY, _NOEXCEPT가 사용된다. 왜?

// ㅅㅓ브트리의 최좌측노드 반환, 이걸 어디에쓰지?
template <class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
	_NodePtr
	__tree_min(_NodePtr __x) _NOEXCEPT
{
	while (__x->__left_ != nullptr)
		__x = __x->__left_;
	return __x;
}

// ㅅㅓ브트리의 최우측노드 반환, 이걸 어디에쓰지?
template <class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
	_NodePtr
	__tree_max(_NodePtr __x) _NOEXCEPT
{
	while (__x->__right_ != nullptr)
		__x = __x->__right_;
	return __x;
}

// 트리에서 다음 값을 가진 노드 찾아서 반환
// 최우측노드의 다음값이 end_node로 정의된 것이 인상적이다.
template <class _NodePtr>
_NodePtr __tree_next(_NodePtr __x) _NOEXCEPT
{
	if (__x->__right_ != nullptr)
		return __tree_min(__x->__right_);
	while (!__tree_is_left_child(__x)) // 트리 그림에서 오른쪽 위에 해당하는 부모를 찾을때까지 올라간다.
		__x = __x->__parent_unsafe();
	return __x->__parent_unsafe();
}

// 왜 end_node로 반환하는지 모르겠다.
// iter는 모든 노드를 가리킬 수 있어야 하니 가장 부모클래스에 해당하는 _EndNodePtr로 하는게 아닐까
// 일반 node를 end_node로 static_cast하면 무슨일이 일어나지?
// 메모리상에서 변화를 알고싶다.
template <class _EndNodePtr, class _NodePtr>
inline _LIBCPP_INLINE_VISIBILITY
	_EndNodePtr
	__tree_next_iter(_NodePtr __x) _NOEXCEPT
{
	if (__x->__right_ != nullptr)
		return static_cast<_EndNodePtr>(__tree_min(__x->__right_)); // 왜 end_node로 형변환 하는거지?
	while (!__tree_is_left_child(__x))
		__x = __x->__parent_unsafe();
	return static_cast<_EndNodePtr>(__x->__parent_);
}

// 아니.... 얘는 왜 end_node를 인자로 받지??????
// 무조건 마지막노드만 end_node니까 이전노드를 찾을때는 end_node가 반환될 일이 없다는 전제로 작성한건가?
template <class _NodePtr, class _EndNodePtr>
inline _LIBCPP_INLINE_VISIBILITY
	_NodePtr
	__tree_prev_iter(_EndNodePtr __x) _NOEXCEPT
{
	if (__x->__left_ != nullptr)
		return __tree_max(__x->__left_);
	_NodePtr __xx = static_cast<_NodePtr>(__x);
	while (__tree_is_left_child(__xx))
		__xx = __xx->__parent_unsafe();
	return __xx->__parent_unsafe();
}

// 이 함수는 왜있는거지?? 의도를 모르겠다.
template <class _NodePtr>
_NodePtr __tree_leaf(_NodePtr __x) _NOEXCEPT
{
	while (true)
	{
		if (__x->__left_ != NULL)
		{
			__x = __x->__left_;
			continue;
		}
		if (__x->__right_ != NULL)
		{
			__x = __x->__right_;
			continue;
		}
		break;
	}
	return __x;
}

template <class _NodePtr>
void __tree_left_rotate(_NodePtr __x) _NOEXCEPT
{
	_NodePtr __y = __x->__right_;
	__x->__right_ = __y->__left_;
	if (__x->__right_ != nullptr)
		__x->__right_->__set_parent(__x);
	__y->__parent_ = __x->__parent_;
	if (__tree_is_left_child(__x))
		__x->__parent_->__left_ = __y;
	else
		__x->__parent_unsafe()->__right_ = __y;
	__y->__left_ = __x;
	__x->__set_parent(__y);
}

template <class _NodePtr>
void __tree_right_rotate(_NodePtr __x) _NOEXCEPT
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

// Effects:  Rebalances __root after attaching __x to a leaf.
// Precondition:  __root != nulptr && __x != nullptr.
//                __x has no children.
//                __x == __root or == a direct or indirect child of __root.
//                If __x were to be unlinked from __root (setting __root to
//                  nullptr if __root == __x), __tree_invariant(__root) == true.
// Postcondition: __tree_invariant(end_node->__left_) == true.  end_node->__left_
//                may be different than the value passed in as __root.
// __x가 __root와 분리된 경우 이해가 안됨..
// postcond 이해가 안됨..
template <class _NodePtr>
void __tree_balance_after_insert(_NodePtr __root, _NodePtr __x) _NOEXCEPT
{
	__x->__is_black_ = __x == __root;							  // 삽입되는 노드가 루트라면 검정으로 추가 그외 빨강으로 추가한다.
	while (__x != __root && !__x->__parent_unsafe()->__is_black_) // double red를 검사한다.
	{
		// 아래 주석 이해안됨
		// __x->__parent_ != __root because __x->__parent_->__is_black == false
		if (__tree_is_left_child(__x->__parent_unsafe())) // x의 부모가 좌측자식이라면
		{
			_NodePtr __y = __x->__parent_unsafe()->__parent_unsafe()->__right_; // y is uncle of x
			if (__y != nullptr && !__y->__is_black_)							// uncle is red -> Recoloring
			{
				__x = __x->__parent_unsafe();
				__x->__is_black_ = true; // 부모 검정
				__x = __x->__parent_unsafe();
				__x->__is_black_ = __x == __root; // 조상 색상결정
				__y->__is_black_ = true;		  // 삼촌 검정
			}
			else // uncle is black
			{
				if (!__tree_is_left_child(__x)) // x가 우측자식이라면 x부모를 좌회전해서 x가 좌측자식이 되도록 모양을 바꾼다.
				{
					__x = __x->__parent_unsafe();
					__tree_left_rotate(__x);
				}
				__x = __x->__parent_unsafe(); // 이 시점에서 x가 좌측자식 이거나 그것과 같은꼴인 모양이다.
				__x->__is_black_ = true;	  // 색을 반전시키는줄 알았는데,,,, 명확하게 색을 지정해준다?
				__x = __x->__parent_unsafe();
				__x->__is_black_ = false;
				__tree_right_rotate(__x);
				break;
			}
		}
		else // x의 부모가 우측자식이라면
		{
			_NodePtr __y = __x->__parent_unsafe()->__parent_->__left_;
			if (__y != nullptr && !__y->__is_black_)
			{
				__x = __x->__parent_unsafe();
				__x->__is_black_ = true;
				__x = __x->__parent_unsafe();
				__x->__is_black_ = __x == __root;
				__y->__is_black_ = true;
			}
			else
			{
				if (__tree_is_left_child(__x))
				{
					__x = __x->__parent_unsafe();
					__tree_right_rotate(__x);
				}
				__x = __x->__parent_unsafe();
				__x->__is_black_ = true;
				__x = __x->__parent_unsafe();
				__x->__is_black_ = false;
				__tree_left_rotate(__x);
				break;
			}
		}
	}
}

// Precondition:  __root != nullptr && __z != nullptr.
//                __tree_invariant(__root) == true.
//                __z == __root or == a direct or indirect child of __root.
// Effects:  unlinks __z from the tree rooted at __root, rebalancing as needed.
// Postcondition: __tree_invariant(end_node->__left_) == true && end_node->__left_
//                nor any of its children refer to __z.  end_node->__left_
//                may be different than the value passed in as __root.
// 시간없으니 바로 함수읽겠음.
// x,y,z,w가 각각 무슨역할인지 잘 모르겠다.
template <class _NodePtr>
void __tree_remove(_NodePtr __root, _NodePtr __z) _NOEXCEPT
{
	// __z는 tree에서 제거되지만 destruct, dealloc은 안해준다.
	// __y is either __z, or if __z has two children, __tree_next(__z).
	// __y will have at most one child.
	// __y will be the initial hole in the tree (make the hole at a leaf)
	// __y는 __z가 제거되면 대체될 노드이다.
	_NodePtr __y = (__z->__left_ == nullptr || __z->__right_ == nullptr) ? __z : __tree_next(__z);
	// __x is __y's possibly null single child
	_NodePtr __x = __y->__left_ != nullptr ? __y->__left_ : __y->__right_;
	// __w is __x's possibly null uncle (will become __x's sibling)
	_NodePtr __w = nullptr;
	// link __x to __y's parent, and find __w
	if (__x != nullptr)
		__x->__parent_ = __y->__parent_;
	if (__tree_is_left_child(__y))
	{
		__y->__parent_->__left_ = __x;
		if (__y != __root)
			__w = __y->__parent_unsafe()->__right_;
		else
			__root = __x; // __w == nullptr
	}
	else
	{
		__y->__parent_unsafe()->__right_ = __x;
		// __y can't be root if it is a right child
		__w = __y->__parent_->__left_;
	}
	// 아니 삭제하는건 __z인데 왜 __y의 색에따라 결정되는거야
	bool __removed_black = __y->__is_black_;
	// 만약 우리가 __z를 제거하지 않았다면,
	// 지금 __z에 대해 __y를 연결해서 제거하되, __z의 색상을 복사하십시오.
	// 이는 __x 또는 __w에 영향을 미치지 않습니다.
	// 이게 뭔소리냐;;
	if (__y != __z)
	{
		// __z->__left_ != nulptr but __z->__right_ might == __x == nullptr
		__y->__parent_ = __z->__parent_;
		if (__tree_is_left_child(__z))
			__y->__parent_->__left_ = __y;
		else
			__y->__parent_unsafe()->__right_ = __y;
		__y->__left_ = __z->__left_;
		__y->__left_->__set_parent(__y);
		__y->__right_ = __z->__right_;
		if (__y->__right_ != nullptr)
			__y->__right_->__set_parent(__y);
		__y->__is_black_ = __z->__is_black_;
		if (__root == __z)
			__root = __y;
	}
	// 삭제노드가 red이거나 삭제한 노드가 트리의 유일한 노드였다면 Rebalance를 할 필요가 없다.
	// 삭제된 노드가 검정이면서 트리가 null이 아닐때만 Rebalance한다.
	if (__removed_black && __root != nullptr)
	{
		// Rebalance:
		// y에서 제거되어 발생한 x는 검은색이다. 어떤경우에든 대체될 노드는 검은색이된다!
		// y가 제거할 노드, x가 대체될 노드로 추정됨.

		// Since __y was black and only had one child (which __x points to), __x
		//   is either red with no children, else null, otherwise __y would have
		//   different black heights under left and right pointers.
		// if (__x == __root || __x != nullptr && !__x->__is_black_)
		if (__x != nullptr)
			__x->__is_black_ = true;
		else
		{
			//  Else __x isn't root, and is "doubly black", even though it may
			//     be null.  __w can not be null here, else the parent would
			//     see a black height >= 2 on the __x side and a black height
			//     of 1 on the __w side (__w must be a non-null black or a red
			//     with a non-null black child).
			while (true)
			{
				if (!__tree_is_left_child(__w)) // if x is left child
				{
					if (!__w->__is_black_)
					{
						__w->__is_black_ = true;
						__w->__parent_unsafe()->__is_black_ = false;
						__tree_left_rotate(__w->__parent_unsafe());
						// __x is still valid
						// reset __root only if necessary
						if (__root == __w->__left_)
							__root = __w;
						// reset sibling, and it still can't be null
						__w = __w->__left_->__right_;
					}
					// __w->__is_black_ is now true, __w may have null children
					if ((__w->__left_ == nullptr || __w->__left_->__is_black_) &&
						(__w->__right_ == nullptr || __w->__right_->__is_black_))
					{
						__w->__is_black_ = false;
						__x = __w->__parent_unsafe();
						// __x can no longer be null
						if (__x == __root || !__x->__is_black_)
						{
							__x->__is_black_ = true;
							break;
						}
						// reset sibling, and it still can't be null
						__w = __tree_is_left_child(__x) ? __x->__parent_unsafe()->__right_ : __x->__parent_->__left_;
						// continue;
					}
					else // __w has a red child
					{
						if (__w->__right_ == nullptr || __w->__right_->__is_black_)
						{
							// __w left child is non-null and red
							__w->__left_->__is_black_ = true;
							__w->__is_black_ = false;
							__tree_right_rotate(__w);
							// __w is known not to be root, so root hasn't changed
							// reset sibling, and it still can't be null
							__w = __w->__parent_unsafe();
						}
						// __w has a right red child, left child may be null
						__w->__is_black_ = __w->__parent_unsafe()->__is_black_;
						__w->__parent_unsafe()->__is_black_ = true;
						__w->__right_->__is_black_ = true;
						__tree_left_rotate(__w->__parent_unsafe());
						break;
					}
				}
				else
				{
					if (!__w->__is_black_)
					{
						__w->__is_black_ = true;
						__w->__parent_unsafe()->__is_black_ = false;
						__tree_right_rotate(__w->__parent_unsafe());
						// __x is still valid
						// reset __root only if necessary
						if (__root == __w->__right_)
							__root = __w;
						// reset sibling, and it still can't be null
						__w = __w->__right_->__left_;
					}
					// __w->__is_black_ is now true, __w may have null children
					if ((__w->__left_ == nullptr || __w->__left_->__is_black_) &&
						(__w->__right_ == nullptr || __w->__right_->__is_black_))
					{
						__w->__is_black_ = false;
						__x = __w->__parent_unsafe();
						// __x can no longer be null
						if (!__x->__is_black_ || __x == __root)
						{
							__x->__is_black_ = true;
							break;
						}
						// reset sibling, and it still can't be null
						__w = __tree_is_left_child(__x) ? __x->__parent_unsafe()->__right_ : __x->__parent_->__left_;
						// continue;
					}
					else // __w has a red child
					{
						if (__w->__left_ == nullptr || __w->__left_->__is_black_)
						{
							// __w right child is non-null and red
							__w->__right_->__is_black_ = true;
							__w->__is_black_ = false;
							__tree_left_rotate(__w);
							// __w is known not to be root, so root hasn't changed
							// reset sibling, and it still can't be null
							__w = __w->__parent_unsafe();
						}
						// __w has a left red child, right child may be null
						__w->__is_black_ = __w->__parent_unsafe()->__is_black_;
						__w->__parent_unsafe()->__is_black_ = true;
						__w->__left_->__is_black_ = true;
						__tree_right_rotate(__w->__parent_unsafe());
						break;
					}
				}
			}
		}
	}
}

//========================================================================================

// NODE TRAITS============================================================================

template <class _Tp>
struct __tree_key_value_types
{
	typedef _Tp key_type;
	typedef _Tp __node_value_type;
	typedef _Tp __container_value_type;
	static const bool __is_map = false;

	_LIBCPP_INLINE_VISIBILITY
	static key_type const &__get_key(_Tp const &__v)
	{
		return __v;
	}
	_LIBCPP_INLINE_VISIBILITY
	static __container_value_type const &__get_value(__node_value_type const &__v)
	{
		return __v;
	}
	_LIBCPP_INLINE_VISIBILITY
	static __container_value_type *__get_ptr(__node_value_type &__n)
	{
		return _VSTD::addressof(__n);
	}
};

template <class _VoidPtr>
struct __tree_node_base_types
{
	typedef _VoidPtr __void_pointer;

	typedef __tree_node_base<__void_pointer> __node_base_type;
	typedef typename __rebind_pointer<_VoidPtr, __node_base_type>::type
		__node_base_pointer;

	typedef __tree_end_node<__node_base_pointer> __end_node_type;
	typedef typename __rebind_pointer<_VoidPtr, __end_node_type>::type
		__end_node_pointer;
#if defined(_LIBCPP_ABI_TREE_REMOVE_NODE_POINTER_UB)
	typedef __end_node_pointer __parent_pointer;
#else
	typedef typename conditional<
		is_pointer<__end_node_pointer>::value,
		__end_node_pointer,
		__node_base_pointer>::type __parent_pointer;
#endif

private:
	static_assert((is_same<typename pointer_traits<_VoidPtr>::element_type, void>::value),
				  "_VoidPtr does not point to unqualified void type");
};

//========================================================================================

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
struct __tree_node : public __tree_node_base<_VoidPtr>
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
	__tree_node_destructor &operator=(const __tree_node_destructor &);

public:
	bool __value_constructed; // 메모리초기화 여부

	__tree_node_destructor(const __tree_node_destructor &);
	__tree_node_destructor(allocator_type &__na, bool __val = false)
		: __na_(__na), __value_constructed(__val) {}

	void operator()(pointer __p)
	{
		if (__value_constructed)
			__alloc_traits::destroy(__na_, _NodeTypes::__get_ptr(__p->__value_));
		if (__p)
			__alloc_traits::deallocate(__na_, __p, 1);
	}

	template <class>
	friend class __map_node_destructor; // 얘를 왜 해줘야 하는지 모르겠다.
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

#endif