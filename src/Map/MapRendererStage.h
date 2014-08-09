#ifndef _OSMAND_CORE_MAP_RENDERER_STAGE_H_
#define _OSMAND_CORE_MAP_RENDERER_STAGE_H_

#include "stdlib_common.h"

#include "QtExtensions.h"

#include "OsmAndCore.h"
#include "CommonTypes.h"
#include "MapRenderer.h"
#include "MapRendererResourcesManager.h"
#include "MapRendererConfiguration.h"
#include "MapRendererState.h"
#include "MapRendererInternalState.h"
#include "MapRendererSetupOptions.h"
#include "MapRendererDebugSettings.h"

namespace OsmAnd
{
    class GPUAPI;

    class MapRendererStage
    {
        Q_DISABLE_COPY(MapRendererStage);
    public:
        MapRendererStage(MapRenderer* const renderer);
        virtual ~MapRendererStage();

        MapRenderer* const renderer;

        const MapRendererResourcesManager& getResources() const;

        const std::unique_ptr<GPUAPI>& gpuAPI;
        const MapRendererSetupOptions& setupOptions;
        const std::shared_ptr<const MapRendererConfiguration>& currentConfiguration;
        const MapRendererState& currentState;
        const MapRendererInternalState& internalState;
        const std::shared_ptr<const MapRendererDebugSettings>& debugSettings;
        QReadWriteLock& publishedMapSymbolsLock;
        const QMap< int, MapRenderer::PublishedMapSymbols >& publishedMapSymbols;

        virtual void initialize() = 0;
        virtual void render() = 0;
        virtual void release() = 0;
    };
}

#endif // !defined(_OSMAND_CORE_MAP_RENDERER_STAGE_H_)
