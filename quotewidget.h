#ifndef QUOTEWIDGET_H
#define QUOTEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

struct Quote
{
    long id;
    QString quote;
    QString author;
};

class QuoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuoteWidget(QWidget *parent = nullptr);
    const Quote& quote() const { return m_quote; };
    void setQuote(const Quote &quote);

private:
    Quote m_quote;
    QVBoxLayout *m_layout;
    QWidget *gui = nullptr;
    void rebuildGui();

signals:
};

#endif // QUOTEWIDGET_H
