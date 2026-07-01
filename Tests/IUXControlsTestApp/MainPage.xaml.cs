using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using MUXControlsTestApp;
using MUXControlsTestApp.Utilities;

namespace IUXControlsTestApp;

public sealed partial class MainPage : Page
{
    public MainPage()
    {
        InitializeComponent();

        Loaded += MainPage_Loaded;
        Unloaded += MainPage_Unloaded;

        // Default to TitleBar hub
        ContentFrame.Navigate(typeof(TitleBarPage));
    }

    private void MainPage_Loaded(object sender, RoutedEventArgs e)
    {
        App.Window.SetTitleBar(WindowingTitleBar);
        WindowingTitleBar.RecomputeDragRegions();
    }

    private void MainPage_Unloaded(object sender, RoutedEventArgs e)
    {
        App.Window.SetTitleBar(null);
    }

    private void WindowingTitleBar_BackRequested(Islands.UI.Xaml.Controls.TitleBar sender, object args)
    {
        if (ContentFrame.CanGoBack)
            ContentFrame.GoBack();
    }

    private void TitleBarSampleButton_Click(object sender, RoutedEventArgs e)
    {
        ContentFrame.NavigateWithoutAnimation(typeof(TitleBarPage));
    }

    private void ScrollViewSampleButton_Click(object sender, RoutedEventArgs e)
    {
        ContentFrame.NavigateWithoutAnimation(typeof(ScrollViewPage));
    }

    private void ScrollPresenterSampleButton_Click(object sender, RoutedEventArgs e)
    {
        ContentFrame.NavigateWithoutAnimation(typeof(ScrollPresenterPage));
    }
}
