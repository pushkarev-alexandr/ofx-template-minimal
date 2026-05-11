#include "ofxCore.h"
#include "ofxImageEffect.h"
#include "ofxProperty.h"
#include <cstdio>
#include <cstring>

namespace {
    OfxHost *gHost;
    OfxPropertySuiteV1 *gPropertySuite;
    OfxImageEffectSuiteV1 *gImageEffectSuite;

    OfxStatus LoadAction(void)
    {
        gPropertySuite = (OfxPropertySuiteV1 *) gHost->fetchSuite(gHost->host, kOfxPropertySuite, 1);
        gImageEffectSuite = (OfxImageEffectSuiteV1 *) gHost->fetchSuite(gHost->host, kOfxImageEffectSuite, 1);

        return kOfxStatOK;
    }

    OfxStatus DescribeAction(OfxImageEffectHandle descriptor)
    {
        OfxPropertySetHandle effectProps;
        gImageEffectSuite->getPropertySet(descriptor, &effectProps);

        gPropertySuite->propSetString(effectProps, kOfxPropLabel, 0, "OFX Template Plugin");
        gPropertySuite->propSetString(effectProps, kOfxImageEffectPluginPropGrouping, 0, "Pushkarev");
        gPropertySuite->propSetString(effectProps, kOfxImageEffectPropSupportedContexts, 0, kOfxImageEffectContextFilter);
        gPropertySuite->propSetString(effectProps, kOfxImageEffectPropSupportedPixelDepths, 0, kOfxBitDepthFloat);
        gPropertySuite->propSetString(effectProps, kOfxImageEffectPluginRenderThreadSafety, 0, kOfxImageEffectRenderFullySafe);
        gPropertySuite->propSetInt(effectProps, kOfxImageEffectPluginPropHostFrameThreading, 0, 1);

        return kOfxStatOK;
    }

    OfxStatus DescribeInContextAction(OfxImageEffectHandle descriptor)
    {
        OfxPropertySetHandle props;

        gImageEffectSuite->clipDefine(descriptor, "Output", &props);
        gPropertySuite->propSetString(props, kOfxImageEffectPropSupportedComponents, 0, kOfxImageComponentRGBA);

        gImageEffectSuite->clipDefine(descriptor, "Source", &props);
        gPropertySuite->propSetString(props, kOfxImageEffectPropSupportedComponents, 0, kOfxImageComponentRGBA);

        return kOfxStatOK;
    }

    OfxStatus RenderAction(OfxImageEffectHandle instance, OfxPropertySetHandle inArgs)
    {
        fprintf(stderr, "RenderAction\n");

        return kOfxStatOK;
    }

    void SetHostFunc(OfxHost *hostStruct)
    {
        gHost = hostStruct;
    }

    OfxStatus MainEntryPoint(const char *action, const void *handle, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
    {
        OfxImageEffectHandle effect = (OfxImageEffectHandle) handle;
        OfxStatus returnStatus = kOfxStatReplyDefault;

        if (strcmp(action, kOfxActionLoad) == 0) {
            returnStatus = LoadAction();
        }
        else if (strcmp(action, kOfxActionDescribe) == 0) {
            returnStatus = DescribeAction(effect);
        }
        else if (strcmp(action, kOfxImageEffectActionDescribeInContext) == 0) {
            returnStatus = DescribeInContextAction(effect);
        }
        else if (strcmp(action, kOfxImageEffectActionRender) == 0) {
            returnStatus = RenderAction(effect, inArgs);
        }

        return returnStatus;
    }
}

static OfxPlugin effectPluginStruct = 
{
    kOfxImageEffectPluginApi,
    1,
    "ru.pushkarevfx:TemplatePlugin",
    1,
    0,
    SetHostFunc,
    MainEntryPoint
};

OfxExport int OfxGetNumberOfPlugins(void)
{
    return 1;
}

OfxExport OfxPlugin * OfxGetPlugin(int nth)
{
    return &effectPluginStruct;
}
