#ifndef FT_REVERSE_ITERATOR
#define FT_REVERSE_ITERATOR

template <class Iterator>
class reverse_iterator
{
public:
// ================================================================================
// Member Types
// ================================================================================
typedef typename Iterator										iterator_type;
typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
typedef typename iterator_traits<Iterator>::value_type			value_type;
typedef typename iterator_traits<Iterator>::difference_type		difference_type;
typedef typename iterator_traits<Iterator>::pointer				pointer;
typedef typename iterator_traits<Iterator>::reference			reference;

// ================================================================================
// Member Functions
// ================================================================================

//constructors
reverse_iterator();

explicit reverse_iterator (iterator_type it);

template <class Iter>
reverse_iterator(const reverse_iterator<Iter>& rev_it)
{

}

reference operator*() const;
reverse_iterator operator+(difference_type n) const;
reverse_iterator& operator++();
reverse_iterator operator++(int);
reverse_iterator& operator+=(difference_type n);
reverse_iterator operator-(difference_type n) const;
reverse_iterator& operator--();
reverse_iterator operator--(int);
reverse_iterator& operator-=(difference_type n);
pointer operator->() const; // {return &(operator*())}
reference operator[](difference_type n) const;

};

// ================================================================================
// Non-member function overloads
// ================================================================================
// 관계연산
template <class Iterator>  bool operator== (const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>  bool operator!= (const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>  bool operator< (const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>  bool operator<= (const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>  bool operator>= (const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);
template <class Iterator>  bool operator>= (const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs);

// r_iter + 1은 멤버함수로 가능 but 1 + r_iter는 불가능
template<class Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
	const reverse_iterator<Iter>& rev_it);
// 두 iter의 거리 계산
template<class Iter>
typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>&lhs,
	const reverse_iterator<Iter>& rhs);

#endif
