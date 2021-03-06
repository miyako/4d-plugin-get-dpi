/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : DPI
 #	author : miyako
 #	2016/02/03
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

#include "shellscalingapi.h"

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	try
	{
		PA_long32 pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
// --- DPI

		case 1 :
			GET_SCREEN_DPI(pResult, pParams);
			break;

	}
}

// -------------------------------------- DPI -------------------------------------


#if VERSIONWIN

	typedef struct
	{
		int currentScreenId;
		int requestedScreenId;
		double dpi_x;
		double dpi_y;
	}EnumDisplayMonitorsContext;

	int getLogicalDpi(int angular_dpi)
	{
		int logical_dpi = 96;
		switch (angular_dpi)
		{
		case 19://500%
			logical_dpi = 480;
			break;
		case 24://400%
			logical_dpi = 384;
			break;
		case 32://300%
			logical_dpi = 288;
			break;
		case 39://250%
			logical_dpi = 240;
			break;
		case 48://200%
			logical_dpi = 192;
			break;
		case 64://150%
			logical_dpi = 144;
			break;
		case 77://125%
			logical_dpi = 120;
			break;
		case 96://100%
			logical_dpi = 96;
			break;
		default:
			logical_dpi = (int)((96 / (angular_dpi / 96)) + 0.5);
			break;
		}
		return logical_dpi;
	}

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dd145061(v=vs.85).aspx
	BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
  {
	EnumDisplayMonitorsContext *ctx = (EnumDisplayMonitorsContext *)dwData;
	ctx->currentScreenId++;
	if(ctx->currentScreenId == ctx->requestedScreenId)
	{
		UINT dpiX =0, dpiY = 0;
		if(S_OK == GetDpiForMonitor(hMonitor, MDT_RAW_DPI, &dpiX, &dpiY))
		{
			ctx->dpi_x = dpiX;
			ctx->dpi_y = dpiY;		
		}else
		{
			//VMWARE on Mac?
			int dpi_x = GetDeviceCaps (hdcMonitor, LOGPIXELSX);
			int dpi_y = GetDeviceCaps (hdcMonitor, LOGPIXELSY);
			if(S_OK == GetDpiForMonitor(hMonitor, MDT_ANGULAR_DPI, &dpiX, &dpiY))
			{
				ctx->dpi_x = getLogicalDpi(dpiX);
				ctx->dpi_y = getLogicalDpi(dpiY);
			}else
			{
				ctx->dpi_x = dpi_x;
				ctx->dpi_y = dpi_y;
			}
		}
		return FALSE;//To stop the enumeration, return FALSE
	}else{
		return TRUE;//To continue the enumeration, return TRUE
	}
  }
#endif

void GET_SCREEN_DPI(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_REAL Param1;
	C_REAL Param2;
	C_LONGINT Param3;

	Param3.fromParamAtIndex(pParams, 3);
	unsigned short index = Param3.getIntValue();
	index = index ? index : 1;
	
	double dpi_x, dpi_y;
	
#if VERSIONMAC

	unsigned short countScreens;
	NSArray *screens = [NSScreen screens];
	countScreens = [screens count];
	NSScreen *screen = (index <= countScreens) ? [screens objectAtIndex:index - 1] : [NSScreen mainScreen];
	NSDictionary *description = [screen deviceDescription];
	NSSize displayPixelSize = [[description objectForKey:NSDeviceSize]sizeValue];
	CGSize displayPhysicalSize = CGDisplayScreenSize([[description objectForKey:@"NSScreenNumber"]unsignedIntValue]);
	
#if __MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
	NSRect rect = NSMakeRect(0, 0, displayPixelSize.width, displayPixelSize.height);
	NSRect backingRect = [screen convertRectToBacking:rect];
	dpi_x = (backingRect.size.width) / displayPhysicalSize.width * 25.4f;
	dpi_y = (backingRect.size.height) / displayPhysicalSize.height * 25.4f;
#endif
	
#else

	EnumDisplayMonitorsContext ctx;
	ctx.currentScreenId = 0;
	ctx.requestedScreenId = index;
	ctx.dpi_x = 0;
	ctx.dpi_y = 0;
	
	HDC hDesktop = GetDC(NULL);

	if(hDesktop)
	{
		EnumDisplayMonitors(hDesktop, NULL, MonitorEnumProc, (LPARAM)&ctx);
		ReleaseDC(NULL, hDesktop);
	}
	
	dpi_x = ctx.dpi_x;
	dpi_y = ctx.dpi_y;
#endif
	
	Param1.setDoubleValue(dpi_x);
	Param2.setDoubleValue(dpi_y);
	
	Param1.toParamAtIndex(pParams, 1);
	Param2.toParamAtIndex(pParams, 2);
}

