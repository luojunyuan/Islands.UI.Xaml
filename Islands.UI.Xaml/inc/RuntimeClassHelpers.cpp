module inc.RuntimeClassHelpers;

import winrt.Windows.System;

namespace RuntimeClassHelpersDetail
{
    bool TryEnqueueFinalRelease(
        winrt::DispatcherQueue const& dispatcherQueue,
        void* instance,
        FinalReleaseCallback callback) noexcept
    {
        if (!dispatcherQueue)
        {
            return false;
        }

        return dispatcherQueue.TryEnqueue(winrt::DispatcherQueueHandler(
            [instance, callback]()
            {
                callback(instance);
            }));
    }
}
