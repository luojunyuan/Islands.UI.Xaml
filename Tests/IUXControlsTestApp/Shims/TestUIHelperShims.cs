// Shims for WinUI 2 / MUX helper types used in ScrollPresenter TestUI pages.
// These are lightweight stand-ins that let the pages compile and navigate.

using System.Collections.Generic;
using System.Collections.Specialized;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace MUXControlsTestApp.Utilities
{
    // TilePanel is a custom panel from MUXControlsTestApp used in ScrollPresenter dynamic test page.
    public sealed partial class TilePanel : Panel
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
    // Mirrors the WinUI2 CustomItemsSourceView + UniqueIdMapping contract.
    // ItemsRepeater requires IList (for indexed access/count) and INotifyCollectionChanged.
    // IKeyIndexMapping comes from Microsoft.UI.Xaml.Controls and enables unique-key lookup.
    public abstract class CustomItemsSourceViewWithUniqueIdMapping
        : System.Collections.IList,
          System.Collections.Specialized.INotifyCollectionChanged,
          Microsoft.UI.Xaml.Controls.IKeyIndexMapping
    {
        // ── IList ──────────────────────────────────────────────────────────────
        public int Count => GetSizeCore();
        public object this[int index]
        {
            get => GetAtCore(index);
            set => throw new NotImplementedException();
        }
        public bool IsFixedSize => false;
        public bool IsReadOnly  => true;
        public bool IsSynchronized => false;
        public object SyncRoot => this;

        public int  Add(object value)           => throw new NotImplementedException();
        public void Clear()                     => throw new NotImplementedException();
        public bool Contains(object value)      => throw new NotImplementedException();
        public int  IndexOf(object value)       => throw new NotImplementedException();
        public void Insert(int index, object v) => throw new NotImplementedException();
        public void Remove(object value)        => throw new NotImplementedException();
        public void RemoveAt(int index)         => throw new NotImplementedException();
        public void CopyTo(Array array, int i)  => throw new NotImplementedException();

        public System.Collections.IEnumerator GetEnumerator()
        {
            for (int i = 0; i < Count; i++)
                yield return GetAtCore(i);
        }

        // ── INotifyCollectionChanged ───────────────────────────────────────────
        public event System.Collections.Specialized.NotifyCollectionChangedEventHandler CollectionChanged;

        protected void OnItemsSourceChanged(System.Collections.Specialized.NotifyCollectionChangedEventArgs args)
            => CollectionChanged?.Invoke(this, args);

        // ── IKeyIndexMapping ──────────────────────────────────────────────────
        public string KeyFromIndex(int index)   => KeyFromIndexCore(index);
        public int    IndexFromKey(string key)  => IndexFromKeyCore(key);

        // ── Abstract core methods ─────────────────────────────────────────────
        protected abstract int    GetSizeCore();
        protected abstract object GetAtCore(int index);
        protected abstract string KeyFromIndexCore(int index);
        protected virtual  int    IndexFromKeyCore(string key) => throw new NotImplementedException();
    }

    public static class CollectionChangeEventArgsConverters
    {
        public static System.Collections.Specialized.NotifyCollectionChangedEventArgs CreateNotifyArgs(
            NotifyCollectionChangedAction action,
            int oldStartingIndex,
            int oldItemsCount,
            int newStartingIndex,
            int newItemsCount)
        {
            if (action == NotifyCollectionChangedAction.Reset)
                return new System.Collections.Specialized.NotifyCollectionChangedEventArgs(action);
            if (action == NotifyCollectionChangedAction.Add)
                return new System.Collections.Specialized.NotifyCollectionChangedEventArgs(
                    action, new System.Collections.Generic.List<object>(newItemsCount), newStartingIndex);
            if (action == NotifyCollectionChangedAction.Remove)
                return new System.Collections.Specialized.NotifyCollectionChangedEventArgs(
                    action, new System.Collections.Generic.List<object>(oldItemsCount), oldStartingIndex);
            return new System.Collections.Specialized.NotifyCollectionChangedEventArgs(action);
        }
    }
}
