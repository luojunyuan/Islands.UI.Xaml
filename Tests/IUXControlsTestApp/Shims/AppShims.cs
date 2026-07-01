// App-level shims for MUXControlsTestApp patterns used in TestUI pages.
// Provides stub implementations so shared TestUI code compiles in IUXControlsTestApp.

using System;
using Windows.UI.Xaml;

// The shared TestUI pages live in namespace MUXControlsTestApp and call App.AppendResourceDictionaryToMergedDictionaries.
// We wire those calls to IUXControlsTestApp.App which is the actual running app.
namespace MUXControlsTestApp
{
    public static class App
    {
        public static void AppendResourceDictionaryToMergedDictionaries(ResourceDictionary? dict)
        {
            if (dict == null) return;
            Application.Current.Resources.MergedDictionaries.Add(dict);
        }

        private static ResourceDictionary? _additionStylesXaml;
        public static ResourceDictionary AdditionStylesXaml
        {
            get
            {
                if (_additionStylesXaml == null)
                {
                    _additionStylesXaml = new ResourceDictionary
                    {
                        Source = new Uri("ms-appx:///Themes/AdditionalStyles.xaml")
                    };
                }
                return _additionStylesXaml;
            }
        }
    }
}

namespace MUXControlsTestApp.Utilities
{
    public static class RunOnUIThread
    {
        public static void Execute(Action action) => action();
    }
}
