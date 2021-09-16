/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * For documentation examples please Javadoc_test at: https://www.doxygen.nl/manual/docblocks.html
 *
 * For coding standard examples please read: https://github.com/opencv/opencv/wiki/Coding_Style_Guide
 */
/*! @file      PhotoEditor.cpp
 *  @date      09/06/2021.
 *  @author    Steven D.
 *  @copyright GNU Public License.
 *  @header    "PhotoEditor.h"
*/
#include "photoeditor.h"
#include <qmath.h>
#include <functional>

const std::string PhotoEditor::WINDOW_NAME = "PhotoEditor";
using namespace cv;

/**
 * Constructor that initializes GUI components and click handlers.
 *
 * @param parent Widget passed to base class
 *
 * @return none
 *
 * @throws none
 *
 * @exceptsafe Strong exception guarantee.
 */
PhotoEditor::PhotoEditor(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("PhotoEditor Features"));
    resize(100, 100);

    photoEditor = new QFutureWatcher<QImage>(this);
    connect(photoEditor, &QFutureWatcher<QImage>::resultReadyAt, this, &PhotoEditor::showImage);

    openButton = new QPushButton(tr("Open PhotoEditor"));
    connect(openButton, &QPushButton::clicked, this, &PhotoEditor::open);

    grayScaleButton = new QPushButton(tr("Grayscale"));
    grayScaleButton->setEnabled(true);
    connect(grayScaleButton, &QPushButton::clicked, this,&PhotoEditor::grayScaleFeature);

    newFeature = new QPushButton(tr("New Feature"));
    newFeature->setEnabled(false);
    connect(newFeature, &QPushButton::clicked, photoEditor, &QFutureWatcher<QImage>::togglePaused);

    /*-----------INSTRUCTIONS-------------------------------------------------------------------------------------------
     * This section demonstrates how to add a new feature(button) .cpp files.
     * Copy and and paste the code below:
     * ----------New Feature logic in .cpp file--------------------------------------------------------------------------
     * newFeatureButton = new QPushButton(tr("New Feature"));
     * newFeatureButton->setEnabled(false);
     * connect(newFeatureButton, &QPushButton::clicked, photoEditor, &QFutureWatcher<QImage>::newFeature);
     * -----------------------------------------------------------------------------------------------------
     *
     * Perform the following steps:
     * 1.) Update the button name with the name of your new feature aka "newFeatureButton"
     * 2.) Add your button the buttonLayout component section of this function: buttonLayout->(newFeatureButton);
     * 3.) Add a function prototype to the header file to support your new feature.
     * 4.) Add your function to the *bottom* of the .cpp file and call showImage function.
     *     PhotoEditor::newFeature()
     *     {
     *          // Your logic goes here
     *          // Do cool ISP stuff
     *          // refreshImage();
     *     }
     * 5.)Done.
    */

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(grayScaleButton);
    buttonLayout->addWidget(newFeature);
    buttonLayout->addStretch();


    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    file  = QString();
}

/**
 * Destorys objects reated by Image class
 *
 * @param none
 *
 * @return none
 *
 * @throws none
 *
 * @exceptsafe Strong exception guarantee.
 */
PhotoEditor::~PhotoEditor()
{
    photoEditor->cancel();
    photoEditor->waitForFinished();
}

/**
 * Read an image from disk and stores it for local use.
 *
 * @param none
 *
 * @return void
 *
 * @throws none
 *
 * @exceptsafe Strong exception guarantee.
 */
void PhotoEditor::open()
{
    // Cancel and wait if we are already loading images.
    if (photoEditor->isRunning()) {
        photoEditor->cancel();
    }

    // Show a file open dialog at QStandardPaths::PicturesLocation.
    file = QFileDialog::getOpenFileName(this, tr("Select Image"),
                            QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                            "*.jpg *.png");

    if (file.isEmpty())
        return;

    image = cv::imread(file.toStdString().c_str(), 1);

    showImage();
    grayScaleButton->setEnabled(true);
    newFeature->setEnabled(false);
}

/**
 * Displays an image after it's initially read in.
 *
 * @param none
 *
 * @return void
 *
 * @throws none
 *
 * @exceptsafe Strong exception guarantee.
 */
void PhotoEditor::showImage()
{
    // create image window
    cv::namedWindow(WINDOW_NAME);
    // show the image on window
    cv::imshow(WINDOW_NAME, image);
}

/**
 * Converts an image to gray scale
 *
 * @param none
 *
 * @return void
 *
 * @throws none
 *
 * @exceptsafe Strong exception guarantee.
 */
void PhotoEditor::grayScaleFeature()
{
    Mat gray_image;
    cvtColor( image, gray_image, COLOR_BGR2GRAY );
    imwrite( "Gray_Image.jpg", gray_image );
    refreshImage(gray_image);
    waitKey(1);
}

/**
 * Refreshes image that has already been loaded.
 *
 * @param image a cv::Mat
 *
 * @return void
 *
 * @throws none
 *
 * @exceptsafe Strong exception guarantee.
 */
void PhotoEditor::refreshImage(cv::Mat image)
{
    // show the image on window
    cv::imshow(WINDOW_NAME, image);
}
