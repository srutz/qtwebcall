#include "asyncfetcher.h"

AsyncFetcher::AsyncFetcher(AsyncFetcherOptions options, QObject *parent)
    : QObject(parent), options(options)
    , manager(new QNetworkAccessManager(this))
{
}

Task<QJsonDocument> AsyncFetcher::fetchJson()
{
    QByteArray data = co_await NetworkAwaiter(*manager, QUrl(options.url));
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        throw std::runtime_error("Failed to parse JSON");
    }
    //throw std::runtime_error("Invalid JSON structure");
    co_return doc;
}
