#ifndef _OSMAND_CORE_MAP_PRESENTATION_ENVIRONMENT_P_H_
#define _OSMAND_CORE_MAP_PRESENTATION_ENVIRONMENT_P_H_

#include "stdlib_common.h"

#include "QtExtensions.h"
#include <QMap>
#include <QHash>
#include <QMutex>

#include "ignore_warnings_on_external_includes.h"
#include <SkPaint.h>
#include "restore_internal_warnings.h"

#include "OsmAndCore.h"
#include "CommonTypes.h"
#include "PrivateImplementation.h"
#include "MapStyle.h"
#include "MapStyleRule.h"
#include "MapRasterizer.h"

class SkBitmap;

namespace OsmAnd
{
    class MapStyle;
    class MapStyleEvaluator;
    class MapStyleEvaluator_P;

    class MapPresentationEnvironment;
    class MapPresentationEnvironment_P Q_DECL_FINAL
    {
    private:
    protected:
        MapPresentationEnvironment_P(MapPresentationEnvironment* owner);

        void initialize();

        mutable QMutex _settingsChangeMutex;
        QHash< std::shared_ptr<const MapStyleValueDefinition>, MapStyleValue > _settings;

        ColorARGB _defaultBgColor;
        double _polygonMinSizeToDisplay;
        unsigned int _roadDensityZoomTile;
        unsigned int _roadsDensityLimitPerTile;
        int _shadowRenderingMode;
        ColorARGB _shadowRenderingColor;

        std::shared_ptr<const MapStyleRule> _attributeRule_defaultColor;
        std::shared_ptr<const MapStyleRule> _attributeRule_shadowRendering;
        std::shared_ptr<const MapStyleRule> _attributeRule_polygonMinSizeToDisplay;
        std::shared_ptr<const MapStyleRule> _attributeRule_roadDensityZoomTile;
        std::shared_ptr<const MapStyleRule> _attributeRule_roadsDensityLimitPerTile;

        mutable QMutex _shadersBitmapsMutex;
        mutable QHash< QString, std::shared_ptr<SkBitmap> > _shadersBitmaps;

        mutable QMutex _mapIconsMutex;
        mutable QHash< QString, std::shared_ptr<const SkBitmap> > _mapIcons;

        mutable QMutex _textShieldsMutex;
        mutable QHash< QString, std::shared_ptr<const SkBitmap> > _textShields;

        QByteArray obtainResourceByName(const QString& name) const;
    public:
        virtual ~MapPresentationEnvironment_P();

        ImplementationInterface<MapPresentationEnvironment> owner;

        const std::shared_ptr<const ObfMapSectionInfo> dummyMapSection;

        QHash< std::shared_ptr<const MapStyleValueDefinition>, MapStyleValue > getSettings() const;
        void setSettings(const QHash< std::shared_ptr<const MapStyleValueDefinition>, MapStyleValue >& newSettings);
        void setSettings(const QHash< QString, QString >& newSettings);

        void applyTo(MapStyleEvaluator& evaluator) const;

        bool obtainShaderBitmap(const QString& name, std::shared_ptr<const SkBitmap>& outBitmap) const;
        bool obtainMapIcon(const QString& name, std::shared_ptr<const SkBitmap>& outIcon) const;
        bool obtainTextShield(const QString& name, std::shared_ptr<const SkBitmap>& outShield) const;

        ColorARGB getDefaultBackgroundColor(const ZoomLevel zoom) const;
        void obtainShadowRenderingOptions(const ZoomLevel zoom, int& mode, ColorARGB& color) const;
        double getPolygonAreaMinimalThreshold(const ZoomLevel zoom) const;
        unsigned int getRoadDensityZoomTile(const ZoomLevel zoom) const;
        unsigned int getRoadsDensityLimitPerTile(const ZoomLevel zoom) const;

    friend class OsmAnd::MapPresentationEnvironment;
    };
}

#endif // !defined(_OSMAND_CORE_MAP_PRESENTATION_ENVIRONMENT_P_H_)
