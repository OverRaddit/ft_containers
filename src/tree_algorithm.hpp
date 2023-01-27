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

#ifndef __TREE_ALGORITHM
#define __TREE_ALGORITHM

# include "utility.hpp"
# include <type_traits>

namespace ft
{

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
		return ft::__tree_min(__x->_right);
	while (!ft::__tree_is_left_child(__x))
		__x = __x->_parent;
	return __x->_parent;
}

template <class _NodePtr>
inline _NodePtr __tree_prev_iter(_NodePtr __x) throw()
{
	if (__x->_left != nullptr)
		return ft::__tree_max(__x->_left);
	_NodePtr __xx = __x;
	while (ft::__tree_is_left_child(__xx))
		__xx = __xx->_parent;
	return __xx->_parent;
}

template <class _NodePtr>
_NodePtr __tree_next(_NodePtr __x) throw()
{
	if (__x->_right != nullptr)
		return ft::__tree_min(__x->_right);
	while (!ft::__tree_is_left_child(__x))
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
	if (ft::__tree_is_left_child(__x))
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
	if (ft::__tree_is_left_child(__x))
		__x->_parent->_left = __y;
	else
		__x->_parent->_right = __y;
	__y->_right = __x;
	__x->_parent = __y;
}

template <class _NodePtr>
void
__tree_balance_after_insert(_NodePtr __root, _NodePtr __x) throw()
{
	__x->_is_black = (int)(__x == __root);
	while (__x != __root && !__x->_parent->_is_black)
	{
		// __x->_parent != __root because __x->_parent->__is_black == false
		if (ft::__tree_is_left_child(__x->_parent))
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
				if (!ft::__tree_is_left_child(__x))
				{
					__x = __x->_parent;
					ft::__tree_left_rotate(__x);
				}
				__x = __x->_parent;
				__x->_is_black = true;
				__x = __x->_parent;
				__x->_is_black = false;
				ft::__tree_right_rotate(__x);
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
				if (ft::__tree_is_left_child(__x))
				{
					__x = __x->_parent;
					ft::__tree_right_rotate(__x);
				}
				__x = __x->_parent;
				__x->_is_black = true;
				__x = __x->_parent;
				__x->_is_black = false;
				ft::__tree_left_rotate(__x);
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
template <class _NodePtr>
void
__tree_remove(_NodePtr __root, _NodePtr __z) _NOEXCEPT
{
    // __z will be removed from the tree.  Client still needs to destruct/deallocate it
    // __y is either __z, or if __z has two children, __tree_next(__z).
    // __y will have at most one child.
    // __y will be the initial hole in the tree (make the hole at a leaf)
    _NodePtr __y = (__z->_left == nullptr || __z->_right == nullptr) ?
                    __z : ft::__tree_next(__z);
    // __x is __y's possibly null single child
    _NodePtr __x = __y->_left != nullptr ? __y->_left : __y->_right;
    // __w is __x's possibly null uncle (will become __x's sibling)
    _NodePtr __w = nullptr;
    // link __x to __y's parent, and find __w
    if (__x != nullptr)
        __x->_parent = __y->_parent;
    if (ft::__tree_is_left_child(__y))
    {
        __y->_parent->_left = __x;
        if (__y != __root)
            __w = __y->_parent->_right;
        else
            __root = __x;  // __w == nullptr
    }
    else
    {
        __y->_parent->_right = __x;
        // __y can't be root if it is a right child
        __w = __y->_parent->_left;
    }
    bool __removed_black = __y->_is_black;
    // If we didn't remove __z, do so now by splicing in __y for __z,
    //    but copy __z's color.  This does not impact __x or __w.
    if (__y != __z)
    {
        // __z->_left != nulptr but __z->_right might == __x == nullptr
        __y->_parent = __z->_parent;
        if (ft::__tree_is_left_child(__z))
            __y->_parent->_left = __y;
        else
            __y->_parent->_right = __y;
        __y->_left = __z->_left;

        //__y->_left->ft::__set_parent(__y);
        __y->_left->_parent = __y;

        __y->_right = __z->_right;
        if (__y->_right != nullptr)
            //__y->_right->ft::__set_parent(__y);
            __y->_right->_parent = __y;
        __y->_is_black = __z->_is_black;
        if (__root == __z)
            __root = __y;
    }
    // There is no need to rebalance if we removed a red, or if we removed
    //     the last node.
    if (__removed_black && __root != nullptr)
    {
        // Rebalance:
        // __x has an implicit black color (transferred from the removed __y)
        //    associated with it, no matter what its color is.
        // If __x is __root (in which case it can't be null), it is supposed
        //    to be black anyway, and if it is doubly black, then the double
        //    can just be ignored.
        // If __x is red (in which case it can't be null), then it can absorb
        //    the implicit black just by setting its color to black.
        // Since __y was black and only had one child (which __x points to), __x
        //   is either red with no children, else null, otherwise __y would have
        //   different black heights under left and right pointers.
        // if (__x == __root || __x != nullptr && !__x->_is_black)
        if (__x != nullptr)
            __x->_is_black = true;
        else
        {
            //  Else __x isn't root, and is "doubly black", even though it may
            //     be null.  __w can not be null here, else the parent would
            //     see a black height >= 2 on the __x side and a black height
            //     of 1 on the __w side (__w must be a non-null black or a red
            //     with a non-null black child).
            while (true)
            {
                if (!ft::__tree_is_left_child(__w))  // if x is left child
                {
                    if (!__w->_is_black)
                    {
                        __w->_is_black = true;
                        __w->_parent->_is_black = false;
                        ft::__tree_left_rotate(__w->_parent);
                        // __x is still valid
                        // reset __root only if necessary
                        if (__root == __w->_left)
                            __root = __w;
                        // reset sibling, and it still can't be null
                        __w = __w->_left->_right;
                    }
                    // __w->_is_black is now true, __w may have null children
                    if ((__w->_left  == nullptr || __w->_left->_is_black) &&
                        (__w->_right == nullptr || __w->_right->_is_black))
                    {
                        __w->_is_black = false;
                        __x = __w->_parent;
                        // __x can no longer be null
                        if (__x == __root || !__x->_is_black)
                        {
                            __x->_is_black = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = ft::__tree_is_left_child(__x) ?
                                    __x->_parent->_right :
                                    __x->_parent->_left;
                        // continue;
                    }
                    else  // __w has a red child
                    {
                        if (__w->_right == nullptr || __w->_right->_is_black)
                        {
                            // __w left child is non-null and red
                            __w->_left->_is_black = true;
                            __w->_is_black = false;
                            ft::__tree_right_rotate(__w);
                            // __w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be null
                            __w = __w->_parent;
                        }
                        // __w has a right red child, left child may be null
                        __w->_is_black = __w->_parent->_is_black;
                        __w->_parent->_is_black = true;
                        __w->_right->_is_black = true;
                        ft::__tree_left_rotate(__w->_parent);
                        break;
                    }
                }
                else
                {
                    if (!__w->_is_black)
                    {
                        __w->_is_black = true;
                        __w->_parent->_is_black = false;
                        ft::__tree_right_rotate(__w->_parent);
                        // __x is still valid
                        // reset __root only if necessary
                        if (__root == __w->_right)
                            __root = __w;
                        // reset sibling, and it still can't be null
                        __w = __w->_right->_left;
                    }
                    // __w->_is_black is now true, __w may have null children
                    if ((__w->_left  == nullptr || __w->_left->_is_black) &&
                        (__w->_right == nullptr || __w->_right->_is_black))
                    {
                        __w->_is_black = false;
                        __x = __w->_parent;
                        // __x can no longer be null
                        if (!__x->_is_black || __x == __root)
                        {
                            __x->_is_black = true;
                            break;
                        }
                        // reset sibling, and it still can't be null
                        __w = ft::__tree_is_left_child(__x) ?
                                    __x->_parent->_right :
                                    __x->_parent->_left;
                        // continue;
                    }
                    else  // __w has a red child
                    {
                        if (__w->_left == nullptr || __w->_left->_is_black)
                        {
                            // __w right child is non-null and red
                            __w->_right->_is_black = true;
                            __w->_is_black = false;
                            ft::__tree_left_rotate(__w);
                            // __w is known not to be root, so root hasn't changed
                            // reset sibling, and it still can't be null
                            __w = __w->_parent;
                        }
                        // __w has a left red child, right child may be null
                        __w->_is_black = __w->_parent->_is_black;
                        __w->_parent->_is_black = true;
                        __w->_left->_is_black = true;
                        ft::__tree_right_rotate(__w->_parent);
                        break;
                    }
                }
            }
        }
    }
}

}

#endif
