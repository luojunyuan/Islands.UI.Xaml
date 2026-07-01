// Shims for WinUI 2 / MUX helper types used in ScrollPresenter TestUI pages.
// These are lightweight stand-ins that let the pages compile and navigate.

using System.Collections.Generic;
using System.Collections.Specialized;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace MUXControlsTestApp.Utilities
{
    // TilePanel is a custom panel from MUXControlsTestApp used in ScrollPresenter dynamic test page.
    public sealed class TilePanel : Panel
    {
        public int TileCount { get; set; } = 10;

        protected override Windows.Foundation.Size MeasureOverride(Windows.Foundation.Size availableSize)
        {
            foreach (UIElement child in Children)
                child.Measure(availableSize);
            return new Windows.Foundation.Size(200, 200);
        }

        protected override Windows.Foundation.Size ArrangeOverride(Windows.Foundation.Size finalSize)
        {
            double x = 0, y = 0, rowH = 0;
            foreach (UIElement child in Children)
            {
                child.Arrange(new Windows.Foundation.Rect(x, y, child.DesiredSize.Width, child.DesiredSize.Height));
                x += child.DesiredSize.Width;
                rowH = System.Math.Max(rowH, child.DesiredSize.Height);
            }
            return finalSize;
        }
    }
}

namespace MUXControlsTestApp
{
    // Stub for ItemsRepeater custom data source used in ScrollPresenter BringIntoView/RepeaterAnchoring pages.
    // Mirrors the WinUI2 ItemsSourceView+UniqueIdMapping abstract contract.
    public abstract class CustomItemsSourceViewWithUniqueIdMapping
    {
        public int Count => GetSizeCore();

        public object GetAt(int index) => GetAtCore(index);

        protected abstract int GetSizeCore();
        protected abstract object GetAtCore(int index);
        protected abstract string KeyFromIndexCore(int index);

        protected string KeyFromIndex(int index) => KeyFromIndexCore(index);

        protected void OnItemsSourceChanged(object args)
        {
        }
    }

    public static class CollectionChangeEventArgsConverters
    {
        public static object CreateNotifyArgs(
            NotifyCollectionChangedAction action,
            int oldStartingIndex,
            int oldItemsCount,
            int newStartingIndex,
            int newItemsCount)
        {
            return new
            {
                Action = action,
                OldStartingIndex = oldStartingIndex,
                OldItemsCount = oldItemsCount,
                NewStartingIndex = newStartingIndex,
                NewItemsCount = newItemsCount
            };
        }
    }
}
