#include <cmath>

#include "rescuemission.hh"
#include "utility.hh"
#include "missiondialog.hh"
#include "missioncompleteddialog.hh"

namespace Student
{

const int RescueMission::REWARD = 1000;

RescueMission::RescueMission(std::shared_ptr<Common::StarSystem> location,
                             unsigned time,
                             QString playerName,
                             QObject *parent)
    : time_(time), location_(location)
{
    finished_ = false;
    failed_ = false;

    int dice = Common::randomMinMax(0,3);

    rng_ = static_cast<double>(Common::randomMinMax(30,60)) / 100.0;

    StudentUI::MissionDialog *dialog = new StudentUI::MissionDialog(rng_,
                                                                    MISSION_TYPE(dice),
                                                                    location->getName(),
                                                                    playerName,
                                                                    time_);

    emit dialogOpened();

    dialog->exec();

    connect(dialog, SIGNAL(accepted()), this, SLOT(closeDialog()));
}

RescueMission::~RescueMission()
{
}

unsigned RescueMission::getTimeLeft()
{
    return time_;
}

std::shared_ptr<Common::StarSystem> RescueMission::getLocation()
{
    return location_;
}

bool RescueMission::getStatus()
{
    if(finished_ || failed_)
    {
        return false;
    }
    return true;
}

void RescueMission::reduceTurn()
{
    if(finished_ == true)
    {
        return;
    }
    else if(time_ < 1)
    {
        failed_ = true;
        emit missionFailed(location_);
        auto *failedDialog = new StudentUI::MissionCompletedDialog(false);
        failedDialog->exec();
    }
    --time_;
}

void RescueMission::closeDialog()
{
    emit closeDialog();
}

void RescueMission::tryComplete()
{
    double diceThrow = static_cast<double>(Common::randomMinMax(1, 100)) / 100.0;

    if(diceThrow > rng_)
    {
        finished_ = true;

        int reward = static_cast<int>(std::floor(REWARD * rng_));

        emit missionSuccess(location_, reward);

        auto *completedDialog = new StudentUI::MissionCompletedDialog(true);
        completedDialog->exec();
    }
    else
    {
        rng_ -= 0.1;
        emit attemptFailed();
    }
}

}
