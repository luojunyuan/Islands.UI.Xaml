// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Islands.UI.Xaml.Controls;
using Islands.UI.Xaml.Controls.Primitives;
using WEX.Logging.Interop;

namespace MUXControlsTestApp
{
    [TopLevelTestPage(Name = "TitleBar", Icon = "DefaultIcon.png")]
    public sealed partial class TitleBarPage
    {
        public TitleBarPage()
        {
            LogController.InitializeLogging();
            this.InitializeComponent();
        }

        private void CmbTitleBarOutputDebugStringLevel_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            MUXControlsTestHooks.SetOutputDebugStringLevelForType(
                "TitleBar",
                cmbTitleBarOutputDebugStringLevel.SelectedIndex == 1 || cmbTitleBarOutputDebugStringLevel.SelectedIndex == 2,
                cmbTitleBarOutputDebugStringLevel.SelectedIndex == 2);
        }

        private void TitleBarWindowingButton_Click(object sender, RoutedEventArgs e)
        {
            var newWindow = new TitleBarPageWindow();
            newWindow.Activate();
        }
    }
}
