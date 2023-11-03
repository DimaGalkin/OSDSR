#pragma once

#include "dsr/renderer.hpp"

static constexpr GlobalSpaceTriangle tri1 = {
    { -50 , 50 , 0 },
    { -50 , -50 , 0 },
    { 50 , 50 , 0 }
};

static constexpr GlobalSpaceTriangle tri2 = {
    { 50 , -50 , 0 },
    { 50 , 50 , 0 },
    { -50 , -50 , 0 },
};

static constexpr GlobalSpaceTriangle tri3 = {
    { -50 , -50 , 50 },
    { -50 , 50 , 50 },
    { 50 , 50 , 50 }
};

static constexpr GlobalSpaceTriangle tri4 = {
    { 50 , 50 , 50 },
    { 50 , -50 , 50 },
    { -50 , -50 , 50 }
};

static constexpr GlobalSpaceTriangle tri5 = {
    { -50 , 50 , 50 },
    { -50 , -50 , 50 },
    { -50 , -50 , 0 }
};

static constexpr GlobalSpaceTriangle tri6 = {
    { -50 , -50 , 0 },
    { -50 , 50 , 0 },
    { -50 , 50 , 50 }
};

static constexpr GlobalSpaceTriangle tri7 = {
    { 50 , -50 , 0 },
    { 50 , -50 , 50 },
    { 50 , 50 , 50 }
};

static constexpr GlobalSpaceTriangle tri8 = {
    { 50 , 50 , 50 },
    { 50 , 50 , 0 },
    { 50 , -50 , 0 }
};

static constexpr GlobalSpaceTriangle tri9 = {
    { -50 , -50 , 0 },
    { -50 , -50 , 50 },
    { 50 , -50 , 50 }
};

static constexpr GlobalSpaceTriangle tri10 = {
    { -50 , -50 , 0 },
    { 50 , -50 , 50 },
    { 50 , -50 , 0 }
};

static constexpr GlobalSpaceTriangle tri11 = {
    { 50 , 50 , 50 },
    { -50 , 50 , 50 },
    { -50 , 50 , 0 }
    
};

static constexpr GlobalSpaceTriangle tri12 = {
    { 50 , 50 , 0 },
    { 50 , 50 , 50 },
    { -50 , 50 , 0 }
};

static constexpr GlobalSpaceTriangle cube[12] = {
    tri1,
    tri2,
    tri3,
    tri4,
    tri5,
    tri6,
    tri7,
    tri8,
    tri9,
    tri10,
    tri11,
    tri12
};