# $Id: tvision.rb,v 1.7 2002/03/04 07:11:13 t-peters Exp $

# tvision-ruby is a ruby wrapper for the text-mode application framework
# developed by Borland.
# Copyright (C) 2002 Tobias Peters <t-peters@users.berlios.de>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.

require "tvision.so"

module TVision

  # Event codes
  EvMouseDown = 0x0001;
  EvMouseUp   = 0x0002;
  EvMouseMove = 0x0004;
  EvMouseAuto = 0x0008;
  EvKeyDown   = 0x0010;
  EvCommand   = 0x0100;
  EvBroadcast = 0x0200;

  # Event masks

  EvNothing   = 0x0000;
  EvMouse     = 0x000f;
  EvKeyboard  = 0x0010;
  EvMessage   = 0xFF00;

  # Mouse button state masks

  MbLeftButton  = 0x01;
  MbRightButton = 0x02;
  MbMiddleButton= 0x04


  #  Standard command codes
  CmValid         = 0
  CmQuit          = 1
  CmError         = 2
  CmMenu          = 3
  CmClose         = 4
  CmZoom          = 5
  CmResize        = 6
  CmNext          = 7
  CmPrev          = 8
  CmHelp          = 9

  # TDialog standard commands

  CmOK            = 10
  CmCancel        = 11
  CmYes           = 12
  CmNo            = 13
  CmDefault       = 14

  # TView State masks 

  SfVisible       = 0x001
  SfCursorVis     = 0x002
  SfCursorIns     = 0x004
  SfShadow        = 0x008
  SfActive        = 0x010
  SfSelected      = 0x020
  SfFocused       = 0x040
  SfDragging      = 0x080
  SfDisabled      = 0x100
  SfModal         = 0x200
  SfDefault       = 0x400
  SfExposed       = 0x800

  # TView Option masks 

  OfSelectable    = 0x001
  OfTopSelect     = 0x002
  OfFirstClick    = 0x004
  OfFramed        = 0x008
  OfPreProcess    = 0x010
  OfPostProcess   = 0x020
  OfBuffered      = 0x040
  OfTileable      = 0x080
  OfCenterX       = 0x100
  OfCenterY       = 0x200
  OfCentered      = 0x300
  # SET: I added it, it means we want the object to send more broadcast
  # than the original TV did. Currently I plan to do it only for a few
  # classes and enable it by default, see TCluster as example.
  OfBeVerbose     = 0x400

  # TView GrowMode masks 

  GfGrowLoX       = 0x01
  GfGrowLoY       = 0x02
  GfGrowHiX       = 0x04
  GfGrowHiY       = 0x08
  GfGrowAll       = 0x0f
  GfGrowRel       = 0x10

  # TView DragMode masks 

  DmDragMove      = 0x01
  DmDragGrow      = 0x02
  DmLimitLoX      = 0x10
  DmLimitLoY      = 0x20
  DmLimitHiX      = 0x40
  DmLimitHiY      = 0x80
  DmLimitAll      = DmLimitLoX | DmLimitLoY | DmLimitHiX | DmLimitHiY

  # TView Help context codes

  HcNoContext     = 0
  HcDragging      = 1

  # TScrollBar part codes 

  SbLeftArrow     = 0
  SbRightArrow    = 1
  SbPageLeft      = 2
  SbPageRight     = 3
  SbUpArrow       = 4
  SbDownArrow     = 5
  SbPageUp        = 6
  SbPageDown      = 7
  SbIndicator     = 8

  # TScrollBar options for TWindow.StandardScrollBar 

  SbHorizontal    = 0x000
  SbVertical      = 0x001
  SbHandleKeyboard = 0x002

  # TWindow Flags masks

  WfMove          = 0x01
  WfGrow          = 0x02
  WfClose         = 0x04
  WfZoom          = 0x08

  #  TView inhibit flags

  NoMenuBar       = 0x0001
  NoDeskTop       = 0x0002
  NoStatusLine    = 0x0004
  NoBackground    = 0x0008
  NoFrame         = 0x0010
  NoViewer        = 0x0020
  NoHistory       = 0x0040

  # TWindow number constants

  WnNoNumber      = 0

  # TWindow palette entries 

  WpBlueWindow    = 0
  WpCyanWindow    = 1
  WpGrayWindow    = 2

  #  Application command codes

  CmCut           = 20
  CmCopy          = 21
  CmPaste         = 22
  CmUndo          = 23
  CmClear         = 24
  CmTile          = 25
  CmCascade       = 26

  # Standard messages 

  CmReceivedFocus     = 50
  CmReleasedFocus     = 51
  CmCommandSetChanged = 52

  # TScrollBar messages 

  CmScrollBarChanged  = 53
  CmScrollBarClicked  = 54

  # TWindow select messages 

  CmSelectWindowNum   = 55

  #  TListViewer messages

  CmListItemSelected  = 56

  # SET: This is a broadcast that TWindow sends to TProgram::application
  # to notify the window is closing. In this way the application can keep
  # track of closed windows

  CmClosingWindow     = 57

  # SET: Usually the owner doesn't have any information about the state of
  # your TCluster members. I added this to change the situation so you don't
  # need to create a specialized TCluster for it.
  # I think that's how an event/message system should work.

  CmClusterMovedTo    = 58
  CmClusterPress      = 59

  # From TButton::press()
  CmRecordHistory     = 60

  # SET: Here is a broadcast for TListViewer objects. It sends a broadcast
  # when an item is focused.

  CmListItemFocused   = 61

  # SET: Moved here to know they exist

  CmGrabDefault       = 62
  CmReleaseDefault    = 63

  #  Event masks

  positionalEvents    = EvMouse
  focusedEvents       = EvKeyboard | EvCommand;


  # Keys

  KbSpace     = 0x0034;

    #  Control keys

    KbCtrlA=0x0101;KbCtrlB=0x0102;KbCtrlC=0x0103;KbCtrlD=0x0104;
    KbCtrlE=0x0105;KbCtrlF=0x0106;KbCtrlG=0x0107;KbCtrlH=0x0108;
    KbCtrlI=0x0109;KbCtrlJ=0x010a;KbCtrlK=0x010b;KbCtrlL=0x010c;
    KbCtrlM=0x010d;KbCtrlN=0x010e;KbCtrlO=0x010f;KbCtrlP=0x0110;
    KbCtrlQ=0x0111;KbCtrlR=0x0112;KbCtrlS=0x0113;KbCtrlT=0x0114;
    KbCtrlU=0x0115;KbCtrlV=0x0116;KbCtrlW=0x0117;KbCtrlX=0x0118;
    KbCtrlY=0x0119;KbCtrlZ=0x011a;

    #// Extended key codes

    KbEsc       = 0x001f;   KbAltSpace  = 0x0234;   KbCtrlIns   = 0x014d;
    KbShiftIns  = 0x00cd;   KbCtrlDel   = 0x014e;   KbShiftDel  = 0x00ce;
    KbCtrlShiftIns = 0x01cd; KbCtrlShiftDel = 0x01ce;
    KbBack      = 0x002a;   KbCtrlBack  = 0x012a;   KbShiftTab  = 0x00ab;
    KbTab       = 0x002b;   KbAltA=0x0201;          KbAltB=0x0202;
    KbAltC=0x0203;          KbAltD=0x0204;          KbAltE=0x0205;
    KbAltF=0x0206;          KbAltG=0x0207;          KbAltH=0x0208;
    KbAltI=0x0209;          KbAltJ=0x020a;          KbAltK=0x020b;
    KbAltL=0x020c;          KbAltM=0x020d;          KbAltN=0x020e;
    KbAltO=0x020f;          KbAltP=0x0210;          KbAltQ=0x0211;
    KbAltR=0x0212;          KbAltS=0x0213;          KbAltT=0x0214;
    KbAltU=0x0215;          KbAltV=0x0216;          KbAltW=0x0217;
    KbAltX=0x0218;          KbAltY=0x0219;          KbAltZ=0x021a;
    KbCtrlEnter=0x012c;     KbEnter=0x002c;         KbF1=0x0039;
    KbF2=0x003a;            KbF3=0x003b;            KbF4=0x003c;
    KbF5=0x003d;            KbF6=0x003e;            KbF7=0x003f;
    KbF8=0x0040;            KbF9=0x0041;            KbF10=0x0042;
    KbF11=0x0043;           KbF12=0x0044;
    KbHome=0x0045;          KbUp=0x0046;            KbPgUp=0x0047;
    KbLeft=0x0048;          KbRight=0x0049;         KbEnd=0x004a;
    KbDown=0x004b;          KbPgDn=0x004c;          KbIns=0x004d;
    KbDel=0x004e;
    #// These are normal + & - because I think isn't good make any
    #// difference
    KbGrayMinus = 0x0035;   KbGrayPlus  = 0x0036;
    KbShiftF1=0x00b9;       KbShiftF2=0x00ba;       KbShiftF3=0x00bb;
    KbShiftF4=0x00bc;       KbShiftF5=0x00bd;       KbShiftF6=0x00be;
    KbShiftF7=0x00bf;       KbShiftF8=0x00c0;       KbShiftF9=0x00c1;
    KbShiftF10=0x00c2;      KbShiftF11=0x00c3;      KbShiftF12=0x00c4;
    KbCtrlF1=0x0139;        KbCtrlF2=0x013a;        KbCtrlF3=0x013b;
    KbCtrlF4=0x013c;        KbCtrlF5=0x013d;        KbCtrlF6=0x013e;
    KbCtrlF7=0x013f;        KbCtrlF8=0x0140;        KbCtrlF9=0x0141;
    KbCtrlF10=0x0142;       KbCtrlF11=0x0143;       KbCtrlF12=0x0144;
    KbAltF1=0x0239;         KbAltF2=0x023a;         KbAltF3=0x023b;
    KbAltF4=0x023c;         KbAltF5=0x023d;         KbAltF6=0x023e;
    KbAltF7=0x023f;         KbAltF8=0x0240;         KbAltF9=0x0241;
    KbAltF10=0x0242;        KbAltF11=0x0243;        KbAltF12=0x0244;
    KbCtrlPrtSc = 0x0137;   KbCtrlLeft=0x0148;      KbCtrlRight=0x0149;
    KbCtrlEnd=0x014a;       KbCtrlPgDn=0x014c;      KbCtrlHome  = 0x0145;
    KbAlt1=0x0221;          KbAlt2=0x0222;          KbAlt3=0x0223;
    KbAlt4=0x0224;          KbAlt5=0x0225;          KbAlt6=0x0226;
    KbAlt7=0x0227;          KbAlt8=0x0228;          KbAlt9=0x0229;
    KbAlt0      = 0x0220;   KbAltMinus  = 0x0235;   KbAltEqual  = 0x0238;
    KbCtrlPgUp  = 0x0147;   KbNoKey     = 0x0000;
    KbAltBack=0x022a;
  

  #//  Keyboard state and shift masks
  #const ushort
    KbRightShift  = 0x0001;
    KbLeftShift   = 0x0002;
    KbShift       = KbLeftShift | KbRightShift;
    KbLeftCtrl    = 0x0004;
    KbRightCtrl   = 0x0004;
    KbCtrlShift   = KbLeftCtrl | KbRightCtrl;
    KbLeftAlt     = 0x0008;
    KbRightAlt    = 0x0008;
    KbAltShift    = KbLeftAlt | KbRightAlt;
    KbScrollState = 0x0010;
    KbNumState    = 0x0020;
    KbCapsState   = 0x0040;
    KbInsState    = 0x0080;


  class Point
    def inspect
      super.sub(">"," <C++::TPoint x=#{x} y=#{y}> >")
    end
  end

  class Rect
    def inspect
      super.sub(">"," <C++::TRect a=#{a.inspect} b=#{b.inspect}> >")
    end
  end

  class StatusItem
    attr_reader :text, :keyCode, :command
    def initialize(text, key, cmd)
      @keyCode, @command = key, cmd
      @text = text.dup
    end
  end

  class StatusDef < Array
    attr_reader :min, :max
    def initialize(min, max, *items)
      super()
      if (min > max) 
	raise ArgumentError, "min may not be greater than max"
      end
      @min, @max = min, max
      if ((items.size == 1) && items[0].kind_of?(Array))
	items = items[0]
      end
      concat(items)
    end
  end

  def TVision.destroy(object)
    object.shutDown
  end

#    class View
#      PhFocused     = :phFocused
#      PhPreProcess  = :phPreProcess
#      PhPostProcess = :phPostProcess

#      NormalSelect = :normalSelect
#      EnterSelect  = :enterSelect
#      LeaveSelect  = :leaveSelect

#      def initialize(rect)
#        @next      = nil
#        @options   = 0
#        @eventMask = EvMouseDown | EvKeyDown | EvCommand
#      end      
#    end

      

#    class StatusLine < View
#    end
end


