
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "util.h"
#include <QJsonObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QDebug>
#include <QScrollArea>
#include <QSplitter>
#include <QMargins>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto layout = new QVBoxLayout(this->centralWidget());

    auto splitter = new QSplitter(Qt::Horizontal, this);
    layout->addWidget(splitter, 1);

    auto textBrowser = new QTextBrowser(this);
    auto fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(9);
    textBrowser->setFont(fixedFont);
    splitter->addWidget(textBrowser);

    auto quotesPanel = new QWidget(this);
    quotesPanel->setStyleSheet("background-color: #dfdfde;");
    auto quotesPanelLayout = new QVBoxLayout(quotesPanel);
    quotesPanelLayout->setSpacing(8);
    quotesPanelLayout->setAlignment(Qt::AlignHCenter);

    auto scrollArea = new QScrollArea(this);
    scrollArea->setWidget(quotesPanel);
    scrollArea->setWidgetResizable(true);  // Allow the widget to resize
    splitter->addWidget(scrollArea);

    QList<int> sizes;
    sizes << 200 << 300;
    splitter->setSizes(sizes);

    auto buttonsPanel = new QWidget(this);
    auto buttonsPanelLayout = new QHBoxLayout(buttonsPanel);
    auto fetchButton = new QPushButton(this);
    fetchButton->setText("Fetch Quotes");
    buttonsPanelLayout->addStretch();
    buttonsPanelLayout->setContentsMargins(QMargins(0, 0, 0, 0));
    buttonsPanelLayout->addWidget(fetchButton);
    layout->addWidget(buttonsPanel);

    auto runFetch = [=] {
        fetcher = new QuoteFetcher();
        connect(fetcher, &QuoteFetcher::quotesReceived, this, [=](const QJsonArray &quotes) {
            qDebug() << "got " << quotes.size() << " quotes";
            auto doc = QJsonDocument(quotes);
            auto formattedJson = doc.toJson(QJsonDocument::Indented);
            textBrowser->setText(formattedJson);

            // convert the json to Quotes
            m_quotes.clear();

            long id = 1;
            for (auto o : quotes) {
                auto q = o.toObject();
                Quote quote = {
                    .id = id++,
                    .quote = q["quote"].toString(""),
                    .author = q["author"].toString(""),
                };
                m_quotes.push_back(quote);
            }
            Util::clearWidget(quotesPanel);
            for (auto &quote : m_quotes) {
                auto widget = new QuoteWidget(this);
                widget->setQuote(quote);
                quotesPanelLayout->addWidget(widget);
            }
        });
        connect(fetcher, &QuoteFetcher::error, this, [=](const QString &message) {
            qDebug() << "error " << message;
        });
        fetcher->fetchQuotes();
    };
    connect(ui->actionFetchQuotes, &QAction::triggered, this, [=]() { runFetch(); });
    connect(fetchButton, &QPushButton::clicked, this, [=]() { runFetch(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
