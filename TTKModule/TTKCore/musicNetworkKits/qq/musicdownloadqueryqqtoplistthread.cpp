#include "musicdownloadqueryqqtoplistthread.h"
#include "musictime.h"
#///QJson import
#include "qjson/parser.h"

MusicDownLoadQueryQQToplistThread::MusicDownLoadQueryQQToplistThread(QObject *parent)
    : MusicDownLoadQueryThreadAbstract(parent)
{
    m_queryServer = "QQ";
}

QString MusicDownLoadQueryQQToplistThread::getClassName()
{
    return staticMetaObject.className();
}

void MusicDownLoadQueryQQToplistThread::startToSearch(QueryType type, const QString &toplist)
{
    Q_UNUSED(type);
    Q_UNUSED(toplist);
    startToSearch("4");
}

void MusicDownLoadQueryQQToplistThread::startToSearch(const QString &toplist)
{
    if(!m_manager)
    {
        return;
    }

    M_LOGGER_INFO(QString("%1 startToSearch").arg(getClassName()));
    QUrl musicUrl = MusicUtils::Algorithm::mdII(QQ_SONG_TOPLIST_C_URL, false).arg(toplist);
    deleteAll();

    QNetworkRequest request;
    request.setUrl(musicUrl);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
#ifndef QT_NO_SSL
    QSslConfiguration sslConfig = request.sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
#endif
    m_reply = m_manager->get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
}

void MusicDownLoadQueryQQToplistThread::downLoadFinished()
{
    if(!m_reply || !m_manager)
    {
        deleteAll();
        return;
    }

    M_LOGGER_INFO(QString("%1 downLoadFinished").arg(getClassName()));
    emit clearAllItems();      ///Clear origin items
    m_musicSongInfos.clear();  ///Empty the last search to songsInfo

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_reply->readAll(); ///Get all the data obtained by request

        QJson::Parser parser;
        bool ok;
        QVariant data = parser.parse(bytes, &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["code"].toInt() == 0 && value.contains("songlist"))
            {
                QVariantMap topInfo = value["topinfo"].toMap();
                MusicPlaylistItem info;
                info.m_name = topInfo["ListName"].toString();
                info.m_coverUrl = topInfo["pic"].toString();
                info.m_playCount = QString::number(topInfo["listennum"].toULongLong());
                info.m_description = topInfo["info"].toString();
                info.m_updateTime = value["date"].toString();
                emit createToplistInfoItem(info);
                ////////////////////////////////////////////////////////////
                QVariantList datas = value["songlist"].toList();
                foreach(const QVariant &var, datas)
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    value = value["data"].toMap();
                    MusicObject::MusicSongInformation musicInfo;
                    foreach(const QVariant &var, value["singer"].toList())
                    {
                        if(var.isNull())
                        {
                            continue;
                        }
                        QVariantMap name = var.toMap();
                        musicInfo.m_singerName = name["name"].toString();
                        musicInfo.m_artistId = QString::number(name["id"].toULongLong());
                    }
                    musicInfo.m_songName = value["songname"].toString();
                    musicInfo.m_timeLength = MusicTime::msecTime2LabelJustified(value["interval"].toInt()*1000);;

                    musicInfo.m_songId = value["songid"].toString();
                    musicInfo.m_albumId = value["albummid"].toString();

                    musicInfo.m_lrcUrl = MusicUtils::Algorithm::mdII(QQ_SONG_LRC_URL, false).arg(musicInfo.m_songId);
                    musicInfo.m_smallPicUrl = MusicUtils::Algorithm::mdII(QQ_SONG_PIC_URL, false)
                                .arg(musicInfo.m_albumId.right(2).left(1))
                                .arg(musicInfo.m_albumId.right(1)).arg(musicInfo.m_albumId);

                    if(!m_manager || m_stateCode != MusicNetworkAbstract::Init) return;
                    readFromMusicSongAttribute(&musicInfo, value, m_searchQuality, m_queryAllRecords);
                    if(!m_manager || m_stateCode != MusicNetworkAbstract::Init) return;

                    if(musicInfo.m_songAttrs.isEmpty())
                    {
                        continue;
                    }

                    MusicSearchedItem item;
                    item.m_songname = musicInfo.m_songName;
                    item.m_artistname = musicInfo.m_singerName;
                    item.m_time = musicInfo.m_timeLength;
                    item.m_type = mapQueryServerString();
                    emit createSearchedItems(item);
                    m_musicSongInfos << musicInfo;
                }
            }
        }
    }

    emit downLoadDataChanged(QString());
    deleteAll();
    M_LOGGER_INFO(QString("%1 downLoadFinished deleteAll").arg(getClassName()));
}
