// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_QUALITY_QUALITYBRISQUE_HPP
#define OPENCV_QUALITY_QUALITYBRISQUE_HPP

#include "qualitybase.hpp"

namespace cv
{
namespace quality
{

/**
@brief TODO:  Brief description and reference to original BRISQUE paper/implementation
*/
class CV_EXPORTS_W QualityBRISQUE : public QualityBase {
public:

    /** @brief Computes XXX for reference images supplied in class constructor and provided comparison images
    @param imgs Images for which to compute quality
    @returns TODO:  describe the resulting cv::Scalar
    */
    CV_WRAP cv::Scalar compute( InputArrayOfArrays imgs ) CV_OVERRIDE;

    /**
    @brief Create an object which calculates quality
    */
    CV_WRAP static Ptr<QualityBRISQUE> create();

    /**
    @brief static method for computing quality
    @param imgs image(s) for which to compute quality
    @param qualityMaps output quality map(s), or cv::noArray()  TODO:  remove this parameter if algorithm doesn't generate output quality maps
    @returns TODO:  describe the resulting cv::Scalar
    */
    CV_WRAP static cv::Scalar compute( InputArrayOfArrays imgs, OutputArrayOfArrays qualityMaps );

protected:

    /**
    @brief Constructor
    */
    QualityBRISQUE();

    // TODO:  Add any protected members here

};  // QualityBRISQUE
}   // quality
}   // cv
#endif