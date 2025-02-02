#ifndef QUOTEFETCHER_H
#define QUOTEFETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class QuoteFetcher : public QObject
{
    Q_OBJECT
public:
    explicit QuoteFetcher(QObject *parent = nullptr);
    void fetchQuotes();

signals:
    void quotesReceived(const QJsonArray &quotes);
    void error(const QString &message);

private slots:
    void handleNetworkResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif // QUOTEFETCHER_H
