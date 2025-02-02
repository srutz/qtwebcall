#include "quotewidget.h"
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QLabel>

QuoteWidget::QuoteWidget(QWidget *parent)
    : QWidget{parent}
{
    setStyleSheet(
        "QuoteWidget {"
        "   background-color: white;"
        "   border-radius: 10px;"  // Rounded corners
        "   padding: 8px;"         // Inner padding
        "   margin: 4px;"          // Space for shadow
        "}"
    );
    setStyleSheet(
        "  background-color: white;"
        "  border-radius: 10px;"  // Rounded corners
        "  padding: 8px;"         // Inner padding
        "  margin: 4px;"          // Space for shadow
    );
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 60));
    shadowEffect->setOffset(0, 4);
    setGraphicsEffect(shadowEffect);
    //resize(480, 200);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    m_layout = new QVBoxLayout(this);
}

void QuoteWidget::setQuote(const Quote &quote) {
    this->m_quote = quote;
    rebuildGui();
}

void QuoteWidget::rebuildGui() {
    if (this->gui) {
        delete this->gui;
    }
    gui = new QWidget(this);
    m_layout->addWidget(gui, 1);
    auto innerLayout = new QVBoxLayout(gui);
    innerLayout->setSpacing(0);
    auto authorLabel = new QLabel(gui);
    auto quoteLabel = new QLabel(gui);
    setMaximumWidth(400);
    setMinimumHeight(140);
    quoteLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    quoteLabel->setWordWrap(true);
    quoteLabel->setStyleSheet("padding: 0px;");
    //quoteLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    innerLayout->addWidget(quoteLabel, 1);
    innerLayout->addWidget(authorLabel, 0, Qt::AlignRight);
    authorLabel->setText(m_quote.author);
    authorLabel->setStyleSheet("padding: 0px; color: #666666; font-size: 12px;");
    quoteLabel->setText(m_quote.quote);
    quoteLabel->adjustSize();
}

