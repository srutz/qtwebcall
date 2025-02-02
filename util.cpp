#include "util.h"
#include <QLayout>
#include <QLayoutItem>


Util::Util() {}

void Util::clearWidget(QWidget *parent) {
    if (!parent) {
        return;
    }
    if (auto layout = parent->layout()) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        auto children = parent->findChildren<QWidget *>();
        for (auto child : children) {
            child->setParent(nullptr); // Detach first to avoid double delete
            delete child;
        }
    }
}
