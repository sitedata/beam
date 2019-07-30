// Copyright 2019 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "wallet/litecoin/litecoin_side.h"

namespace
{
    constexpr uint32_t kLitecoinWithdrawTxAverageSize = 360;
    constexpr beam::Amount kLitecoinDustThreshold = 546;
    constexpr uint32_t kLitecoinLockTxEstimatedTimeInBeamBlocks = 20;   // it's average value
    constexpr uint8_t kLitecoinMainnetP2KH = 48;
}

namespace beam::wallet
{
    LitecoinSide::LitecoinSide(BaseTransaction& tx, IBitcoinBridge::Ptr bitcoinBridge, ILitecoinSettingsProvider::Ptr settingsProvider, bool isBeamSide)
        : BitcoinSide(tx, bitcoinBridge, settingsProvider, isBeamSide)
    {
    }

    bool LitecoinSide::CheckAmount(Amount amount, Amount feeRate)
    {
        Amount fee = static_cast<Amount>(std::round(double(kLitecoinWithdrawTxAverageSize * feeRate) / 1000));
        return amount > kLitecoinDustThreshold && amount > fee;
    }

    uint32_t LitecoinSide::GetLockTxEstimatedTimeInBeamBlocks() const
    {
        return kLitecoinLockTxEstimatedTimeInBeamBlocks;
    }

    uint8_t LitecoinSide::GetAddressVersion() const
    {
        if (IsMainnet())
        {
            return kLitecoinMainnetP2KH;
        }

        return libbitcoin::wallet::ec_private::testnet_p2kh;
    }
}