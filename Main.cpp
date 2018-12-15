


#include <thread>
#include <vector>
#include "./Lapse.h"



#define SIMPLE  1



void* Alloc(std::size_t s);
void Free(void* p);



constexpr long long bit(int v) noexcept
{
    return 1ll<<v;
}



void testAlloc(int nRepeat, int nTest, std::size_t s)
{
    std::vector<void*> ap(nTest);
    for (int n = nRepeat; n; --n){
        #if SIMPLE//[
        for (int n = nTest; n; --n) Free(Alloc(s));
        #else//][
        for (auto& p : ap) p = Alloc(s);
        for (auto& p : ap) Free(p);
        #endif//]
    }
}



void testThread(int nRepeat, int nTest, std::size_t s, int nThread)
{
    Lapse l;
    std::vector<std::thread> at(nThread);
    for (auto& t : at) t = std::thread(testAlloc, nRepeat, nTest, s);
    for (auto& t : at) t.join();
}



void test(int nRepeat, int nTest, std::size_t s)
{
    clog("===", s);
    testThread(nRepeat, nTest, s, 1);
    testThread(nRepeat, nTest, s, std::thread::hardware_concurrency());
}



int main(int argc, const char* argv[])
{
    test(100, 100, 0);
    for (int v = 0; v <= 24; ++v){
        test(100, 100, bit(v));
    }
    
    clog("*******");
    return 0;
}
