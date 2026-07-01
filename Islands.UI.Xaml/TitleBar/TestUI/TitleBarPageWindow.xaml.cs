// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using Islands.UI.Xaml.Controls;
using Islands.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Markup;
using WEX.Logging.Interop;
using System.Runtime.InteropServices;
using System;

namespace MUXControlsTestApp
{
    public sealed partial class TitleBarPageWindow
    {
        private int backRequestedCount = 0;
        private int paneToggleRequestedCount = 0;
        private CoreIsland.Window? window;

        private const int GWL_EXSTYLE = -20;
        private const int WS_EX_LAYOUTRTL = 0x00400000;

        public TitleBarPageWindow()
        {
            LogController.InitializeLogging();
            this.InitializeComponent();
        }

        // Called by parent page to activate (show) this control in a new CoreIsland window.
        public void Activate()
        {
            window = new CoreIsland.Window { Content = this };
            window.ExtendsContentIntoTitleBar = true;
            window.SetTitleBar(this.WindowingTitleBar);
            window.Title = this.WindowingTitleBar.Title;
            window.Activate();
        }

        private void CmbTitleBarOutputDebugStringLevel_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            MUXControlsTestHooks.SetOutputDebugStringLevelForType(
                "TitleBar",
                cmbTitleBarOutputDebugStringLevel.SelectedIndex == 1 || cmbTitleBarOutputDebugStringLevel.SelectedIndex == 2,
                cmbTitleBarOutputDebugStringLevel.SelectedIndex == 2);
        }

        private void EnableRTLToggleButton_Checked(object sender, RoutedEventArgs e)
        {
            TitleBarPageWindowGrid.FlowDirection = FlowDirection.RightToLeft;
            UpdateCaptionButtonDirection(TitleBarPageWindowGrid.FlowDirection);
        }

        private void EnableRTLToggleButton_Unchecked(object sender, RoutedEventArgs e)
        {
            TitleBarPageWindowGrid.FlowDirection = FlowDirection.LeftToRight;
            UpdateCaptionButtonDirection(TitleBarPageWindowGrid.FlowDirection);
        }

        [DllImport("user32.dll", EntryPoint = "SetWindowLongPtr")]
        internal static extern IntPtr SetWindowLongPtr(IntPtr hWnd, int nIndex, nint newProc);

        [DllImport("user32.dll", EntryPoint = "GetWindowLongPtr")]
        internal static extern IntPtr GetWindowLongPtr(IntPtr hWnd, int nIndex);

        private void UpdateCaptionButtonDirection(FlowDirection direction)
        {
            if (window == null) return;
            var hwnd = CoreIsland.Windowing.WindowNative.GetWindowHandle(window);
            if (hwnd == IntPtr.Zero) return;

            var exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
            if (direction == FlowDirection.RightToLeft)
                exStyle |= WS_EX_LAYOUTRTL;
            else
                exStyle &= ~WS_EX_LAYOUTRTL;
            SetWindowLongPtr(hwnd, GWL_EXSTYLE, exStyle);
        }

        private void WindowingTitleBar_BackRequested(TitleBar sender, object args)
        {
            BackRequestedCountTextBox.Text = (backRequestedCount++).ToString();
        }

        private void IsBackButtonVisibleCheckBox_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar != null)
                WindowingTitleBar.IsBackButtonVisible = IsBackButtonVisibleCheckBox.IsChecked!.Value;
        }

        private void IsBackButtonEnabledCheckBox_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar != null)
                WindowingTitleBar.IsBackButtonEnabled = IsBackButtonEnabledCheckBox.IsChecked!.Value;
        }

        private void WindowingTitleBar_PaneToggleRequested(TitleBar sender, object args)
        {
            PaneToggleButtonRequestedCountTextBox.Text = (paneToggleRequestedCount++).ToString();
        }

        private void IsPaneToggleButtonVisibleCheckbox_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar != null)
                WindowingTitleBar.IsPaneToggleButtonVisible = IsPaneToggleButtonVisibleCheckbox.IsChecked!.Value;
        }

        private void SetIconCheckBox_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar == null) return;
            if (SetIconCheckBox.IsChecked!.Value)
            {
                var icon = new Microsoft.UI.Xaml.Controls.SymbolIconSource { Symbol = Symbol.Mail };
                WindowingTitleBar.IconSource = icon;
            }
            else
            {
                WindowingTitleBar.IconSource = null;
            }
        }

        private void CustomContentCheckBox_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar == null) return;
            if (CustomContentCheckBox.IsChecked!.Value)
            {
                string xaml =
                @"<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation'>
                     <Grid.ColumnDefinitions>
                        <ColumnDefinition Width='Auto'/>
                        <ColumnDefinition Width='*' />
                     </Grid.ColumnDefinitions >
                     <Button Content='Left'/>
                     <Button Grid.Column='1' Content='Right' HorizontalAlignment='Right'/>
                </Grid>";
                var element = (Grid)XamlReader.Load(xaml);
                WindowingTitleBar.Content = element;
            }
            else
            {
                WindowingTitleBar.Content = null;
            }
        }

        private void LeftHeaderCheckBox_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar == null) return;
            WindowingTitleBar.LeftHeader = LeftHeaderCheckBox.IsChecked!.Value
                ? new Button { Content = "LeftHeader" }
                : null;
        }

        private void RightHeaderCheckBox_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar == null) return;
            WindowingTitleBar.RightHeader = RightHeaderCheckBox.IsChecked!.Value
                ? new Button { Content = "RightHeader" }
                : null;
        }

        private void SetSubtitleButton_Click(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar != null)
                WindowingTitleBar.Subtitle = SubtitleTextBox.Text;
        }

        private void TitleButton_Click(object sender, RoutedEventArgs e)
        {
            if (WindowingTitleBar != null)
                WindowingTitleBar.Title = TitleTextBox.Text;
        }
    }
}
