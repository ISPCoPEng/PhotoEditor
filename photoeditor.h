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
 *
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
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

#ifndef PHOTOEDITOR_H
#define PHOTOEDITOR_H

#include <QtWidgets>
#include <QtConcurrent>
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/cvdef.h"
#include <opencv2/imgproc/imgproc.hpp>

/*! @file     PhotoEditor.h
 *  @class    PhotoEditor
 *  @brief    A PhotoEditor class.
 *  @date     09/06/2021
 *  @details  The PhotoEditor class contains logic needed for opening
 *            and modifying an images.
 *  @author   Steven D.
 *  @copyright GNU Public License.
*/
class PhotoEditor : public QWidget
{
Q_OBJECT
public:

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
    PhotoEditor(QWidget *parent = nullptr);

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
    ~PhotoEditor();

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
    void refreshImage(cv::Mat image);
public slots:

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
    void open();

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
    void showImage();

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
    void grayScaleFeature();
    /* ----------New Feature logic in .h file--------------------------------------------------------------------------
     *   This is where your function prototype for a new feature goes. New features are "Signals" that have to be connected
     *   to buttons. Please add the new function prototype to the bottom of the list.For Example:
     *
     *   void newFeature();
    */
private:

    /* ----------New button declaration in .h file--------------------------------------------------------------------------
     *   This is where you add your new button
     *   QPushButton *newFeatureButton;
    */
    QPushButton *openButton;                /*!< Detailed description after the member */
    QPushButton *grayScaleButton;           /*!< Detailed description after the member */
    QPushButton *newFeature;               /*!< Detailed description after the member */
    QVBoxLayout *mainLayout;                /*!< Detailed description after the member */
    QGridLayout *imagesLayout;              /*!< Detailed description after the member */
    QFutureWatcher<QImage> *photoEditor;    /*!< Detailed description after the member */
    QLabel *imageLabel;                     /*!< Detailed description after the member */
    QString file;                           /*!< Detailed description after the member */
    cv::Mat image;                          /*!< Detailed description after the member */
    static const std::string WINDOW_NAME;   /*!< Detailed description after the member */
};

#endif // PHOTOEDITOR_H
