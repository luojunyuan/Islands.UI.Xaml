export module ixx.ResourceAccessor;

import inc.common;

export
{
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using PCWSTR = const wchar_t*;

/// <summary>
/// Resource Accessor
/// </summary>
class ResourceAccessor sealed
{
private:
    /// <summary>
    /// Declare a private constructor to prevent instance creation.
    /// </summary>
    ResourceAccessor() = delete;

    /// <summary>
    /// String containing the resource location
    /// </summary>
    static PCWSTR c_resourceLoc;
    static PCWSTR c_assetLoc;
    static PCWSTR c_resourceLocWinUI;

    static winrt::Windows::ApplicationModel::Resources::Core::ResourceMap GetAssetMap();
    static winrt::Windows::ApplicationModel::Resources::Core::ResourceMap GetResourceMap();
    static winrt::Windows::ApplicationModel::Resources::Core::ResourceManager GetResourceManagerImpl();
    static winrt::Windows::ApplicationModel::Resources::Core::ResourceManager GetResourceManager();
    static winrt::Windows::ApplicationModel::Resources::Core::ResourceContext GetResourceContext();
    static winrt::Windows::ApplicationModel::Resources::Core::ResourceManager m_resourceManagerWinRT;
public:
    static winrt::hstring GetLocalizedStringResource(const wstring_view &resourceName);
    static winrt::LoadedImageSurface GetImageSurface(const wstring_view &assetName, winrt::Size imageSize);
    static winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> GetFileContents(const wstring_view& assetFileName);
    static winrt::IInspectable ResourceLookup(const winrt::Control& control, const winrt::IInspectable& key);

    static bool IsResourceIdNull(ResourceIdType resourceId)
    {
        return resourceId.size() == 0;
    }
};

inline constexpr std::wstring_view SR_BasicRatingString{ L"BasicRatingString" };
inline constexpr std::wstring_view SR_CommunityRatingString{ L"CommunityRatingString" };
inline constexpr std::wstring_view SR_RatingsControlName{ L"RatingsControlName" };
inline constexpr std::wstring_view SR_RatingControlName{ L"RatingControlName" };
inline constexpr std::wstring_view SR_RatingUnset{ L"RatingUnset" };
inline constexpr std::wstring_view SR_NavigationButtonToggleName{ L"NavigationButtonToggleName" };
inline constexpr std::wstring_view SR_NavigationButtonClosedName{ L"NavigationButtonClosedName" };
inline constexpr std::wstring_view SR_NavigationButtonOpenName{ L"NavigationButtonOpenName" };
inline constexpr std::wstring_view SR_NavigationViewItemDefaultControlName{ L"NavigationViewItemDefaultControlName" };
inline constexpr std::wstring_view SR_NavigationBackButtonName{ L"NavigationBackButtonName" };
inline constexpr std::wstring_view SR_NavigationBackButtonToolTip{ L"NavigationBackButtonToolTip" };
inline constexpr std::wstring_view SR_NavigationCloseButtonName{ L"NavigationCloseButtonName" };
inline constexpr std::wstring_view SR_NavigationOverflowButtonName{ L"NavigationOverflowButtonName" };
inline constexpr std::wstring_view SR_NavigationOverflowButtonText{ L"NavigationOverflowButtonText" };
inline constexpr std::wstring_view SR_NavigationOverflowButtonToolTip{ L"NavigationOverflowButtonToolTip" };
inline constexpr std::wstring_view SR_SettingsButtonName{ L"SettingsButtonName" };
inline constexpr std::wstring_view SR_NavigationViewSearchButtonName{ L"NavigationViewSearchButtonName" };
inline constexpr std::wstring_view SR_TextAlphaLabel{ L"TextAlphaLabel" };
inline constexpr std::wstring_view SR_AutomationNameAlphaSlider{ L"AutomationNameAlphaSlider" };
inline constexpr std::wstring_view SR_AutomationNameAlphaTextBox{ L"AutomationNameAlphaTextBox" };
inline constexpr std::wstring_view SR_AutomationNameHueSlider{ L"AutomationNameHueSlider" };
inline constexpr std::wstring_view SR_AutomationNameSaturationSlider{ L"AutomationNameSaturationSlider" };
inline constexpr std::wstring_view SR_AutomationNameValueSlider{ L"AutomationNameValueSlider" };
inline constexpr std::wstring_view SR_TextBlueLabel{ L"TextBlueLabel" };
inline constexpr std::wstring_view SR_AutomationNameBlueTextBox{ L"AutomationNameBlueTextBox" };
inline constexpr std::wstring_view SR_AutomationNameColorModelComboBox{ L"AutomationNameColorModelComboBox" };
inline constexpr std::wstring_view SR_AutomationNameColorSpectrum{ L"AutomationNameColorSpectrum" };
inline constexpr std::wstring_view SR_TextGreenLabel{ L"TextGreenLabel" };
inline constexpr std::wstring_view SR_AutomationNameGreenTextBox{ L"AutomationNameGreenTextBox" };
inline constexpr std::wstring_view SR_HelpTextColorSpectrum{ L"HelpTextColorSpectrum" };
inline constexpr std::wstring_view SR_AutomationNameRGBHexTextBox{ L"AutomationNameRGBHexTextBox" };
inline constexpr std::wstring_view SR_AutomationNameHSVHexTextBox{ L"AutomationNameHSVHexTextBox" };
inline constexpr std::wstring_view SR_ContentHSVComboBoxItem{ L"ContentHSVComboBoxItem" };
inline constexpr std::wstring_view SR_TextHueLabel{ L"TextHueLabel" };
inline constexpr std::wstring_view SR_AutomationNameHueTextBox{ L"AutomationNameHueTextBox" };
inline constexpr std::wstring_view SR_LocalizedControlTypeColorSpectrum{ L"LocalizedControlTypeColorSpectrum" };
inline constexpr std::wstring_view SR_TextRedLabel{ L"TextRedLabel" };
inline constexpr std::wstring_view SR_AutomationNameRedTextBox{ L"AutomationNameRedTextBox" };
inline constexpr std::wstring_view SR_ContentRGBComboBoxItem{ L"ContentRGBComboBoxItem" };
inline constexpr std::wstring_view SR_TextSaturationLabel{ L"TextSaturationLabel" };
inline constexpr std::wstring_view SR_AutomationNameSaturationTextBox{ L"AutomationNameSaturationTextBox" };
inline constexpr std::wstring_view SR_TextValueLabel{ L"TextValueLabel" };
inline constexpr std::wstring_view SR_ValueStringColorSpectrumWithColorName{ L"ValueStringColorSpectrumWithColorName" };
inline constexpr std::wstring_view SR_ValueStringColorSpectrumWithoutColorName{ L"ValueStringColorSpectrumWithoutColorName" };
inline constexpr std::wstring_view SR_ValueStringHueSliderWithColorName{ L"ValueStringHueSliderWithColorName" };
inline constexpr std::wstring_view SR_ValueStringHueSliderWithoutColorName{ L"ValueStringHueSliderWithoutColorName" };
inline constexpr std::wstring_view SR_ValueStringSaturationSliderWithColorName{ L"ValueStringSaturationSliderWithColorName" };
inline constexpr std::wstring_view SR_ValueStringSaturationSliderWithoutColorName{ L"ValueStringSaturationSliderWithoutColorName" };
inline constexpr std::wstring_view SR_ValueStringValueSliderWithColorName{ L"ValueStringValueSliderWithColorName" };
inline constexpr std::wstring_view SR_ValueStringValueSliderWithoutColorName{ L"ValueStringValueSliderWithoutColorName" };
inline constexpr std::wstring_view SR_AutomationNameValueTextBox{ L"AutomationNameValueTextBox" };
inline constexpr std::wstring_view SR_ToolTipStringAlphaSlider{ L"ToolTipStringAlphaSlider" };
inline constexpr std::wstring_view SR_ToolTipStringHueSliderWithColorName{ L"ToolTipStringHueSliderWithColorName" };
inline constexpr std::wstring_view SR_ToolTipStringHueSliderWithoutColorName{ L"ToolTipStringHueSliderWithoutColorName" };
inline constexpr std::wstring_view SR_ToolTipStringSaturationSliderWithColorName{ L"ToolTipStringSaturationSliderWithColorName" };
inline constexpr std::wstring_view SR_ToolTipStringSaturationSliderWithoutColorName{ L"ToolTipStringSaturationSliderWithoutColorName" };
inline constexpr std::wstring_view SR_ToolTipStringValueSliderWithColorName{ L"ToolTipStringValueSliderWithColorName" };
inline constexpr std::wstring_view SR_ToolTipStringValueSliderWithoutColorName{ L"ToolTipStringValueSliderWithoutColorName" };
inline constexpr std::wstring_view SR_AutomationNameMoreButtonCollapsed{ L"AutomationNameMoreButtonCollapsed" };
inline constexpr std::wstring_view SR_AutomationNameMoreButtonExpanded{ L"AutomationNameMoreButtonExpanded" };
inline constexpr std::wstring_view SR_HelpTextMoreButton{ L"HelpTextMoreButton" };
inline constexpr std::wstring_view SR_TextMoreButtonLabelCollapsed{ L"TextMoreButtonLabelCollapsed" };
inline constexpr std::wstring_view SR_TextMoreButtonLabelExpanded{ L"TextMoreButtonLabelExpanded" };
inline constexpr std::wstring_view SR_BadgeItemPlural1{ L"BadgeItemPlural1" };
inline constexpr std::wstring_view SR_BadgeItemPlural2{ L"BadgeItemPlural2" };
inline constexpr std::wstring_view SR_BadgeItemPlural3{ L"BadgeItemPlural3" };
inline constexpr std::wstring_view SR_BadgeItemPlural4{ L"BadgeItemPlural4" };
inline constexpr std::wstring_view SR_BadgeItemPlural5{ L"BadgeItemPlural5" };
inline constexpr std::wstring_view SR_BadgeItemPlural6{ L"BadgeItemPlural6" };
inline constexpr std::wstring_view SR_BadgeItemPlural7{ L"BadgeItemPlural7" };
inline constexpr std::wstring_view SR_BadgeItemSingular{ L"BadgeItemSingular" };
inline constexpr std::wstring_view SR_BadgeItemTextOverride{ L"BadgeItemTextOverride" };
inline constexpr std::wstring_view SR_BadgeIcon{ L"BadgeIcon" };
inline constexpr std::wstring_view SR_BadgeIconTextOverride{ L"BadgeIconTextOverride" };
inline constexpr std::wstring_view SR_PersonName{ L"PersonName" };
inline constexpr std::wstring_view SR_GroupName{ L"GroupName" };
inline constexpr std::wstring_view SR_CancelDraggingString{ L"CancelDraggingString" };
inline constexpr std::wstring_view SR_DefaultItemString{ L"DefaultItemString" };
inline constexpr std::wstring_view SR_DropIntoNodeString{ L"DropIntoNodeString" };
inline constexpr std::wstring_view SR_FallBackPlaceString{ L"FallBackPlaceString" };
inline constexpr std::wstring_view SR_PagerControlPageTextName{ L"PagerControlPageText" };
inline constexpr std::wstring_view SR_PagerControlPrefixTextName{ L"PagerControlPrefixText" };
inline constexpr std::wstring_view SR_PagerControlSuffixTextName{ L"PagerControlSuffixText" };
inline constexpr std::wstring_view SR_PagerControlFirstPageButtonTextName{ L"PagerControlFirstPageButtonText" };
inline constexpr std::wstring_view SR_PagerControlPreviousPageButtonTextName{ L"PagerControlPreviousPageButtonText" };
inline constexpr std::wstring_view SR_PagerControlNextPageButtonTextName{ L"PagerControlNextPageButtonText" };
inline constexpr std::wstring_view SR_PagerControlLastPageButtonTextName{ L"PagerControlLastPageButtonText" };
inline constexpr std::wstring_view SR_PipsPagerNameText{ L"PipsPagerNameText" };
inline constexpr std::wstring_view SR_PipsPagerNextPageButtonText{ L"PipsPagerNextPageButtonText" };
inline constexpr std::wstring_view SR_PipsPagerPreviousPageButtonText{ L"PipsPagerPreviousPageButtonText" };
inline constexpr std::wstring_view SR_PipsPagerPageText{ L"PipsPagerPageText" };
inline constexpr std::wstring_view SR_PlaceAfterString{ L"PlaceAfterString" };
inline constexpr std::wstring_view SR_PlaceBeforeString{ L"PlaceBeforeString" };
inline constexpr std::wstring_view SR_PlaceBetweenString{ L"PlaceBetweenString" };
inline constexpr std::wstring_view SR_ProgressRingName{ L"ProgressRingName" };
inline constexpr std::wstring_view SR_ProgressRingIndeterminateStatus{ L"ProgressRingIndeterminateStatus" };
inline constexpr std::wstring_view SR_ProgressBarIndeterminateStatus{ L"ProgressBarIndeterminateStatus" };
inline constexpr std::wstring_view SR_ProgressBarPausedStatus{ L"ProgressBarPausedStatus" };
inline constexpr std::wstring_view SR_ProgressBarErrorStatus{ L"ProgressBarErrorStatus" };
inline constexpr std::wstring_view SR_RatingLocalizedControlType{ L"RatingLocalizedControlType" };
inline constexpr std::wstring_view SR_BreadcrumbBarItemLocalizedControlType{ L"BreadcrumbBarItemLocalizedControlType" };
inline constexpr std::wstring_view SR_SplitButtonSecondaryButtonName{ L"SplitButtonSecondaryButtonName" };
inline constexpr std::wstring_view SR_ProofingMenuItemLabel{ L"ProofingMenuItemLabel" };
inline constexpr std::wstring_view SR_TextCommandLabelCut{ L"TextCommandLabelCut" };
inline constexpr std::wstring_view SR_TextCommandLabelCopy{ L"TextCommandLabelCopy" };
inline constexpr std::wstring_view SR_TextCommandLabelPaste{ L"TextCommandLabelPaste" };
inline constexpr std::wstring_view SR_TextCommandLabelSelectAll{ L"TextCommandLabelSelectAll" };
inline constexpr std::wstring_view SR_TextCommandLabelBold{ L"TextCommandLabelBold" };
inline constexpr std::wstring_view SR_TextCommandLabelItalic{ L"TextCommandLabelItalic" };
inline constexpr std::wstring_view SR_TextCommandLabelUnderline{ L"TextCommandLabelUnderline" };
inline constexpr std::wstring_view SR_TextCommandLabelUndo{ L"TextCommandLabelUndo" };
inline constexpr std::wstring_view SR_TextCommandLabelRedo{ L"TextCommandLabelRedo" };
inline constexpr std::wstring_view SR_TextCommandDescriptionCut{ L"TextCommandDescriptionCut" };
inline constexpr std::wstring_view SR_TextCommandDescriptionCopy{ L"TextCommandDescriptionCopy" };
inline constexpr std::wstring_view SR_TextCommandDescriptionPaste{ L"TextCommandDescriptionPaste" };
inline constexpr std::wstring_view SR_TextCommandDescriptionSelectAll{ L"TextCommandDescriptionSelectAll" };
inline constexpr std::wstring_view SR_TextCommandDescriptionBold{ L"TextCommandDescriptionBold" };
inline constexpr std::wstring_view SR_TextCommandDescriptionItalic{ L"TextCommandDescriptionItalic" };
inline constexpr std::wstring_view SR_TextCommandDescriptionUnderline{ L"TextCommandDescriptionUnderline" };
inline constexpr std::wstring_view SR_TextCommandDescriptionUndo{ L"TextCommandDescriptionUndo" };
inline constexpr std::wstring_view SR_TextCommandDescriptionRedo{ L"TextCommandDescriptionRedo" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyCut{ L"TextCommandKeyboardAcceleratorKeyCut" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyCopy{ L"TextCommandKeyboardAcceleratorKeyCopy" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyPaste{ L"TextCommandKeyboardAcceleratorKeyPaste" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeySelectAll{ L"TextCommandKeyboardAcceleratorKeySelectAll" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyBold{ L"TextCommandKeyboardAcceleratorKeyBold" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyItalic{ L"TextCommandKeyboardAcceleratorKeyItalic" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyUnderline{ L"TextCommandKeyboardAcceleratorKeyUnderline" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyUndo{ L"TextCommandKeyboardAcceleratorKeyUndo" };
inline constexpr std::wstring_view SR_TextCommandKeyboardAcceleratorKeyRedo{ L"TextCommandKeyboardAcceleratorKeyRedo" };
inline constexpr std::wstring_view SR_TeachingTipAlternateCloseButtonName{ L"TeachingTipAlternateCloseButtonName" };
inline constexpr std::wstring_view SR_TeachingTipAlternateCloseButtonTooltip{ L"TeachingTipAlternateCloseButtonTooltip" };
inline constexpr std::wstring_view SR_TeachingTipCustomLandmarkName{ L"TeachingTipCustomLandmarkName" };
inline constexpr std::wstring_view SR_TeachingTipNotification{ L"TeachingTipNotification" };
inline constexpr std::wstring_view SR_TeachingTipNotificationWithoutAppName{ L"TeachingTipNotificationWithoutAppName" };
inline constexpr std::wstring_view SR_TabViewAddButtonName{ L"TabViewAddButtonName" };
inline constexpr std::wstring_view SR_TabViewAddButtonTooltip{ L"TabViewAddButtonTooltip" };
inline constexpr std::wstring_view SR_TabViewCloseButtonName{ L"TabViewCloseButtonName" };
inline constexpr std::wstring_view SR_TabViewCloseButtonTooltip{ L"TabViewCloseButtonTooltip" };
inline constexpr std::wstring_view SR_TabViewCloseButtonTooltipWithKA{ L"TabViewCloseButtonTooltipWithKA" };
inline constexpr std::wstring_view SR_TabViewScrollDecreaseButtonTooltip{ L"TabViewScrollDecreaseButtonTooltip" };
inline constexpr std::wstring_view SR_TabViewScrollIncreaseButtonTooltip{ L"TabViewScrollIncreaseButtonTooltip" };
inline constexpr std::wstring_view SR_TabViewNewTabAddedNotification{ L"TabViewNewTabAddedNotification" };
inline constexpr std::wstring_view SR_NumberBoxUpSpinButtonName{ L"NumberBoxUpSpinButtonName" };
inline constexpr std::wstring_view SR_NumberBoxDownSpinButtonName{ L"NumberBoxDownSpinButtonName" };
inline constexpr std::wstring_view SR_NumberBoxMaximumValueStatus{ L"NumberBoxMaximumValueStatus" };
inline constexpr std::wstring_view SR_NumberBoxMinimumValueStatus{ L"NumberBoxMinimumValueStatus" };
inline constexpr std::wstring_view SR_ExpanderDefaultControlName{ L"ExpanderDefaultControlName" };
inline constexpr std::wstring_view SR_ItemContainerDefaultControlName{ L"ItemContainerDefaultControlName" };
inline constexpr std::wstring_view SR_SelectorBarItemDefaultControlName{ L"SelectorBarItemDefaultControlName" };
inline constexpr std::wstring_view SR_InfoBarCloseButtonName{ L"InfoBarCloseButtonName" };
inline constexpr std::wstring_view SR_InfoBarOpenedNotification{ L"InfoBarOpenedNotification" };
inline constexpr std::wstring_view SR_InfoBarClosedNotification{ L"InfoBarClosedNotification" };
inline constexpr std::wstring_view SR_InfoBarCustomLandmarkName{ L"InfoBarCustomLandmarkName" };
inline constexpr std::wstring_view SR_InfoBarCloseButtonTooltip{ L"InfoBarCloseButtonTooltip" };
inline constexpr std::wstring_view SR_InfoBarSeverityInformationalName{ L"InfoBarSeverityInformationalName" };
inline constexpr std::wstring_view SR_InfoBarSeveritySuccessName{ L"InfoBarSeveritySuccessName" };
inline constexpr std::wstring_view SR_InfoBarSeverityWarningName{ L"InfoBarSeverityWarningName" };
inline constexpr std::wstring_view SR_InfoBarSeverityErrorName{ L"InfoBarSeverityErrorName" };
inline constexpr std::wstring_view SR_InfoBarIconSeverityInformationalName{ L"InfoBarIconSeverityInformationalName" };
inline constexpr std::wstring_view SR_InfoBarIconSeveritySuccessName{ L"InfoBarIconSeveritySuccessName" };
inline constexpr std::wstring_view SR_InfoBarIconSeverityWarningName{ L"InfoBarIconSeverityWarningName" };
inline constexpr std::wstring_view SR_InfoBarIconSeverityErrorName{ L"InfoBarIconSeverityErrorName" };
inline constexpr std::wstring_view SR_AutomationNameEllipsisBreadcrumbBarItem{ L"AutomationNameEllipsisBreadcrumbBarItem" };
inline constexpr std::wstring_view SR_CommandBarFlyoutCommandBarLocalizedControlType{ L"CommandBarFlyoutCommandBarLocalizedControlType" };
inline constexpr std::wstring_view SR_CommandBarFlyoutAppBarButtonLocalizedControlType{ L"CommandBarFlyoutAppBarButtonLocalizedControlType" };
inline constexpr std::wstring_view SR_CommandBarFlyoutAppBarToggleButtonLocalizedControlType{ L"CommandBarFlyoutAppBarToggleButtonLocalizedControlType" };
inline constexpr std::wstring_view SR_WarningSuitableWebView2NotFound{ L"WarningSuitableWebView2NotFound" };
inline constexpr std::wstring_view SR_DownloadWebView2Runtime{ L"DownloadWebView2Runtime" };
inline constexpr std::wstring_view IR_NoiseAsset_256X256_PNG{ L"NoiseAsset_256X256_PNG" };
inline constexpr std::wstring_view FR_Map_Html{ L"map.html" };
}
