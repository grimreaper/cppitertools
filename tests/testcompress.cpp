#include <compress.hpp>

#include <vector>
#include <iostream>

using iter::compress;

template <typename DataType, typename SelectorType>
void testcase(std::vector<DataType> data_vec,
        std::vector<SelectorType> sel_vec)
{

    for (auto e : compress(data_vec, sel_vec)) {
        std::cout << e << '\n';
    }
}

int main(void)
{
    std::vector<int> ivec{1, 2, 3, 4, 5, 6};
    std::vector<bool> bvec{true, false, true, false, true, false};
    std::cout << "Should print 1 3 5\n";
    testcase(ivec, bvec);

    std::vector<bool> bvec2{false, true, false, false, false, true};
    std::cout << "Should print 2 6\n";
    testcase(ivec, bvec2);

    std::vector<bool> bvec3{false, true};
    std::cout << "Should print 2\n";
    testcase(ivec, bvec3);


    return 0;
}
