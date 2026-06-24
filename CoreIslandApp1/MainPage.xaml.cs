using Islands.UI.Xaml.Controls;
using CoreIsland.Windowing;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace CoreIslandApp1
{
    public sealed partial class MainPage : Page
    {
        private readonly TitleBarWindowAdapter _titleBarAdapter;
        private bool _isTitleBarAttached;

        public MainPage()
        {
            InitializeComponent();

            _titleBarAdapter = new TitleBarWindowAdapter(MyTitleBar);
            _titleBarAdapter.WindowTitleBar.ExtendsContentIntoTitleBar = true;

            Loaded += MainPage_Loaded;
            Unloaded += MainPage_Unloaded;

            AttachTitleBar();
        }

        private void MainPage_Loaded(object sender, RoutedEventArgs e)
        {
            AttachTitleBar();
            MyTitleBar.RecomputeDragRegions();
            App.Window.RefreshTitleBar();
        }

        private void MainPage_Unloaded(object sender, RoutedEventArgs e)
        {
            if (!_isTitleBarAttached)
                return;

            App.Window.Activated -= Window_Activated;
            App.Window.SetTitleBar(null);
            _isTitleBarAttached = false;
        }

        private void Window_Activated(object sender, CoreIsland.WindowActivatedEventArgs e)
        {
            _titleBarAdapter.NotifyWindowActivated(e.IsActive);
        }

        private void AttachTitleBar()
        {
            if (_isTitleBarAttached)
                return;

            _titleBarAdapter.WindowHandle = (long)WindowNative.GetWindowHandle(App.Window);
            App.Window.SetTitleBar(
                MyTitleBar,
                _titleBarAdapter.HitTest,
                _titleBarAdapter.ApplyTitleBarWindowRegion);
            App.Window.Activated += Window_Activated;
            _isTitleBarAttached = true;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // Open a new CoreIsland window on button click
            var rootFrame = new Frame();
            var newWindow = new CoreIsland.Window()
            {
                Content = rootFrame
            };
            rootFrame.Navigate(typeof(MainPage));
            newWindow.Title = "CoreIsland Window";
            newWindow.Activate();
        }
    }
}
