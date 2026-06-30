using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace IUXControlsTestApp;

public sealed partial class TitleBarPage : UserControl
{
    public TitleBarPage()
    {
        InitializeComponent();
    }

    private void BackButtonVisibleCheckBox_Changed(object sender, RoutedEventArgs e)
    {
        SampleTitleBar.IsBackButtonVisible = BackButtonVisibleCheckBox.IsChecked == true;
        SampleTitleBar.RecomputeDragRegions();
    }

    private void PaneToggleVisibleCheckBox_Changed(object sender, RoutedEventArgs e)
    {
        SampleTitleBar.IsPaneToggleButtonVisible = PaneToggleVisibleCheckBox.IsChecked == true;
        SampleTitleBar.RecomputeDragRegions();
    }

    private void IconVisibleCheckBox_Changed(object sender, RoutedEventArgs e)
    {
        SampleTitleBar.IconSource = IconVisibleCheckBox.IsChecked == true
            ? new Microsoft.UI.Xaml.Controls.SymbolIconSource { Symbol = Symbol.Mail }
            : null;
        SampleTitleBar.RecomputeDragRegions();
    }

    private void SetTitleButton_Click(object sender, RoutedEventArgs e)
    {
        SampleTitleBar.Title = string.IsNullOrWhiteSpace(TitleTextBox.Text)
            ? "Sample Title"
            : TitleTextBox.Text;
    }
}
