/**
* \file
* Copyright 2014-2015 Benjamin Worpitz
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

#include <alpaka/core/Common.hpp>
#include <alpaka/core/Unused.hpp>

#if !BOOST_LANG_CUDA
    #error If ALPAKA_ACC_GPU_CUDA_ENABLED is set, the compiler has to support CUDA!
#endif

#include <alpaka/math/round/Traits.hpp>

#include <cuda_runtime.h>
#include <type_traits>


namespace alpaka
{
    namespace math
    {
        //#############################################################################
        //! The CUDA round.
        class RoundCudaBuiltIn
        {
        public:
            using RoundBase = RoundCudaBuiltIn;
        };

        namespace traits
        {
            //#############################################################################
            //! The CUDA round trait specialization.
            template<
                typename TArg>
            struct Round<
                RoundCudaBuiltIn,
                TArg,
                typename std::enable_if<
                    std::is_floating_point<TArg>::value>::type>
            {
                ALPAKA_FN_ACC_CUDA_ONLY static auto round(
                    RoundCudaBuiltIn const & round_ctx,
                    TArg const & arg)
                -> decltype(::round(arg))
                {
                    alpaka::ignore_unused(round_ctx);
                    return ::round(arg);
                }
            };
            //#############################################################################
            //! The CUDA lround trait specialization.
            template<
                typename TArg>
            struct Lround<
                RoundCudaBuiltIn,
                TArg,
                typename std::enable_if<
                    std::is_floating_point<TArg>::value>::type>
            {
                ALPAKA_FN_ACC_CUDA_ONLY static auto lround(
                    RoundCudaBuiltIn const & lround_ctx,
                    TArg const & arg)
                -> long int
                {
                    alpaka::ignore_unused(lround_ctx);
                    return ::lround(arg);
                }
            };
            //#############################################################################
            //! The CUDA llround trait specialization.
            template<
                typename TArg>
            struct Llround<
                RoundCudaBuiltIn,
                TArg,
                typename std::enable_if<
                    std::is_floating_point<TArg>::value>::type>
            {
                ALPAKA_FN_ACC_CUDA_ONLY static auto llround(
                    RoundCudaBuiltIn const & llround_ctx,
                    TArg const & arg)
                -> long int
                {
                    alpaka::ignore_unused(llround_ctx);
                    return ::llround(arg);
                }
            };
            //! The CUDA round float specialization.
            template<>
            struct Round<
                RoundCudaBuiltIn,
                float>
            {
                __device__ static auto round(
                    RoundCudaBuiltIn const & round_ctx,
                    float const & arg)
                -> float
                {
                    alpaka::ignore_unused(round_ctx);
                    return ::roundf(arg);
                }
            };
        }
    }
}

#endif
