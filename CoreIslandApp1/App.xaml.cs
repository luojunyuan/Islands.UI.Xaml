using Windows.ApplicationModel.Activation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace CoreIslandApp1
{
    public sealed partial class App : CoreIsland.Application
    {
        public static CoreIsland.Window Window => _window!;

        private static CoreIsland.Window? _window;

        public App()
        {
            InitializeComponent();
        }

        protected override void OnIslandLaunched(LaunchActivatedEventArgs e)
        {
            var rootFrame = new Frame();
            rootFrame.NavigationFailed += OnNavigationFailed;

            _window = new CoreIsland.Window()
            {
                Content = rootFrame
            };

            rootFrame.Navigate(typeof(MainPage), e.Arguments);

            _window.ExtendsContentIntoTitleBar = true;

            _window.Activate();
        }

        private void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception($"Failed to load Page {e.SourcePageType.FullName}");
        }
    }
}
