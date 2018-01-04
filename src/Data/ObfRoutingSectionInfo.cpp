#include "ObfRoutingSectionInfo.h"
#include "ObfRoutingSectionInfo_P.h"

#include "Utilities.h"
#include "Logging.h"

OsmAnd::ObfRoutingSectionInfo::ObfRoutingSectionInfo(const std::shared_ptr<const ObfInfo>& container)
    : ObfSectionInfo(container)
    , _p(new ObfRoutingSectionInfo_P(this))
{
}

OsmAnd::ObfRoutingSectionInfo::~ObfRoutingSectionInfo()
{
}

std::shared_ptr<const OsmAnd::ObfRoutingSectionAttributeMapping> OsmAnd::ObfRoutingSectionInfo::getAttributeMapping() const
{
    return _p->getAttributeMapping();
}

OsmAnd::ObfRoutingSectionLevel::ObfRoutingSectionLevel(const RoutingDataLevel dataLevel_)
    : _p(new ObfRoutingSectionLevel_P(this))
    , dataLevel(dataLevel_)
    , rootNodes(_p->_rootNodes)
{
}

OsmAnd::ObfRoutingSectionLevel::~ObfRoutingSectionLevel()
{
}

OsmAnd::ObfRoutingSectionLevelTreeNode::ObfRoutingSectionLevelTreeNode()
    : length(0)
    , offset(0)
    , hasChildrenDataBoxes(false)
    , firstDataBoxInnerOffset(0)
    , dataOffset(0)
{
}

OsmAnd::ObfRoutingSectionLevelTreeNode::~ObfRoutingSectionLevelTreeNode()
{
}

OsmAnd::ObfRoutingSectionAttributeMapping::ObfRoutingSectionAttributeMapping()
{
    decodeMap.reserve(4096);
}

OsmAnd::ObfRoutingSectionAttributeMapping::~ObfRoutingSectionAttributeMapping()
{
}

void OsmAnd::ObfRoutingSectionAttributeMapping::registerMapping(
                                                          const uint32_t id,
                                                          const QString& tag,
                                                          const QString& value)
{
    MapObject::AttributeMapping::registerMapping(id, tag, value);

    // Create decode mapping
    auto pDecode = decodeMap.getRef(id);
    if (!pDecode)
    {
        LogPrintf(LogSeverityLevel::Error,
                  "Decode attribute #%u is not defined. Capture of %s = %s ignored.",
                  id,
                  qPrintable(tag),
                  qPrintable(value));
        return;
    }
    const QStringRef tagRef(&pDecode->tag);
    const QStringRef valueRef(&pDecode->value);
    
    // Capture quick-access rules
    if (tag.startsWith(QLatin1String("ref:")))
    {
        const auto languageIdRef = tagRef.mid(QLatin1String("ref:").size());
        localizedRefAttributes.insert(languageIdRef, id);
        localizedRefAttributeIds.insert(id, languageIdRef);
        refAttributeIds.insert(id);
    }
}

    /*else
    {
        LogPrintf(LogSeverityLevel::Debug, "%s = %s", qPrintable(ruleTag), qPrintable(ruleValue));
    }*/
    //if (ruleTag.compare(QLatin1String("oneway"), Qt::CaseInsensitive) == 0)
    //{
    //    rule->type = RuleType::OneWay;
    //    if (ruleValue == QLatin1String("-1") || ruleValue == QLatin1String("reverse"))
    //        rule->parsedValue.asSignedInt = -1;
    //    else if (ruleValue == QLatin1String("1") || ruleValue == QLatin1String("yes"))
    //        rule->parsedValue.asSignedInt = 1;
    //    else
    //        rule->parsedValue.asSignedInt = 0;
    //}
    //else if (ruleTag.compare(QLatin1String("highway"), Qt::CaseInsensitive) == 0 && ruleValue == QLatin1String("traffic_signals"))
    //{
    //    rule->type = RuleType::TrafficSignals;
    //}
    //else if (ruleTag.compare(QLatin1String("railway"), Qt::CaseInsensitive) == 0 && (ruleValue == QLatin1String("crossing") || ruleValue == QLatin1String("level_crossing")))
    //{
    //    rule->type = RuleType::RailwayCrossing;
    //}
    //else if (ruleTag.compare(QLatin1String("roundabout"), Qt::CaseInsensitive) == 0 && !ruleValue.isEmpty())
    //{
    //    rule->type = RuleType::Roundabout;
    //}
    //else if (ruleTag.compare(QLatin1String("junction"), Qt::CaseInsensitive) == 0 && ruleValue.compare(QLatin1String("roundabout"), Qt::CaseInsensitive) == 0)
    //{
    //    rule->type = RuleType::Roundabout;
    //}
    //else if (ruleTag.compare(QLatin1String("highway"), Qt::CaseInsensitive) == 0 && !ruleValue.isEmpty())
    //{
    //    rule->type = RuleType::Highway;
    //}
    //else if (ruleTag.startsWith(QLatin1String("access")) && !ruleValue.isEmpty())
    //{
    //    rule->type = RuleType::Access;
    //}
    //else if (ruleTag.compare(QLatin1String("maxspeed"), Qt::CaseInsensitive) == 0 && !ruleValue.isEmpty())
    //{
    //    rule->type = RuleType::Maxspeed;
    //    rule->parsedValue.asFloat = Utilities::parseSpeed(ruleValue, -1.0);
    //}
    //else if (ruleTag.compare(QLatin1String("lanes"), Qt::CaseInsensitive) == 0 && !ruleValue.isEmpty())
    //{
    //    rule->type = RuleType::Lanes;
    //    rule->parsedValue.asSignedInt = Utilities::parseArbitraryInt(ruleValue, -1);
    //}

    //// Fill gaps in IDs
    //while (decodingRules.size() < rule->id)
    //    decodingRules.push_back(nullptr);
    //decodingRules.push_back(rule);
