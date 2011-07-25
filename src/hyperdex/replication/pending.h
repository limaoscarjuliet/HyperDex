// Copyright (c) 2011, Cornell University
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of HyperDex nor the names of its contributors may be
//       used to endorse or promote products derived from this software without
//       specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef hyperdex_replication_pending_h_
#define hyperdex_replication_pending_h_

// e
#include <e/intrusive_ptr.h>

namespace hyperdex
{
namespace replication
{

class pending
{
    public:
        pending(bool has_value,
                const std::vector<e::buffer>& value,
                const clientop& co = clientop());

    public:
        const bool has_value;
        const std::vector<e::buffer> value;
        clientop co;
        bool fresh;
        bool acked;
        bool ondisk; // True if the pending update is already on disk.
        bool mayack; // True if it is OK to receive ACK messages.
        regionid _prev;
        regionid _next;

    private:
        friend class e::intrusive_ptr<pending>;

    private:
        size_t m_ref;
};

inline
pending :: pending(bool hv,
                   const std::vector<e::buffer>& val,
                   const clientop& c)
    : has_value(hv)
    , value(val)
    , co(c)
    , fresh(false)
    , acked(false)
    , ondisk(false)
    , mayack(false)
    , _prev()
    , _next()
    , m_ref(0)
{
}

} // namespace replication
} // namespace hyperdex

#endif // hyperdex_replication_pending_h_
