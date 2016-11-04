#ifndef CHECKHEADER_SLIB_RENDER_OPENGL_EGL
#define CHECKHEADER_SLIB_RENDER_OPENGL_EGL

#include "definition.h"

#include "engine.h"

SLIB_RENDER_NAMESPACE_BEGIN

class SLIB_EXPORT EGL
{
public:
	static Ref<Renderer> createRenderer(void* windowHandle, const RendererParam& param);

public:
	static sl_bool isAvailable();
	
	static void loadEntries(const String& pathDll, sl_bool flagReload = sl_true);
	
	static void loadEntries(sl_bool flagReload = sl_false);
	
};

SLIB_RENDER_NAMESPACE_END

#endif
