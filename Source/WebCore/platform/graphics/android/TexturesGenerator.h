/*
 * Copyright 2010, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TexturesGenerator_h
#define TexturesGenerator_h

#if USE(ACCELERATED_COMPOSITING)

#include "QueuedOperation.h"
#include "TilePainter.h"
#include <wtf/Vector.h>

#include <utils/threads.h>

namespace WebCore {

using namespace android;

class TilesManager;

class TexturesGenerator : public Thread {
public:
    TexturesGenerator(TilesManager* instance) : Thread(false)
        , m_waitForCompletion(false)
        , m_currentOperation(0)
        , m_tilesManager(instance) { }
    virtual ~TexturesGenerator() { }
    virtual status_t readyToRun();

    void removeOperationsForFilter(OperationFilter* filter, bool waitForRunning = true);

    void scheduleOperation(QueuedOperation* operation);

private:
    QueuedOperation* popNext();
    virtual bool threadLoop();
    WTF::Vector<QueuedOperation*> mRequestedOperations;
    android::Mutex mRequestedOperationsLock;
    android::Condition mRequestedOperationsCond;
    bool m_waitForCompletion;
    QueuedOperation* m_currentOperation;
    TilesManager* m_tilesManager;
};

} // namespace WebCore

#endif // USE(ACCELERATED_COMPOSITING)
#endif // TexturesGenerator_h
