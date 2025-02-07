#ifndef JSONFETCHER_H
#define JSONFETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QByteArray>

/*
 * Generic JSON Fetcher
 */


class JsonFetcher : public QObject
{
    Q_OBJECT

    /* options for the fetch
    */
    struct FetchOptions {
        QString url;
        std::optional<QString> httpMethod; // POST, GET, DELETE, PUT etc
        std::optional<QByteArray> data; // POST / PUT upload-data
    };


public:
    explicit JsonFetcher(QObject *parent = nullptr);
    void fetch(const FetchOptions &options);

signals:
    void responseReceived(const QJsonDocument &document);
    void error(const QString &message);

private slots:
    void handleNetworkResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};


#endif // JSONFETCHER_H
