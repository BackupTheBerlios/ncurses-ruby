require "tvision.so"

module Tvision

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


  class Point
    attr_accessor :x,:y
    def initialize(*args)
      case args.size()
      when 0
	@x, @y = 0,0
      when 2
	@x, @y = *args
      else
	raise "needs 0 or 2 arguments"
      end
    end
    def +(other)
      Point.new(@x + other.x, @y + other.y)
    end
    def -(other)
      Point.new(@x - other.x, @y - other.y)
    end
    def ==(other)
      (@x == other.x) && (@y == other.y)
    end
  end

  class Rect
    attr_accessor :a, :b
    def initialize(*args)
      case args.size
      when 0
	@a = Point.new
	@b = Point.new
      when 2
	@a, @b = *args
      when 4
	@a = Point.new(*(args[0,2]));
	@b = Point.new(*(args[2,2]));
      else
	raise "needs 0, 2 or 4 arguments"
      end
    end

    def move!(aDx, aDy)
      a.x += aDX
      a.y += aDY
      b.x += aDX
      b.y += aDY
    end
    def grow!(aDX, aDY)
      a.x -= aDX
      a.y -= aDY
      b.x += aDX
      b.y += aDY
    end
    def intersect!(other)
      a.x = [a.x, other.a.x].max
      a.y = [a.y, other.a.y].max
      b.x = [b.x, other.b.x].min
      b.y = [b.y, other.b.y].min
    end
    def union!(other)
      a.x = [a.x, other.a.x].min
      a.y = [a.y, other.a.y].min
      b.x = [b.x, other.b.x].max
      b.y = [b.y, other.b.y].max
    end		
    def contains(point)
      (point.x >= a.x) && (point.x < b.x) &&
	(point.y >= a.y) && (point.y < b.y)
    end
    def ==(other)
      (a == other.a) && (b == other.b)
    end
    def empty?
      (a.x >= b.x) || (a.y >= b.y)
    end
  end

  class StatusItem
    attr_accessor :next, :text, :keyCode, :command
    def initialize(text, key, cmd, next = nil)
      @next, @keyCode, @command = next, key, cmd
      @text = text.dup
    end
    def add!(item)
      if (next)
	next.add!(item)
      else
	next = item
      end
      self
    end
  end

  class StatusDef
    attr_accessor :min, :max, :items, :next
    def initialize(min, max, items = nil, next = nil)
      @min, @max, @items, @next = min, max, items, next
    end
    def add!(other)
      if (@next)
	@next.add!(other)
      else
	case other
	when StatusItem
	  if (@items)
	    @items.add!(other)
	  else
	    @items = other
	  end
	when StatusDef
	  @next = other
	end
      end
      self
    end
  end

  def Tvision.destroy(object)
    object.shutDown
  end

  class View
    PhFocused     = :phFocused
    PhPreProcess  = :phPreProcess
    PhPostProcess = :phPostProcess

    NormalSelect = :normalSelect
    EnterSelect  = :enterSelect
    LeaveSelect  = :leaveSelect

    def initialize(rect)
      @next      = nil
      @options   = 0
      @eventMask = EvMouseDown | EvKeyDown | EvCommand
    end      
  end

      

  class StatusLine < View
  end
end


