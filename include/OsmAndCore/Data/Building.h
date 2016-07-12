#ifndef _OSMAND_CORE_BUILDING_H_
#define _OSMAND_CORE_BUILDING_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>
#include <QString>
#include <QHash>

#include <OsmAndCore.h>
#include <OsmAndCore/MemoryCommon.h>
#include <OsmAndCore/PointsAndAreas.h>
#include <OsmAndCore/Data/Address.h>
#include <OsmAndCore/Data/DataCommonTypes.h>

namespace OsmAnd
{
    class ObfStreet;
    class StreetGroup;

    class OSMAND_CORE_API Building Q_DECL_FINAL: public Address
    {
        Q_DISABLE_COPY_AND_MOVE(Building);

    public:
        enum class Interpolation : int32_t
        {
            Disabled = 0,
            All = -1,
            Even = -2,
            Odd = -3,
            Alphabetic = -4
        };

    private:
    protected:
    public:
        Building(const std::shared_ptr<const ObfStreet>& street);
        Building(const std::shared_ptr<const StreetGroup>& streetGroup);
        virtual ~Building();
        virtual QString toString() const;

        const std::shared_ptr<const ObfStreet> street;
        const std::shared_ptr<const StreetGroup> streetGroup;

        ObfObjectId id;
        QString nativeName;
        QHash<QString, QString> localizedNames;
        QString postcode;
        PointI position31;

        Interpolation interpolation;
        QString interpolationNativeName;
        QHash<QString, QString> interpolationLocalizedNames;
        PointI interpolationPosition31;
    };
}

#endif // !defined(_OSMAND_CORE_BUILDING_H_)
