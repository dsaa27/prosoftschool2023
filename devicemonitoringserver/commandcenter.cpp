#include "commandcenter.h"

#include "messagecommand.h"
#include "messageerror.h"
#include "messagemeterage.h"

#include <algorithm>
#include <cmath>
#include <numeric>

void CommandCenter::setSchedule(const DeviceWorkSchedule& schedule)
{
    m_scheduleInfo[schedule.deviceId] = {};
    auto& scheduleInfo = m_scheduleInfo[schedule.deviceId];
    scheduleInfo.phases = schedule.schedule;
    std::sort(scheduleInfo.phases.begin(),
              scheduleInfo.phases.end(),
              [](const Phase& phaseA, const Phase& phaseB) { return phaseA.timeStamp < phaseB.timeStamp; });
}

void CommandCenter::processMeterage(uint64_t deviceId, MessageMeterage meterage, std::function<void(uint64_t, const Message&)> callback)
{
    auto currentTimeStamp = meterage.timeStamp();

    auto lastTimeStampIt = m_lastTimeStamp.find(deviceId);
    if (lastTimeStampIt != m_lastTimeStamp.end() && lastTimeStampIt->second >= currentTimeStamp)
    {
        callback(deviceId, MessageError(MessageError::ErrorType::Obsolete));
        return;
    }
    m_lastTimeStamp[deviceId] = currentTimeStamp;

    auto& scheduleInfo = m_scheduleInfo[deviceId];
    auto& statsInfo = m_statsInfo[deviceId];
    if (scheduleInfo.phases.empty())
    {
        callback(deviceId, MessageError(MessageError::ErrorType::NoSchedule));
        return;
    }

    while (scheduleInfo.currentPhaseIndex + 1 < scheduleInfo.phases.size()
           && scheduleInfo.phases[scheduleInfo.currentPhaseIndex + 1].timeStamp <= currentTimeStamp)
    {
        ++scheduleInfo.currentPhaseIndex;
    }

    auto currentPhase = scheduleInfo.phases[scheduleInfo.currentPhaseIndex];

    if (currentPhase.timeStamp > currentTimeStamp)
    {
        callback(deviceId, MessageError(MessageError::ErrorType::NoTimestamp));
        return;
    }

    int command = currentPhase.value - meterage.meterage();

    auto lastDeviationStatIt = statsInfo.deviationStats.rbegin();
    if (lastDeviationStatIt == statsInfo.deviationStats.rend()
        || lastDeviationStatIt->phase.timeStamp != currentPhase.timeStamp
        || lastDeviationStatIt->phase.value != currentPhase.value)
    {
        statsInfo.squareDiffs.clear();
        statsInfo.deviationStats.push_back({ currentPhase, currentTimeStamp, 0.0 });
        lastDeviationStatIt = statsInfo.deviationStats.rbegin();
    }
    statsInfo.squareDiffs.push_back(command * command);
    double squareDiffsSum = std::accumulate(statsInfo.squareDiffs.cbegin(), statsInfo.squareDiffs.cend(), 0.0);
    double deviation = std::sqrt(squareDiffsSum / statsInfo.squareDiffs.size());
    lastDeviationStatIt->deviation = deviation;

    callback(deviceId, MessageCommand(command));
}

std::vector<DeviationStats> CommandCenter::deviationStats(uint64_t deviceId)
{
    return m_statsInfo[deviceId].deviationStats;
}
