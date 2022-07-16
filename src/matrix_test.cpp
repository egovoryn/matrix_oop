#include "gtest/gtest.h"
#include "matrix_oop.h"

OMatrix fill_matrix_example() {
    OMatrix matrix(5, 5);
    matrix(0, 0) = 1.0;
    matrix(0, 1) = 2.0;
    matrix(0, 2) = 3.0;
    matrix(0, 3) = 4.0;
    matrix(0, 4) = 3.0;
    matrix(1, 0) = 0.0;
    matrix(1, 1) = 4.0;
    matrix(1, 2) = 2.0;
    matrix(1, 3) = 3.0;
    matrix(1, 4) = 2.0;
    matrix(2, 0) = 5.0;
    matrix(2, 1) = 2.0;
    matrix(2, 2) = 1.0;
    matrix(2, 3) = 3.0;
    matrix(2, 4) = 3.0;
    matrix(3, 0) = 5.0;
    matrix(3, 1) = 1.0;
    matrix(3, 2) = 1.0;
    matrix(3, 3) = 3.0;
    matrix(3, 4) = 3.0;
    matrix(4, 0) = 5.0;
    matrix(4, 1) = 2.0;
    matrix(4, 2) = 1.0;
    matrix(4, 3) = 8.0;
    matrix(4, 4) = 3.0;
    return matrix;
}

TEST(MatrixEqualTest, HandlesZeroMatrixInput) {
    try {
        OMatrix matrixOne(3, 3);
        OMatrix matrixTwo(3, 3);
        matrixOne.sum_matrix(matrixTwo);
        bool check = matrixOne.eq_matrix(matrixTwo);
        EXPECT_EQ(check, true);
    } catch (std::exception& ex) {
        std::cout << ex.what();
    }
}

TEST(MatrixConstructorTest, HandlesMatrixInput) {
    try {
        OMatrix matrixOne(3, 3);
        matrixOne = fill_matrix_example();
        OMatrix matrixTwo(matrixOne);
        bool check = matrixOne.eq_matrix(matrixTwo);
        EXPECT_EQ(check, true);
    } catch (std::exception& ex) {
        std::cout << ex.what();
    }
}

TEST(MatrixEqualTest, HandlesCorrectMatrixInput) {
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo = fill_matrix_example();
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixEqualTest, HandlesMatrixInput) {
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo(5, 5);
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, false);
}

TEST(MatrixSumTest, HandlesZeroMatrixInput) {
    OMatrix matrixOne;
    OMatrix matrixTwo(3, 3);
    matrixOne.sum_matrix(matrixTwo);
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixSumTest, HandlesMatrixInput) {
    OMatrix matrixTwo(5, 5);
    OMatrix matrixOne = fill_matrix_example();
    matrixTwo.sum_matrix(matrixOne);
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixSumTest, HandlesMatrixInputCorrect) {
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo = fill_matrix_example();
    matrixOne.sum_matrix(matrixTwo);
    matrixTwo *= 2;
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixSubTest, HandlesZeroMatrixInput) {
    OMatrix matrixOne;
    OMatrix matrixTwo(3, 3);
    matrixOne.sub_matrix(matrixTwo);
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixSubTest, HandlesMatrixInput) {
    OMatrix matrixZero(5, 5);
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo = fill_matrix_example();
    matrixOne.sub_matrix(matrixTwo);
    bool check = matrixOne.eq_matrix(matrixZero);
    EXPECT_EQ(check, true);
}

TEST(MatrixSubTest, HandlesMatrixInputCorrect) {
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo = fill_matrix_example();
    matrixOne *= 2;
    matrixOne.sub_matrix(matrixTwo);
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixMulTest, HandlesZeroMatrixInput) {
    OMatrix matrixOne;
    OMatrix matrixTwo(3, 3);
    matrixOne.mul_matrix(matrixTwo);
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixMulTest, HandlesDifferentMatrixInput) {
    OMatrix matrixOne(3, 3);
    matrixOne.fill_matrix();
    OMatrix matrixTwo(3, 1);
    matrixTwo(0, 0) = 1.0;
    matrixTwo(1, 0) = 2.0;
    matrixTwo(2, 0) = 3.0;
    matrixOne.mul_matrix(matrixTwo);
    OMatrix matrixResult(3, 1);
    matrixResult(0, 0) = 8.0;
    matrixResult(1, 0) = 14.0;
    matrixResult(2, 0) = 20.0;
    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(MatrixMulTest, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixTwo(3, 3);
    OMatrix matrixThree(3, 3);
    matrixOne.fill_matrix();
    matrixTwo.fill_matrix();
    matrixOne.mul_matrix(matrixTwo);
    matrixThree(0, 0) = 5.0;
    matrixThree(0, 1) = 8.0;
    matrixThree(0, 2) = 11.0;
    matrixThree(1, 0) = 8.0;
    matrixThree(1, 1) = 14.0;
    matrixThree(1, 2) = 20.0;
    matrixThree(2, 0) = 11.0;
    matrixThree(2, 1) = 20.0;
    matrixThree(2, 2) = 29.0;
    bool check = matrixOne.eq_matrix(matrixThree);
    EXPECT_EQ(check, true);
}

TEST(MatrixTransposeTest, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixTwo(3, 3);
    matrixOne.fill_matrix();
    matrixTwo.fill_matrix();
    matrixOne.transpose();
    bool check = matrixOne.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixCalcComplecsTest, HandlesMatrixInput) {
    try {
        OMatrix matrixOne(3, 3);
        OMatrix matrixTwo(3, 3);
        matrixOne(0, 0) = 1.0;
        matrixOne(0, 1) = 2.0;
        matrixOne(0, 2) = 3.0;
        matrixOne(1, 0) = 0.0;
        matrixOne(1, 1) = 4.0;
        matrixOne(1, 2) = 2.0;
        matrixOne(2, 0) = 5.0;
        matrixOne(2, 1) = 2.0;
        matrixOne(2, 2) = 1.0;

        matrixTwo(0, 0) = 0.0;
        matrixTwo(0, 1) = 10.0;
        matrixTwo(0, 2) = -20.0;
        matrixTwo(1, 0) = 4.0;
        matrixTwo(1, 1) = -14.0;
        matrixTwo(1, 2) = 8.0;
        matrixTwo(2, 0) = -8.0;
        matrixTwo(2, 1) = -2.0;
        matrixTwo(2, 2) = 4.0;

        OMatrix matrixResult = matrixOne.calc_complements();
        bool check = matrixResult.eq_matrix(matrixTwo);
        EXPECT_EQ(check, true);
    } catch (std::exception& ex) {
        std::cout << ex.what();
    }
}

TEST(MatrixDetermanantTest, HandlesMatrixInput) {
    OMatrix matrixOne = fill_matrix_example();
    double resultDet = matrixOne.determinant();
    EXPECT_EQ(resultDet, 20);
}

TEST(MatrixDetermanantTest, HandlesMatrixZeroInput) {
    OMatrix matrixOne(5, 5);
    EXPECT_EQ(matrixOne.determinant(), 0);
}

TEST(MatrixDetermanantTest, HandlesOrdinaryMatrixInput) {
    OMatrix matrixOne(1, 1);
    matrixOne(0, 0) = 1;
    EXPECT_EQ(matrixOne.determinant(), 1);
}

TEST(MatrixInverseTest, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixTwo(3, 3);
    matrixOne(0, 0) = 1.0;
    matrixOne(0, 1) = 2.0;
    matrixOne(0, 2) = 3.0;
    matrixOne(1, 0) = 0.0;
    matrixOne(1, 1) = 4.0;
    matrixOne(1, 2) = 2.0;
    matrixOne(2, 0) = 5.0;
    matrixOne(2, 1) = 2.0;
    matrixOne(2, 2) = 1.0;
    matrixTwo(0, 0) = 0.0;
    matrixTwo(0, 1) = -0.1;
    matrixTwo(0, 2) = 0.2;
    matrixTwo(1, 0) = -0.25;
    matrixTwo(1, 1) = 0.35;
    matrixTwo(1, 2) = 0.05;
    matrixTwo(2, 0) = 0.5;
    matrixTwo(2, 1) = -0.2;
    matrixTwo(2, 2) = -0.1;
    OMatrix matrixResult = matrixOne.inverse_matrix();
    bool check = matrixResult.eq_matrix(matrixTwo);
    EXPECT_EQ(check, true);
}

TEST(MatrixSubTestUnary, HandlesMatrixInput) {
    OMatrix matrixZero(5, 5);
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo(matrixOne);
    matrixOne -= matrixTwo;
    bool check = matrixOne.eq_matrix(matrixZero);
    EXPECT_EQ(check, true);
}

TEST(MatrixSubTestBinary, HandlesMatrixInput) {
    OMatrix matrixZero(5, 5);
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo(matrixOne);
    OMatrix matrixResult = matrixOne - matrixTwo;
    bool check = matrixResult.eq_matrix(matrixZero);
    EXPECT_EQ(check, true);
}

TEST(MatrixSumTestUnary, HandlesMatrixInput) {
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo(matrixOne);
    matrixOne += matrixTwo;
    OMatrix matrixResult(matrixOne);
    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(MatrixSumTestBinary, HandlesMatrixInput) {
    OMatrix matrixOne = fill_matrix_example();
    OMatrix matrixTwo(matrixOne);
    OMatrix matrixResult = matrixOne + matrixTwo;
    matrixOne *= 2;
    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(MatrixMulTestBinary, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixTwo(3, 3);
    OMatrix matrixThree(3, 3);
    matrixOne.fill_matrix();
    matrixTwo.fill_matrix();
    OMatrix matrixResult = matrixOne * matrixTwo;
    matrixThree(0, 0) = 5.0;
    matrixThree(0, 1) = 8.0;
    matrixThree(0, 2) = 11.0;
    matrixThree(1, 0) = 8.0;
    matrixThree(1, 1) = 14.0;
    matrixThree(1, 2) = 20.0;
    matrixThree(2, 0) = 11.0;
    matrixThree(2, 1) = 20.0;
    matrixThree(2, 2) = 29.0;
    bool check = matrixThree.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(MatrixMulTestUnary, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixThree(3, 3);
    OMatrix matrixResult(3, 3);
    matrixOne.fill_matrix();
    matrixResult.fill_matrix();
    matrixResult *= matrixOne;
    matrixThree(0, 0) = 5.0;
    matrixThree(0, 1) = 8.0;
    matrixThree(0, 2) = 11.0;
    matrixThree(1, 0) = 8.0;
    matrixThree(1, 1) = 14.0;
    matrixThree(1, 2) = 20.0;
    matrixThree(2, 0) = 11.0;
    matrixThree(2, 1) = 20.0;
    matrixThree(2, 2) = 29.0;
    bool check = matrixThree.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(NumberMulTestBinary, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    matrixOne.fill_matrix();
    OMatrix matrixResult = matrixOne * 2.0;
    matrixOne.mul_number(2.0);
    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(BoolOperator, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixTwo(3, 3);
    matrixOne.fill_matrix();
    matrixTwo.fill_matrix();
    bool check = false;
    if (matrixOne == matrixTwo) check = true;
    EXPECT_EQ(check, true);
}

TEST(GetterCols, HandlesMatrixInput) {
    OMatrix matrixOne(3, 3);
    matrixOne.fill_matrix();
    ASSERT_EQ(3, matrixOne.getCols());
}

TEST(SetterRows, HandlesMatrixInputBigger) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixTwo(5, 3);
    OMatrix matrixResult(5, 3);

    matrixTwo.fill_matrix();
    matrixTwo(3, 0) = 0.0;
    matrixTwo(4, 0) = 0.0;
    matrixTwo(3, 1) = 0.0;
    matrixTwo(4, 1) = 0.0;
    matrixTwo(3, 2) = 0.0;
    matrixTwo(4, 2) = 0.0;
    matrixOne.fill_matrix();

    matrixOne.setRows(5);
    ASSERT_EQ(5, matrixOne.getRows());

    matrixOne.sub_matrix(matrixTwo);

    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(SetterRows, HandlesMatrixInputSmaller) {
    OMatrix matrixOne(5, 5);
    OMatrix matrixTwo(3, 5);
    OMatrix matrixResult(3, 5);

    matrixTwo.fill_matrix();
    matrixOne.fill_matrix();

    matrixOne.setRows(3);
    ASSERT_EQ(3, matrixOne.getRows());

    matrixOne.sub_matrix(matrixTwo);

    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(SetterCols, HandlesMatrixInputBigger) {
    OMatrix matrixOne(3, 3);
    OMatrix matrixTwo(3, 5);
    OMatrix matrixResult(3, 5);

    matrixTwo.fill_matrix();
    matrixTwo(0, 3) = 0.0;
    matrixTwo(1, 3) = 0.0;
    matrixTwo(2, 3) = 0.0;
    matrixTwo(0, 4) = 0.0;
    matrixTwo(1, 4) = 0.0;
    matrixTwo(2, 4) = 0.0;
    matrixOne.fill_matrix();

    matrixOne.setCols(5);
    ASSERT_EQ(5, matrixOne.getCols());

    matrixOne.sub_matrix(matrixTwo);

    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

TEST(SetterCols, HandlesMatrixInputSmaller) {
    OMatrix matrixOne(5, 5);
    OMatrix matrixTwo(5, 3);
    OMatrix matrixResult(5, 3);

    matrixTwo.fill_matrix();
    matrixOne.fill_matrix();

    matrixOne.setCols(3);
    ASSERT_EQ(3, matrixOne.getCols());

    matrixOne.sub_matrix(matrixTwo);

    bool check = matrixOne.eq_matrix(matrixResult);
    EXPECT_EQ(check, true);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
