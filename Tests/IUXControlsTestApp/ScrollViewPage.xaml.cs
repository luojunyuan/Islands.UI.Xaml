using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace IUXControlsTestApp;

public sealed partial class ScrollViewPage : UserControl
{
    private readonly Brush[] _rowBrushes =
    [
        new SolidColorBrush(Windows.UI.Color.FromArgb(255, 215, 232, 255)),
        new SolidColorBrush(Windows.UI.Color.FromArgb(255, 255, 227, 194)),
        new SolidColorBrush(Windows.UI.Color.FromArgb(255, 217, 240, 211)),
        new SolidColorBrush(Windows.UI.Color.FromArgb(255, 238, 220, 255)),
    ];

    private bool _isWide = true;
    private int _nextRow = 4;

    public ScrollViewPage()
    {
        InitializeComponent();
        UpdateMetrics();
    }

    private void AddRowButton_Click(object sender, RoutedEventArgs e)
    {
        RowsPanel.Children.Add(new Border
        {
            Height = 96,
            Background = _rowBrushes[_nextRow % _rowBrushes.Length],
            BorderBrush = new SolidColorBrush(Windows.UI.Color.FromArgb(255, 91, 120, 160)),
            BorderThickness = new Thickness(1),
            Child = new TextBlock
            {
                Margin = new Thickness(16),
                VerticalAlignment = VerticalAlignment.Center,
                FontSize = 18,
                Text = $"Row {_nextRow}",
            },
        });

        _nextRow++;
        ScrollableContent.Height += 108;
        SampleScrollView.ScrollBy(0, 108);
    }

    private void ToggleWidthButton_Click(object sender, RoutedEventArgs e)
    {
        _isWide = !_isWide;
        ScrollableContent.Width = _isWide ? 1280 : 860;
        UpdateMetrics();
    }

    private void ScrollToOriginButton_Click(object sender, RoutedEventArgs e)
    {
        SampleScrollView.ScrollTo(0, 0);
    }

    private void SampleScrollView_ViewChanged(Islands.UI.Xaml.Controls.ScrollView sender, object args)
    {
        UpdateMetrics();
    }

    private void UpdateMetrics()
    {
        MetricsTextBlock.Text = $"H {SampleScrollView.HorizontalOffset:0}  V {SampleScrollView.VerticalOffset:0}";
    }
}
