// Copyright 2019 The MWC Developers
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EVENTS_H
#define EVENTS_H

#include "state.h"
#include "../core/Notification.h"
#include <QVector>

namespace wnd {
class Events;
}

namespace state {

class Events : public QObject, public State
{
    Q_OBJECT
public:
    Events( StateContext * context );
    virtual ~Events() override;

    void deleteEventsWnd(wnd::Events * w);

    QVector<int> getColumnsWidhts() const;
    void updateColumnsWidhts(const QVector<int> & widths);

    QVector<notify::NotificationMessage> getWalletNotificationMessages();
    int64_t getWatermarkTime() const {return messageWaterMark;}

    // Check if some error/warnings need to be shown
    bool hasNonShownWarnings() const;
public:
signals:
    void updateNonShownWarnings(bool hasNonShownWarns);

private slots:
    void onNewNotificationMessage(notify::MESSAGE_LEVEL level, QString message);

protected:
    virtual NextStateRespond execute() override;
    virtual QString getHelpDocName() override {return "event_log.html";}
private:
    wnd::Events *   wnd = nullptr;
    int64_t         messageWaterMark = 0;
};

}

#endif // EVENTS_H
