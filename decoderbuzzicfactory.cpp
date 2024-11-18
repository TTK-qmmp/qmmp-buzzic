#include "decoderbuzzicfactory.h"
#include "buzzicmetadatamodel.h"
#include "decoder_buzzic.h"
#include "buzzichelper.h"

#include <QMessageBox>

bool DecoderBuzzicFactory::canDecode(QIODevice *input) const
{
    const QFile * const file = qobject_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    BuzzicHelper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderBuzzicFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("Buzzic Plugin");
    properties.shortName = "buzzic";
    properties.filters << "*.buz" << "*.buz2";
    properties.description = "Buzzic Audio File";
    properties.protocols << "file";
    properties.noInput = true;
    return properties;
}

Decoder *DecoderBuzzicFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderBuzzic(path);
}

QList<TrackInfo*> DecoderBuzzicFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);
    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    BuzzicHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "Buzzic");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderBuzzicFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(readOnly);
    return new BuzzicMetaDataModel(path);
}

#if (QMMP_VERSION_INT < 0x10700) || (0x20000 <= QMMP_VERSION_INT && QMMP_VERSION_INT < 0x20200)
void DecoderBuzzicFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}
#else
QDialog *DecoderBuzzicFactory::createSettings(QWidget *parent)
{
    Q_UNUSED(parent);
    return nullptr;
}
#endif

void DecoderBuzzicFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About Buzzic Reader Plugin"),
                       tr("Qmmp Buzzic Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderBuzzicFactory::translation() const
{
    return QString();
}
