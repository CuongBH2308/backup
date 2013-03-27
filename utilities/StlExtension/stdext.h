// My std extensions

namespace lz
{

// copy elements to a new sequence only fulfill certain criteria
template<class In, class Out, class Pred>
Out copy_if(In first, In last, Out res, Pred p)
{
	while(first != last)
	{
		if(p(*first)) *res++ = *first;
		first++;
	}
	return res;
} 


// transform 2 sequence witout output to another sequence.
template <class In, class In2, class BinOp>
BinOp for_each(In first, In last, In2 first2, BinOp op)
{
	while(first != last) op(*first++, *first2++);
	return op;
}

// replace sub strings in a string - it seems both basic_string class and don't support 
template <class _Char>
size_t replace_string(basic_string<_Char>& str,  const _Char* orig, const _Char* replace)
{
	size_t replaced = 0;
	size_t pos = 0;
	size_t len = char_traits<_Char>::length(orig);

	size_t occur = str.find(orig, pos);
	while (occur != basic_string<_Char>::npos)
	{
		str.replace(occur, len, replace);

		replaced++;

		pos = pos + occur + len;
		occur = str.find(orig, pos);
	}

	return replaced;
}

}