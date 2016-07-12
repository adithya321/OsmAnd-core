#ifndef _OSMAND_CORE_OBF_FILE_H_
#define _OSMAND_CORE_OBF_FILE_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>
#include <QString>
#include <QFileInfo>

#include <OsmAndCore.h>
#include <OsmAndCore/PrivateImplementation.h>

namespace OsmAnd
{
    class ObfInfo;
    class ObfReader_P;

    class ObfFile_P;
    class OSMAND_CORE_API ObfFile
    {
        Q_DISABLE_COPY_AND_MOVE(ObfFile);
    private:
        PrivateImplementation<ObfFile_P> _p;
    protected:
    public:
        ObfFile(const QString& filePath);
        ObfFile(const QString& filePath, const uint64_t fileSize);
        virtual ~ObfFile();

        const QString filePath;
        const uint64_t fileSize;
        const std::shared_ptr<const ObfInfo>& obfInfo;

    friend class OsmAnd::ObfReader_P;
    };
}

#endif // !defined(_OSMAND_CORE_OBF_FILE_H_)
