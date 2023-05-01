object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1055#1086#1080#1089#1082' '#1089#1080#1075#1085#1072#1090#1091#1088
  ClientHeight = 521
  ClientWidth = 480
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object VirtualStringTree: TVirtualStringTree
    Left = 16
    Top = 37
    Width = 441
    Height = 414
    Colors.BorderColor = 15987699
    Colors.DisabledColor = clGray
    Colors.DropMarkColor = 15385233
    Colors.DropTargetColor = 15385233
    Colors.DropTargetBorderColor = 15385233
    Colors.FocusedSelectionColor = 15385233
    Colors.FocusedSelectionBorderColor = 15385233
    Colors.GridLineColor = 15987699
    Colors.HeaderHotColor = clBlack
    Colors.HotColor = clBlack
    Colors.SelectionRectangleBlendColor = 15385233
    Colors.SelectionRectangleBorderColor = 15385233
    Colors.SelectionTextColor = clBlack
    Colors.TreeLineColor = 9471874
    Colors.UnfocusedColor = clGray
    Colors.UnfocusedSelectionColor = clWhite
    Colors.UnfocusedSelectionBorderColor = clWhite
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnGetText = VirtualStringTreeGetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = #1053#1086#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072
        Width = 124
      end
      item
        Position = 1
        Text = #1058#1080#1087' '#1092#1072#1081#1083#1072
        Width = 135
      end>
  end
  object ProgressBar: TProgressBar
    Left = 16
    Top = 457
    Width = 441
    Height = 25
    TabOrder = 1
    Visible = False
  end
  object SearchButton: TButton
    Left = 16
    Top = 457
    Width = 441
    Height = 25
    Caption = #1053#1072#1081#1090#1080
    Enabled = False
    TabOrder = 2
    OnClick = SearchButtonClick
  end
  object StopButton: TButton
    Left = 16
    Top = 488
    Width = 441
    Height = 25
    Caption = #1047#1072#1074#1077#1088#1096#1080#1090#1100' '#1087#1086#1080#1089#1082
    Enabled = False
    TabOrder = 3
    OnClick = StopButtonClick
  end
  object VolumeBox: TComboBox
    Left = 16
    Top = 8
    Width = 441
    Height = 23
    TabOrder = 4
    Text = #1042#1099#1073#1077#1088#1080#1090#1077' '#1083#1086#1075#1080#1095#1077#1089#1082#1080#1081' '#1090#1086#1084' '#1076#1083#1103' '#1087#1086#1080#1089#1082#1072' '#1089#1080#1075#1085#1072#1090#1091#1088'...'
    OnSelect = VolumeBoxSelect
  end
end
