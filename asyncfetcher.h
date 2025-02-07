#ifndef ASYNCFETCHER_H
#define ASYNCFETCHER_H

#include <QObject>


#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <coroutine>
#include <exception>

// Task type to represent our async operation
template<typename T>
class Task {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    Task(handle_type h) : coro(h) {}
    ~Task() {
        if (coro) coro.destroy();
    }

    struct promise_type {
        T result;
        std::exception_ptr exception;

        Task get_return_object() {
            return Task(handle_type::from_promise(*this));
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_value(T value) {
            result = std::move(value);
        }
        void unhandled_exception() {
            exception = std::current_exception();
        }
    };

    T result() const { return coro.promise().result; }

private:
    handle_type coro;
};


// Awaitable type for network operations
class NetworkAwaiter {
public:
    NetworkAwaiter(QNetworkAccessManager& manager, const QUrl& url)
        : m_manager(manager), m_url(url) {}

    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> h) {
        QNetworkRequest request(m_url);
        auto reply = m_manager.get(request);
        QObject::connect(reply, &QNetworkReply::finished, [reply, h]() {
            if (reply->error() == QNetworkReply::NoError) {
                m_result = reply->readAll();
            } else {
                m_error = reply->errorString();
            }
            reply->deleteLater();
            h.resume();
        });
    }
    QByteArray await_resume() {
        if (!m_error.isEmpty()) {
            throw std::runtime_error(m_error.toStdString());
        }
        return m_result;
    }

private:
    QNetworkAccessManager& m_manager;
    QUrl m_url;
    static inline QByteArray m_result;
    static inline QString m_error;
};




struct AsyncFetcherOptions {
    QString url;
};

class AsyncFetcher : public QObject {
    Q_OBJECT
public:
    explicit AsyncFetcher(AsyncFetcherOptions options, QObject *parent = nullptr);
    Task<QJsonDocument> fetchJson();

private:
    QNetworkAccessManager *manager;
    AsyncFetcherOptions options;
};

#endif // ASYNCFETCHER_H
