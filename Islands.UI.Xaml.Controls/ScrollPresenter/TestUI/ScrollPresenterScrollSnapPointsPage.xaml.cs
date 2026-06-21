// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Numerics;
using Windows.UI;
using Windows.UI.Xaml;
using Islands.UI.Xaml.Controls;
using Islands.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;
using Windows.UI.Xaml.Navigation;
using Islands.UI.Xaml.Controls.Primitives;

namespace MUXControlsTestApp
{
    public sealed partial class ScrollPresenterScrollSnapPointsPage : TestPage
    {
        private const int snapPointColumns = 29;
        private const int snapPointColumnWidth = 10;
        private const int snapPointColumnHeight = 10000;
        private int colorIndex = 0;
        private List<string> fullLogs = new List<string>();

        public ScrollPresenterScrollSnapPointsPage()
        {
            this.InitializeComponent();
            Loaded += ScrollPresenterScrollSnapPointsPage_Loaded;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            if (chkLogScrollPresenterMessages.IsChecked == true)
            {
                MUXControlsTestHooks.SetLoggingLevelForType("ScrollPresenter", isLoggingInfoLevel: false, isLoggingVerboseLevel: false);
                MUXControlsTestHooks.LoggingMessage -= MUXControlsTestHooks_LoggingMessage;
            }

            base.OnNavigatedFrom(e);
        }

        private void ScrollPresenterScrollSnapPointsPage_Loaded(object sender, RoutedEventArgs e)
        {
            SolidColorBrush brush = new SolidColorBrush(Windows.UI.Colors.Red);
            for (int j = 0; j < snapPointColumns; j++)
            {
                Grid innerGrid = new Grid();
                innerGrid.Width = snapPointColumnWidth;
                innerGrid.Height = snapPointColumnHeight;
                this.stackPanel.Children.Add(innerGrid);
            }
            this.markupScrollPresenter.ViewChanged += MarkupScrollPresenter_ViewChanged;
            this.markupScrollPresenter.StateChanged += MarkupScrollPresenter_StateChanged;
        }

        private void MarkupScrollPresenter_ViewChanged(ScrollPresenter sender, object args)
        {
            this.txtScrollPresenterOffset.Text = this.markupScrollPresenter.VerticalOffset.ToString("F2");
            this.txtScrollPresenterZoomFactor.Text = this.markupScrollPresenter.ZoomFactor.ToString("F2");
        }

        private void MarkupScrollPresenter_StateChanged(ScrollPresenter sender, object args)
        {
            this.txtScrollPresenterState.Text = this.markupScrollPresenter.State.ToString();
        }

        private void BtnMIAddSnapPoint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                double value = Convert.ToDouble(txtMISnapPointValue.Text);
                ScrollSnapPoint newSnapPoint = new ScrollSnapPoint(value, (ScrollSnapPointsAlignment)cmbMISnapPointAlignment.SelectedIndex);
                Color fillColor = GetNewColor();
                ScrollPresenterTestHooks.SetSnapPointVisualizationColor(newSnapPoint, fillColor);
                markupScrollPresenter.VerticalSnapPoints.Add(newSnapPoint);

                FillSnapPoint(new List<double> { value }, value, value, fillColor);
                FixConsolidatedView();
            }
            catch (Exception ex)
            {
                this.fullLogs.Add(ex.ToString());
                txtExceptionReport.Text = ex.ToString();
            }
        }

#if ApplicableRangeType
        private void BtnOIAddSnapPoint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                double value = Convert.ToDouble(txtOISnapPointValue.Text);
                double range = Convert.ToDouble(txtOIApplicableRange.Text);
                ScrollSnapPoint newSnapPoint = new ScrollSnapPoint(value, range, ScrollSnapPointsAlignment.Near);
                Color fillColor = GetNewColor();
                ScrollPresenterTestHooks.SetSnapPointVisualizationColor(newSnapPoint, fillColor);
                markupScrollPresenter.VerticalSnapPoints.Add(newSnapPoint);

                FillSnapPoint(new List<double> { value }, (value - range), (value + range), fillColor);
                FixConsolidatedView();
            }
            catch (Exception ex)
            {
                this.fullLogs.Add(ex.ToString());
                txtExceptionReport.Text = ex.ToString();
            }
        }
#endif

        private void BtnMRAddSnapPoint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                double offset = Convert.ToDouble(txtMRSnapPointOffset.Text);
                double interval = Convert.ToDouble(txtMRSnapPointInterval.Text);
                double start = Convert.ToDouble(txtMRSnapPointStart.Text);
                double end = Convert.ToDouble(txtMRSnapPointEnd.Text);
                RepeatedScrollSnapPoint newSnapPoint = new RepeatedScrollSnapPoint(offset, interval, start, end, (ScrollSnapPointsAlignment)cmbMRSnapPointAlignment.SelectedIndex);
                Color fillColor = GetNewColor();
                ScrollPresenterTestHooks.SetSnapPointVisualizationColor(newSnapPoint, fillColor);
                markupScrollPresenter.VerticalSnapPoints.Add(newSnapPoint);

                double value = GetFirstRepeatedSnapPoint(offset, interval, start);
                List<double> values = new List<double>();

                while (value <= end)
                {
                    values.Add(value);
                    value += interval;
                }

                FillSnapPoint(values, start, end, fillColor);
                FixConsolidatedView();
            }
            catch (Exception ex)
            {
                this.fullLogs.Add(ex.ToString());
                txtExceptionReport.Text = ex.ToString();
            }
        }

#if ApplicableRangeType
        private void BtnORAddSnapPoint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                double offset = Convert.ToDouble(txtORSnapPointOffset.Text);
                double interval = Convert.ToDouble(txtORSnapPointInterval.Text);
                double range = Convert.ToDouble(txtORApplicableRange.Text);
                double start = Convert.ToDouble(txtORSnapPointStart.Text);
                double end = Convert.ToDouble(txtORSnapPointEnd.Text);

                RepeatedScrollSnapPoint newSnapPoint = new RepeatedScrollSnapPoint(offset, interval, start, end, range, ScrollSnapPointsAlignment.Near);
                Color fillColor = GetNewColor();
                ScrollPresenterTestHooks.SetSnapPointVisualizationColor(newSnapPoint, fillColor);
                markupScrollPresenter.VerticalSnapPoints.Add(newSnapPoint);

                double value = GetFirstRepeatedSnapPoint(offset, interval, start);
                
                int minColumn = FillSnapPoint(new List<double>(), start, end, fillColor);
                while (value <= end)
                {
                    FillSnapPoint(new List<double> { value }, Math.Max(start, value - range), Math.Min(end, value + range), fillColor, minColumn);
                    value += interval;
                }
                FixConsolidatedView();
            }
            catch (Exception ex)
            {
                this.fullLogs.Add(ex.ToString());
                txtExceptionReport.Text = ex.ToString();
            }
        }
#endif

        private void BtnRemoveFirst_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                markupScrollPresenter.VerticalSnapPoints.RemoveAt(0);
                // TODO: Consider refreshing visualization of snap points
            }
            catch (Exception ex)
            {
                txtExceptionReport.Text = ex.ToString();
            }
        }

        private void BtnRemoveAll_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                markupScrollPresenter.VerticalSnapPoints.Clear();
                // TODO: Consider clearing visualization of snap points
            }
            catch (Exception ex)
            {
                txtExceptionReport.Text = ex.ToString();
            }
        }

        private void BtnScrollPresenterOffsetChange_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                double changeAmount = Convert.ToDouble(txtScrollPresenterOffsetChange.Text);
                markupScrollPresenter.AddScrollVelocity(new Vector2(0.0f, (float)((changeAmount * 3) + 30)), null);
            }
            catch (Exception ex)
            {
                txtExceptionReport.Text = ex.ToString();
            }
        }

        private void BtnOffsetPlus10With_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                markupScrollPresenter.ScrollBy(0.0, 10.0, new ScrollingScrollOptions(ScrollingAnimationMode.Auto, ScrollingSnapPointsMode.Default));
            }
            catch (Exception ex)
            {
                txtExceptionReport.Text = ex.ToString();
            }
        }

        private void BtnOffsetPlus10Without_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                markupScrollPresenter.ScrollBy(0.0, 10.0, new ScrollingScrollOptions(ScrollingAnimationMode.Auto, ScrollingSnapPointsMode.Ignore));
            }
            catch (Exception ex)
            {
                txtExceptionReport.Text = ex.ToString();
            }
        }

        private void BtnClearExceptionReport_Click(object sender, RoutedEventArgs e)
        {
            txtExceptionReport.Text = string.Empty;
        }

        private int FillSnapPoint(List<double> values, double min, double max, int minColumn = 0)
        {
            return FillSnapPoint(values, min, max, GetNewColor(), minColumn);
        }

        private int FillSnapPoint(List<double> values, double min, double max, Color fillColor, int minColumn = 0)
        {
            bool argsAreValid = true;
            foreach (int value in values)
            {
                if (!(min <= value && value <= max))
                {
                    argsAreValid = false;
                    break;
                }
            }
            if (argsAreValid)
            {
                for (int i = minColumn; i < snapPointColumns; i++)
                {
                    Grid snapPointColumn = ((Grid)this.stackPanel.Children[i]);
                    bool isOccupied = false;
                    foreach (Rectangle child in snapPointColumn.Children)
                    {
                        double previousSnapPointMin = child.Margin.Top;
                        double previousSnapPointMax = child.Height + previousSnapPointMin;
                        if ((min >= previousSnapPointMin && min <= previousSnapPointMax) ||
                           (min < previousSnapPointMin && max >= previousSnapPointMin))
                        {
                            isOccupied = true;
                            break;
                        }
                    }
                    if (!isOccupied)
                    {
                        Rectangle rangeRectangle = new Rectangle();
                        rangeRectangle.Width = snapPointColumnWidth;
                        rangeRectangle.Height = max - min;
                        rangeRectangle.Margin = new Thickness(0, min, 0, 0);
                        rangeRectangle.Fill = new SolidColorBrush(fillColor);
                        rangeRectangle.VerticalAlignment = VerticalAlignment.Top;
                        snapPointColumn.Children.Add(rangeRectangle);

                        foreach (int value in values)
                        {
                            Rectangle pointRectangle = new Rectangle();
                            pointRectangle.Width = snapPointColumnWidth;
                            pointRectangle.Height = 1;
                            pointRectangle.Margin = new Thickness(0, value, 0, 0);
                            pointRectangle.Fill = new SolidColorBrush(Windows.UI.Colors.Black);
                            pointRectangle.VerticalAlignment = VerticalAlignment.Top;
                            snapPointColumn.Children.Add(pointRectangle);
                        }
                        return i;
                    }
                }
                this.fullLogs.Add("Ran out of room to display additional snap points.");
            }
            else
            {
                throw (new ArgumentException(string.Format("The following inequality must be true: min <= All Values <= max. {0} <= {1} <= {2}", min, values.ToString(), max)));
            }
            return -1;
        }

        private void FixConsolidatedView()
        {
            consolidatedView.Children.Clear();
            foreach (ScrollSnapPointBase snapPoint in ScrollPresenterTestHooks.GetConsolidatedVerticalScrollSnapPoints(markupScrollPresenter))
            {
                Vector2 zone = ScrollPresenterTestHooks.GetVerticalSnapPointActualApplicableZone(markupScrollPresenter, snapPoint);
                zone.X = Math.Max(0, zone.X);
                zone.Y = Math.Min(snapPointColumnHeight, zone.Y);
                Rectangle rangeRectangle = new Rectangle();
                rangeRectangle.Width = snapPointColumnWidth - 1;
                rangeRectangle.Height = zone.Y - zone.X;
                rangeRectangle.Margin = new Thickness(0, zone.X, 0, 0);
                rangeRectangle.Fill = new SolidColorBrush(ScrollPresenterTestHooks.GetSnapPointVisualizationColor(snapPoint));
                rangeRectangle.VerticalAlignment = VerticalAlignment.Top;
                consolidatedView.Children.Add(rangeRectangle);
            }
        }

        private double GetFirstRepeatedSnapPoint(double offset, double interval, double start)
        {
            Debug.Assert(offset >= start);
            Debug.Assert(interval > 0);

            return offset - (int)((offset - start) / interval) * interval;
        }

        private Color GetNewColor()
        {
            colorIndex++;
            switch (colorIndex)
            {
                case 0:
                    return Windows.UI.Colors.YellowGreen;
                case 1:
                    return Windows.UI.Colors.AliceBlue;
                case 2:
                    return Windows.UI.Colors.AntiqueWhite;
                case 3:
                    return Windows.UI.Colors.Aqua;
                case 4:
                    return Windows.UI.Colors.Aquamarine;
                case 5:
                    return Windows.UI.Colors.Azure;
                case 6:
                    return Windows.UI.Colors.Beige;
                case 7:
                    return Windows.UI.Colors.Bisque;
                case 8:
                    return Windows.UI.Colors.BlanchedAlmond;
                case 9:
                    return Windows.UI.Colors.Blue;
                case 10:
                    return Windows.UI.Colors.BlueViolet;
                case 11:
                    return Windows.UI.Colors.Brown;
                case 12:
                    return Windows.UI.Colors.BurlyWood;
                case 13:
                    return Windows.UI.Colors.CadetBlue;
                case 14:
                    return Windows.UI.Colors.Chartreuse;
                case 15:
                    return Windows.UI.Colors.Chocolate;
                case 16:
                    return Windows.UI.Colors.Coral;
                case 17:
                    return Windows.UI.Colors.CornflowerBlue;
                case 18:
                    return Windows.UI.Colors.Cornsilk;
                case 19:
                    return Windows.UI.Colors.Crimson;
                case 20:
                    return Windows.UI.Colors.Cyan;
                case 21:
                    return Windows.UI.Colors.DarkBlue;
                case 22:
                    return Windows.UI.Colors.DarkCyan;
                case 23:
                    return Windows.UI.Colors.DarkGoldenrod;
                case 24:
                    return Windows.UI.Colors.DarkGray;
                case 25:
                    return Windows.UI.Colors.DarkGreen;
                case 26:
                    return Windows.UI.Colors.DarkKhaki;
                case 27:
                    return Windows.UI.Colors.DarkMagenta;
                case 28:
                    return Windows.UI.Colors.DarkOliveGreen;
                case 29:
                    return Windows.UI.Colors.DarkOrange;
                case 30:
                    return Windows.UI.Colors.DarkOrchid;
                case 31:
                    return Windows.UI.Colors.DarkRed;
                case 32:
                    return Windows.UI.Colors.DarkSalmon;
                case 33:
                    return Windows.UI.Colors.DarkSeaGreen;
                case 34:
                    return Windows.UI.Colors.DarkSlateBlue;
                case 35:
                    return Windows.UI.Colors.DarkSlateGray;
                case 36:
                    return Windows.UI.Colors.DarkTurquoise;
                case 37:
                    return Windows.UI.Colors.DarkViolet;
                case 38:
                    return Windows.UI.Colors.DeepPink;
                case 39:
                    return Windows.UI.Colors.DeepSkyBlue;
                case 40:
                    return Windows.UI.Colors.DimGray;
                case 41:
                    return Windows.UI.Colors.DodgerBlue;
                case 42:
                    return Windows.UI.Colors.Firebrick;
                case 43:
                    return Windows.UI.Colors.FloralWhite;
                case 44:
                    return Windows.UI.Colors.ForestGreen;
                case 45:
                    return Windows.UI.Colors.Fuchsia;
                case 46:
                    return Windows.UI.Colors.Gainsboro;
                case 47:
                    return Windows.UI.Colors.GhostWhite;
                case 48:
                    return Windows.UI.Colors.Gold;
                case 49:
                    return Windows.UI.Colors.Goldenrod;
                case 50:
                    return Windows.UI.Colors.Gray;
                case 51:
                    return Windows.UI.Colors.Green;
                case 52:
                    return Windows.UI.Colors.GreenYellow;
                case 53:
                    return Windows.UI.Colors.Honeydew;
                case 54:
                    return Windows.UI.Colors.HotPink;
                case 55:
                    return Windows.UI.Colors.IndianRed;
                case 56:
                    return Windows.UI.Colors.Indigo;
                case 57:
                    return Windows.UI.Colors.Ivory;
                case 58:
                    return Windows.UI.Colors.Khaki;
                case 59:
                    return Windows.UI.Colors.Lavender;
                case 60:
                    return Windows.UI.Colors.LavenderBlush;
                case 61:
                    return Windows.UI.Colors.LawnGreen;
                case 62:
                    return Windows.UI.Colors.LemonChiffon;
                case 63:
                    return Windows.UI.Colors.LightBlue;
                case 64:
                    return Windows.UI.Colors.LightCoral;
                case 65:
                    return Windows.UI.Colors.LightCyan;
                case 66:
                    return Windows.UI.Colors.LightGoldenrodYellow;
                case 67:
                    return Windows.UI.Colors.LightGray;
                case 68:
                    return Windows.UI.Colors.LightGreen;
                case 69:
                    return Windows.UI.Colors.LightPink;
                case 70:
                    return Windows.UI.Colors.LightSalmon;
                case 71:
                    return Windows.UI.Colors.LightSeaGreen;
                case 72:
                    return Windows.UI.Colors.LightSkyBlue;
                case 73:
                    return Windows.UI.Colors.LightSlateGray;
                case 74:
                    return Windows.UI.Colors.LightSteelBlue;
                case 75:
                    return Windows.UI.Colors.LightYellow;
                case 76:
                    return Windows.UI.Colors.Lime;
                case 77:
                    return Windows.UI.Colors.LimeGreen;
                case 78:
                    return Windows.UI.Colors.Linen;
                case 79:
                    return Windows.UI.Colors.Magenta;
                case 80:
                    return Windows.UI.Colors.Maroon;
                case 81:
                    return Windows.UI.Colors.MediumAquamarine;
                case 82:
                    return Windows.UI.Colors.MediumBlue;
                case 83:
                    return Windows.UI.Colors.MediumOrchid;
                case 84:
                    return Windows.UI.Colors.MediumPurple;
                case 85:
                    return Windows.UI.Colors.MediumSeaGreen;
                case 86:
                    return Windows.UI.Colors.MediumSlateBlue;
                case 87:
                    return Windows.UI.Colors.MediumSpringGreen;
                case 88:
                    return Windows.UI.Colors.MediumTurquoise;
                case 89:
                    return Windows.UI.Colors.MediumVioletRed;
                case 90:
                    return Windows.UI.Colors.MidnightBlue;
                case 91:
                    return Windows.UI.Colors.MintCream;
                case 92:
                    return Windows.UI.Colors.MistyRose;
                case 93:
                    return Windows.UI.Colors.Moccasin;
                case 94:
                    return Windows.UI.Colors.NavajoWhite;
                case 95:
                    return Windows.UI.Colors.Navy;
                case 96:
                    return Windows.UI.Colors.OldLace;
                case 97:
                    return Windows.UI.Colors.Olive;
                case 98:
                    return Windows.UI.Colors.OliveDrab;
                case 99:
                    return Windows.UI.Colors.Orange;
                case 100:
                    return Windows.UI.Colors.OrangeRed;
                case 101:
                    return Windows.UI.Colors.Orchid;
                case 102:
                    return Windows.UI.Colors.PaleGoldenrod;
                case 103:
                    return Windows.UI.Colors.PaleGreen;
                case 104:
                    return Windows.UI.Colors.PaleTurquoise;
                case 105:
                    return Windows.UI.Colors.PaleVioletRed;
                case 106:
                    return Windows.UI.Colors.PapayaWhip;
                case 107:
                    return Windows.UI.Colors.PeachPuff;
                case 108:
                    return Windows.UI.Colors.Peru;
                case 109:
                    return Windows.UI.Colors.Pink;
                case 110:
                    return Windows.UI.Colors.Plum;
                case 111:
                    return Windows.UI.Colors.PowderBlue;
                case 112:
                    return Windows.UI.Colors.Purple;
                case 113:
                    return Windows.UI.Colors.Red;
                case 114:
                    return Windows.UI.Colors.RosyBrown;
                case 115:
                    return Windows.UI.Colors.RoyalBlue;
                case 116:
                    return Windows.UI.Colors.SaddleBrown;
                case 117:
                    return Windows.UI.Colors.Salmon;
                case 118:
                    return Windows.UI.Colors.SandyBrown;
                case 119:
                    return Windows.UI.Colors.SeaGreen;
                case 120:
                    return Windows.UI.Colors.SeaShell;
                case 121:
                    return Windows.UI.Colors.Sienna;
                case 122:
                    return Windows.UI.Colors.Silver;
                case 123:
                    return Windows.UI.Colors.SkyBlue;
                case 124:
                    return Windows.UI.Colors.SlateBlue;
                case 125:
                    return Windows.UI.Colors.SlateGray;
                case 126:
                    return Windows.UI.Colors.Snow;
                case 127:
                    return Windows.UI.Colors.SpringGreen;
                case 128:
                    return Windows.UI.Colors.Tan;
                case 129:
                    return Windows.UI.Colors.Teal;
                case 130:
                    return Windows.UI.Colors.Thistle;
                case 131:
                    return Windows.UI.Colors.Tomato;
                case 132:
                    return Windows.UI.Colors.Turquoise;
                case 133:
                    return Windows.UI.Colors.Violet;
                case 134:
                    return Windows.UI.Colors.Wheat;
                case 135:
                    return Windows.UI.Colors.WhiteSmoke;
                case 136:
                    return Windows.UI.Colors.Yellow;
                case 137:
                    return Windows.UI.Colors.YellowGreen;
                default:
                    return Windows.UI.Colors.Black;
            }
        }

        private void ChkLogScrollPresenterMessages_Checked(object sender, RoutedEventArgs e)
        {
            //Turn on info and verbose logging for the ScrollPresenter type:
            MUXControlsTestHooks.SetLoggingLevelForType("ScrollPresenter", isLoggingInfoLevel: true, isLoggingVerboseLevel: true);

            MUXControlsTestHooks.LoggingMessage += MUXControlsTestHooks_LoggingMessage;
        }

        private void ChkLogScrollPresenterMessages_Unchecked(object sender, RoutedEventArgs e)
        {
            //Turn off info and verbose logging for the ScrollPresenter type:
            MUXControlsTestHooks.SetLoggingLevelForType("ScrollPresenter", isLoggingInfoLevel: false, isLoggingVerboseLevel: false);

            MUXControlsTestHooks.LoggingMessage -= MUXControlsTestHooks_LoggingMessage;
        }

        private void MUXControlsTestHooks_LoggingMessage(object sender, MUXControlsTestHooksLoggingMessageEventArgs args)
        {
            // Cut off the terminating new line.
            string msg = args.Message.Substring(0, args.Message.Length - 1);
            string senderName = string.Empty;
            FrameworkElement fe = sender as FrameworkElement;

            if (fe != null)
            {
                senderName = "s:" + fe.Name + ", ";
            }

            if (args.IsVerboseLevel)
            {
                this.fullLogs.Add("Verbose: " + senderName + "m:" + msg);
            }
            else
            {
                this.fullLogs.Add("Info: " + senderName + "m:" + msg);
            }
        }

        private void btnGetFullLog_Click(object sender, RoutedEventArgs e)
        {
            foreach (string log in this.fullLogs)
            {
                this.cmbFullLog.Items.Add(log);
            }
        }

        private void btnClearFullLog_Click(object sender, RoutedEventArgs e)
        {
            this.fullLogs.Clear();
            this.cmbFullLog.Items.Clear();
        }
    }
}

