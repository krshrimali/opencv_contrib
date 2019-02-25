// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#include "test_precomp.hpp"

#define TEST_CASE_NAME CV_Quality_BRISQUE

namespace opencv_test
{
namespace quality_test
{

// brisque per channel
// computed test file values via original brisque c++ impl, libsvm 318, opencv 2.x
const cv::Scalar
    BRISQUE_EXPECTED_1 = { 31.154966299963547 }  // testfile_1a
    // , BRISQUE_EXPECTED_2 = { 15.411353283158718 }  // testfile_2a with original c++ impl
    , BRISQUE_EXPECTED_2 = { 15.600739064304520 }   // testfile 2a; delta is due to differences between opencv 2.x and opencv 4.x cvtColor, RGB2GRAY
;

// instantiates a brisque object for testing
inline cv::Ptr<quality::QualityBRISQUE> create_brisque()
{
    // location of BRISQUE model and range file
    //  place these files in ${OPENCV_TEST_DATA_PATH}/quality/, or the tests will be skipped
    const auto model = cvtest::findDataFile("brisque_allmodel.dat", false);
    const auto range = cvtest::findDataFile("brisque_allrange.dat", false);
    return quality::QualityBRISQUE::create(model, range);
}

// multi-channel
TEST(TEST_CASE_NAME, multi_channel)
{
    
    quality_test(create_brisque(), get_testfile_2a(), BRISQUE_EXPECTED_2, 0, true)
        ;

}

// static method
TEST(TEST_CASE_NAME, static_ )
{
    quality_expect_near(
        quality::QualityBRISQUE::compute(
            get_testfile_1a() 
            , cvtest::findDataFile("brisque_allmodel.dat", false)
            , cvtest::findDataFile("brisque_allrange.dat", false)
        )
        , BRISQUE_EXPECTED_1
    );
}

// single channel, instance method, with and without opencl
TEST(TEST_CASE_NAME, single_channel )
{
    auto fn = []() { quality_test(create_brisque(), get_testfile_1a(), BRISQUE_EXPECTED_1, 0, true ); };
    OCL_OFF( fn() );
    OCL_ON( fn() );
}


// multi-frame test
TEST(TEST_CASE_NAME, multi_frame)
{
    // result mse == average of all frames
    cv::Scalar expected;
    cv::add(BRISQUE_EXPECTED_1, BRISQUE_EXPECTED_2, expected);
    expected /= 2.;

    quality_test(create_brisque(), get_testfile_1a2a(), expected, 0, true );
}

// check brisque model/range persistence
TEST(TEST_CASE_NAME, model_persistence )
{
    auto ptr = create_brisque();
    auto fn = [&ptr]() { quality_test(ptr, get_testfile_1a(), BRISQUE_EXPECTED_1, 0, true); };
    fn();
    fn();   // model/range should persist with brisque ptr through multiple invocations
}

// internal a/b test
/*
TEST(TEST_CASE_NAME, performance)
{
    auto ref = get_testfile_1a();

    quality_performance_test("BRISQUE", [&]() { cv::quality::QualityBRISQUE::compute(ref, cv::noArray()); });
}
*/
}
} // namespace