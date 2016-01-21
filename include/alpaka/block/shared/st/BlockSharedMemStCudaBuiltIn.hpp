/**
 * \file
 * Copyright 2014-2015 Benjamin Worpitz, Rene Widera
 *
 * This file is part of alpaka.
 *
 * alpaka is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * alpaka is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with alpaka.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef ALPAKA_ACC_GPU_CUDA_ENABLED

#ifndef __CUDACC__
    #error If ALPAKA_ACC_GPU_CUDA_ENABLED is set, the compiler has to support CUDA!
#endif

#include <alpaka/block/shared/st/Traits.hpp>// AllocVar, AllocArr

#include <alpaka/core/Common.hpp>           // ALPAKA_FN_ACC_CUDA_ONLY

#include <type_traits>                      // std::is_trivially_default_constructible, std::is_trivially_destructible

namespace alpaka
{
    namespace block
    {
        namespace shared
        {
            namespace st
            {
                //#############################################################################
                //! The GPU CUDA block shared memory allocator.
                //#############################################################################
                class BlockSharedMemStCudaBuiltIn
                {
                public:
                    using BlockSharedMemStBase = BlockSharedMemStCudaBuiltIn;

                    //-----------------------------------------------------------------------------
                    //! Default constructor.
                    //-----------------------------------------------------------------------------
                    ALPAKA_FN_ACC_CUDA_ONLY BlockSharedMemStCudaBuiltIn() = default;
                    //-----------------------------------------------------------------------------
                    //! Copy constructor.
                    //-----------------------------------------------------------------------------
                    ALPAKA_FN_ACC_CUDA_ONLY BlockSharedMemStCudaBuiltIn(BlockSharedMemStCudaBuiltIn const &) = delete;
                    //-----------------------------------------------------------------------------
                    //! Move constructor.
                    //-----------------------------------------------------------------------------
                    ALPAKA_FN_ACC_CUDA_ONLY BlockSharedMemStCudaBuiltIn(BlockSharedMemStCudaBuiltIn &&) = delete;
                    //-----------------------------------------------------------------------------
                    //! Copy assignment operator.
                    //-----------------------------------------------------------------------------
                    ALPAKA_FN_ACC_CUDA_ONLY auto operator=(BlockSharedMemStCudaBuiltIn const &) -> BlockSharedMemStCudaBuiltIn & = delete;
                    //-----------------------------------------------------------------------------
                    //! Move assignment operator.
                    //-----------------------------------------------------------------------------
                    ALPAKA_FN_ACC_CUDA_ONLY auto operator=(BlockSharedMemStCudaBuiltIn &&) -> BlockSharedMemStCudaBuiltIn & = delete;
                    //-----------------------------------------------------------------------------
                    //! Destructor.
                    //-----------------------------------------------------------------------------
                    ALPAKA_FN_ACC_CUDA_ONLY /*virtual*/ ~BlockSharedMemStCudaBuiltIn() = default;
                };

                namespace traits
                {
                    //#############################################################################
                    //!
                    //#############################################################################
                    template<
                        typename T,
                        std::size_t TuniqueId>
                    struct AllocVar<
                        T,
                        TuniqueId,
                        BlockSharedMemStCudaBuiltIn>
                    {
                        // NOTE: CUDA requires the constructor and destructor of shared objects to be empty.
                        //  That means it is either std::is_trivially_default_constructible or of the form Type(){}.
                        //static_assert(
                        //    std::is_trivially_default_constructible<T>::value,
                        //    "The type of the object to allocate in block shared memory has to be trivially default constructible!");
                        //static_assert(
                        //    std::is_trivially_destructible<T>::value,
                        //    "The type of the object to allocate in block shared memory has to be trivially destructible!");

                        //-----------------------------------------------------------------------------
                        //
                        //-----------------------------------------------------------------------------
                        ALPAKA_FN_ACC_CUDA_ONLY static auto allocVar(
                            block::shared::st::BlockSharedMemStCudaBuiltIn const &)
                        -> T &
                        {
                            __shared__ T shMem;
                            return shMem;
                        }
                    };
                    //#############################################################################
                    //!
                    //#############################################################################
                    template<
                        typename T,
                        std::size_t TnumElements,
                        std::size_t TuniqueId>
                    struct AllocArr<
                        T,
                        TnumElements,
                        TuniqueId,
                        BlockSharedMemStCudaBuiltIn>
                    {
                        // NOTE: CUDA requires the constructor and destructor of shared objects to be empty.
                        //  That means it is either std::is_trivially_default_constructible or of the form Type(){}.
                        //static_assert(
                        //    std::is_trivially_default_constructible<T>::value,
                        //    "The type of the objects to allocate in block shared memory has to be trivially default constructible!");
                        //static_assert(
                        //    std::is_trivially_destructible<T>::value,
                        //    "The type of the objects to allocate in block shared memory has to be trivially destructible!");
                        static_assert(
                            TnumElements > 0,
                            "The number of elements to allocate in block shared memory must not be zero!");

                        //-----------------------------------------------------------------------------
                        //
                        //-----------------------------------------------------------------------------
                        ALPAKA_FN_ACC_CUDA_ONLY static auto allocArr(
                            block::shared::st::BlockSharedMemStCudaBuiltIn const &)
                        -> T *
                        {
                            __shared__ T shMem[TnumElements];
                            return shMem;
                        }
                    };
                    //#############################################################################
                    //!
                    //#############################################################################
                    template<>
                    struct FreeMem<
                        BlockSharedMemStCudaBuiltIn>
                    {
                        //-----------------------------------------------------------------------------
                        //
                        //-----------------------------------------------------------------------------
                        ALPAKA_FN_ACC_CUDA_ONLY static auto freeMem(
                            block::shared::st::BlockSharedMemStCudaBuiltIn const &)
                        -> void
                        {
                            // Nothing to do. CUDA block shared memory is automatically freed when all threads left the block.
                        }
                    };
                }
            }
        }
    }
}

#endif