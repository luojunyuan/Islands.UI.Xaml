using Windows.UI.Xaml.Controls;

// Extension method in MUXControlsTestApp so all TestUI pages (namespace MUXControlsTestApp) can call it without an extra using.
namespace MUXControlsTestApp
{
    public static class FrameExtensions
    {
        public static bool NavigateWithoutAnimation(this Frame frame, System.Type pageType, object? parameter = null)
        {
            return frame.Navigate(pageType, parameter, new Windows.UI.Xaml.Media.Animation.SuppressNavigationTransitionInfo());
        }
    }
}
