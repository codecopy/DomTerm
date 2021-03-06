/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef BROWSERAPPLICATION_H
#define BROWSERAPPLICATION_H

#include <QtWidgets/QApplication>

#include <QtCore/QUrl>
#include <QtCore/QPointer>

#include <QtGui/QIcon>

#include <QtNetwork/QAuthenticator>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
class QWebEngineProfile;
class QFileSystemWatcher;
QT_END_NAMESPACE

#include "processoptions.h"

#include "dt_version.h"

class BrowserMainWindow;
class CookieJar;

class BrowserApplication : public QApplication
{
    Q_OBJECT

public:
    BrowserApplication(int &argc, char **argv,
                       QSharedDataPointer<ProcessOptions> processOptions);
    ~BrowserApplication();
    static BrowserApplication *instance();
    void loadSettings();

    //bool isTheOnlyBrowser() const;
    BrowserMainWindow *mainWindow();
    QList<BrowserMainWindow*> mainWindows();
    QIcon icon(const QUrl &url) const;
    QIcon defaultIcon() const;
    QFileSystemWatcher* fileSystemWatcher() { return m_fileSystemWatcher; }

    QString generateSessionName();
    int getSaveFileCount() { return ++saveFileCounter; }

    static CookieJar *cookieJar();
    static QNetworkAccessManager *networkAccessManager();

#if defined(Q_OS_OSX)
    bool event(QEvent *event);
#endif

public slots:
  BrowserMainWindow *newMainWindow(const QString& url, int width, int height,
                                   const QString& position, bool headless,
                                   QSharedDataPointer<ProcessOptions> processOption);
    BrowserMainWindow *newMainWindow(const QString& url, QSharedDataPointer<ProcessOptions> processOption);
    void quitBrowser();
private slots:
    void postLaunch();
    void openUrl(const QUrl &url);

private:
    void clean();
    void installTranslator(const QString &name);
    static QNetworkAccessManager *s_networkAccessManager;

    QList<QPointer<BrowserMainWindow> > m_mainWindows;
    QWebEngineProfile *m_privateProfile;
    mutable QIcon m_defaultIcon;

    QAuthenticator m_lastAuthenticator;
    QAuthenticator m_lastProxyAuthenticator;
    QFileSystemWatcher *m_fileSystemWatcher;
    QString nameTemplate;
    int nextSessionNameIndex;
    int saveFileCounter;
    bool headlessOption;
};

#endif // BROWSERAPPLICATION_H
