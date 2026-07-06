using System.Collections.Generic;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace CoreIslandApp1
{
    public sealed partial class MainPage : Page
    {
        private sealed partial class StringItemsSource
            : List<string>, Microsoft.UI.Xaml.Controls.IKeyIndexMapping
        {
            public string KeyFromIndex(int index) => this[index];
            public int IndexFromKey(string key)
            {
                int i = IndexOf(key);
                return i >= 0 ? i : -1;
            }
        }

        private readonly StringItemsSource _items = new()
        {
            "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf",
            "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf",
            "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf",
            "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf",
            "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf",
            "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf",
            "sadfsdf", "sadfsdf", "sadfsdf", "sadfsdf",
        };

        public MainPage()
        {
            InitializeComponent();
            repeater.ItemsSource = _items;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var rootFrame = new Frame();
            var newWindow = new CoreIsland.Window() { Content = rootFrame };
            rootFrame.Navigate(typeof(MainPage));
            newWindow.Title = "CoreIsland Window";
            newWindow.Activate();
        }
    }
}
