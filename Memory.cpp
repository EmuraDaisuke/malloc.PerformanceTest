


#include <cstdlib>



void* Alloc(std::size_t s)
{
	return std::malloc(s);
}



void Free(void* p)
{
	std::free(p);
}
