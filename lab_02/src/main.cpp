#include <cstdio>

#include "iterator.hpp"
#include "matrix.hpp"
#include "matrix_implementation.hpp"

#define RED_COLOR "\u001b[31m"
#define GREEN_COLOR "\u001b[32m"
#define YELLOW_COLOR "\u001b[33m"
#define RESET_COLOR "\u001b[0m"

int main() {

    try {

        printf(YELLOW_COLOR "Testing constructors" RESET_COLOR "\n");

        Matrix<int> test1(3, 3);

        Matrix<int> test2(test1);

        Matrix<float> test3 = {{1.0f, 2.0f, 3.0f}, {0.1f, 0.2f, 0.3f}, {3.1415f, 2.718281f, 1.4142f}};

        std::cout << test1 << std::endl;
        std::cout << test2 << std::endl;
        std::cout << test3 << std::endl;

        printf(GREEN_COLOR "Done" RESET_COLOR "\n");

        printf(YELLOW_COLOR "Testing operators" RESET_COLOR "\n");

        Matrix<int> m1(3, 3);
        m1.identity_matrix();

        Matrix<int> m2(3, 3);
        m2.identity_matrix();

        Matrix<int> m_res = m1 + m2;

        printf("\nSum of identity matrices\n");
        std::cout << m_res;

        printf("\n += operator\n");
        m_res += 6;

        std::cout << m_res;

        m_res = m1 - m2;

        printf("\nSub of identity matrices\n");
        std::cout << m_res;

        printf("\n -= operator\n");
        m_res -= 6;

        std::cout << m_res;

        printf("\n Mul of matrices\n");

        Matrix<int> m5 = {{1, 2, 3}};
        Matrix<int> m6 = {{4}, {5}, {6}};

        auto m7 = m5 * m6;

        printf("\nResult:\n");

        std::cout << m7;

        auto m8 = m7 * 2;

        printf("\n Mul with const\n");

        std::cout << m8;

        printf("\n Division\n");

        auto m9 = test3 / 2;

        std::cout << m9;

        std::cout << "Getting val: " << m9.at(2, 2) << "\n";

        printf(GREEN_COLOR "Done" RESET_COLOR "\n");

        printf(YELLOW_COLOR "Testing Iterators" RESET_COLOR "\n");

        Iterator<float> iter = test3.begin();

        for (size_t i = 0; iter != test3.end(); i++, iter++) {
            std::cout << *iter << " ";
        }

        std::cout << std::endl;

        const Matrix<float> test4 = {{1.0f, 2.0f, 3.0f}, {0.1f, 0.2f, 0.3f}, {3.1415f, 2.718281f, 1.4142f}};

        auto const_iter = test4.begin();

        for (size_t i = 0; const_iter != test4.end(); i++, const_iter++) {
            std::cout << *const_iter << " ";
        }

        std::cout << std::endl;

        printf(GREEN_COLOR "Done" RESET_COLOR "\n");

    } catch (basicMatrixException& exception) {
        printf(RED_COLOR "Failed" RESET_COLOR "\n");
        std::cout << exception.what();
    }

    return 0;
}
