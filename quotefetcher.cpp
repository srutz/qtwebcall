#include "quotefetcher.h"

QuoteFetcher::QuoteFetcher(QObject *parent)
    : QObject(parent)
    , manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished,
            this, &QuoteFetcher::handleNetworkResponse);
}

void QuoteFetcher::fetchQuotes()
{
    QNetworkRequest request(QUrl("https://dummyjson.com/quotes"));
    manager->get(request);
}

void QuoteFetcher::handleNetworkResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit error(reply->errorString());
        reply->deleteLater();
        return;
    }

    auto data = reply->readAll();
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        emit error("Failed to parse JSON");
        reply->deleteLater();
        return;
    }

    auto root = doc.object();
    if (root.contains("quotes") && root["quotes"].isArray()) {
        emit quotesReceived(root["quotes"].toArray());
    } else {
        emit error("Invalid JSON structure");
    }

    reply->deleteLater();
}
