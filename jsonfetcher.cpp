#include "jsonfetcher.h"
#include "raiiguard.h"

JsonFetcher::JsonFetcher(QObject *parent)
    : QObject(parent)
    , manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &JsonFetcher::handleNetworkResponse);
}

void JsonFetcher::fetch(const FetchOptions &options)
{
    QUrl url(options.url);
    if (!url.isValid()) {
        emit error("Invalid URL");
        return;
    }
    QNetworkRequest request(url);
    qDebug() << "Fetching URL:" << url.toString();
    request.setRawHeader("Accept", "application/json");
    if (options.httpMethod.value_or("GET") == "POST") {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        manager->post(request, options.data.value_or(QByteArray()));
    } else {
        manager->get(request);
    }
}

void JsonFetcher::handleNetworkResponse(QNetworkReply *reply)
{
    qDebug() << "network request finished 2";
    /* make sure reply is deleted under all circumstances */
    RAIIGuard guard([reply] { reply->deleteLater(); });
    qDebug() << "handle json response";

    if (reply->error() != QNetworkReply::NoError) {
        emit error(reply->errorString());
        return;
    }
    auto data = reply->readAll();
    qDebug() << "got data" << data.size() << "bytes" << ": utf8=" << QString::fromUtf8(data);
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        emit error("Failed to parse JSON");
        return;
    }
    emit responseReceived(doc);
}
