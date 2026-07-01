// Shims for WEX test infrastructure and MUXControlsTestApp base types,
// allowing the shared TestUI .projitems to compile without the original WEX/TAEF packages.

using System;
using System.Diagnostics;
using Windows.UI.Xaml.Controls;

namespace MUXControlsTestApp
{
    public class TestPage : Page { }

    [AttributeUsage(AttributeTargets.Class)]
    public sealed class TopLevelTestPageAttribute : Attribute
    {
        public string Name { get; set; } = "";
        public string Icon { get; set; } = "";
    }
}

namespace WEX.Logging.Interop
{
    public static class Log
    {
        public static void Comment(string message) => Debug.WriteLine($"[LOG] {message}");
        public static void Warning(string message) => Debug.WriteLine($"[WARN] {message}");
        public static void Error(string message) => Debug.WriteLine($"[ERROR] {message}");
    }

    public static class LogController
    {
        public static void InitializeLogging() { }
    }
}

namespace WEX.TestExecution
{
    public static class Verify
    {
        public static void IsNotNull(object? obj, string message = "") { }
        public static void IsNull(object? obj, string message = "") { }
        public static void IsTrue(bool condition, string message = "") { }
        public static void IsFalse(bool condition, string message = "") { }
        public static void AreEqual<T>(T expected, T actual, string message = "") { }
        public static void AreNotEqual<T>(T expected, T actual, string message = "") { }
        public static void IsGreaterThan(double actual, double expected, string message = "") { }
        public static void IsLessThan(double actual, double expected, string message = "") { }
        public static void Fail(string message = "") => throw new InvalidOperationException(message);
    }
}

namespace WEX.TestExecution.Markup
{
    [AttributeUsage(AttributeTargets.Class)] public sealed class TestClassAttribute : Attribute { }
    [AttributeUsage(AttributeTargets.Method)] public sealed class TestMethodAttribute : Attribute { }
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Class, AllowMultiple = true)]
    public sealed class TestPropertyAttribute : Attribute
    {
        public TestPropertyAttribute(string name, string value) { }
    }
    [AttributeUsage(AttributeTargets.Method)] public sealed class TestInitializeAttribute : Attribute { }
    [AttributeUsage(AttributeTargets.Method)] public sealed class TestCleanupAttribute : Attribute { }
    [AttributeUsage(AttributeTargets.Method)] public sealed class ClassInitializeAttribute : Attribute { }
    [AttributeUsage(AttributeTargets.Method)] public sealed class ClassCleanupAttribute : Attribute { }

    public class TestContext { }
}

namespace Common
{
    public static class PlatformConfiguration
    {
        public static bool IsOsVersionGreaterThan(int major, int minor = 0, int build = 0, int revision = 0) => true;
        public static bool IsOsVersionGreaterThanOrEqual(int major, int minor = 0, int build = 0, int revision = 0) => true;
        public static bool IsDevice(DeviceType type) => type == DeviceType.Desktop;
    }

    public enum DeviceType { Desktop, Phone, IoT, Xbox }

    public sealed class PrivateLoggingHelper : IDisposable
    {
        public PrivateLoggingHelper(params string[] types) { }
        public void Dispose() { }
    }
}
