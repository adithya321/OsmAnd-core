#ifndef _OSMAND_CORE_BASE_SEARCH_H_
#define _OSMAND_CORE_BASE_SEARCH_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>

#include <OsmAndCore.h>
#include <OsmAndCore/Data/DataCommonTypes.h>
#include <OsmAndCore/Search/ISearch.h>

namespace OsmAnd
{
    class ObfDataInterface;

    class OSMAND_CORE_API BaseSearch : public ISearch
    {
        Q_DISABLE_COPY_AND_MOVE(BaseSearch);
    private:
    protected:
        BaseSearch(const std::shared_ptr<const IObfsCollection>& obfsCollection);

        std::shared_ptr<ObfDataInterface> obtainDataInterface(
            const Criteria& criteria,
            const ObfDataTypesMask desiredDataTypes) const;
    public:
        virtual ~BaseSearch();

        const std::shared_ptr<const IObfsCollection> obfsCollection;
        virtual std::shared_ptr<const IObfsCollection> getObfsCollection() const;
    };
}

#endif // !defined(_OSMAND_CORE_BASE_SEARCH_H_)
