#ifndef FT_ITERATOR_CATEGORY
#define FT_ITERATOR_CATEGORY

namespace ft
{


struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

}
#endif
