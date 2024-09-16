#include "Emitter.h"

Emitter::Emitter() {
}

Emitter& Emitter::onInfo(std::function<void(const Emitter::Info&)> handler) {
    _infoHandler = handler;
    return *this;
}
