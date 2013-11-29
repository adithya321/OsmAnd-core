#include "OfflineMapSymbolProvider.h"
#include "OfflineMapSymbolProvider_P.h"

OsmAnd::OfflineMapSymbolProvider::OfflineMapSymbolProvider( const std::shared_ptr<OfflineMapDataProvider>& dataProvider_, const float density /*= 1.0f*/ )
    : _d(new OfflineMapSymbolProvider_P(this))
    , dataProvider(dataProvider_)
{
}

OsmAnd::OfflineMapSymbolProvider::~OfflineMapSymbolProvider()
{
}

bool OsmAnd::OfflineMapSymbolProvider::obtainSymbols(
    const TileId tileId, const ZoomLevel zoom,
    std::shared_ptr<const MapSymbolsTile>& outTile,
    std::function<bool (const std::shared_ptr<const Model::MapObject>& mapObject)> filter/*= nullptr*/)
{
    return _d->obtainSymbols(tileId, zoom, outTile, filter);
}
